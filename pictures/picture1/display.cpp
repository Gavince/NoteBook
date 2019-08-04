#include "display.h"
#include "state.h"
#include <QMessageBox>

string haar_face_datapath = "/home/gavin/NoteBook/picture1/haarcascade_frontalface_alt.xml";
vector<Mat> images;
vector<int> labels;
Mat testsample;
int testlabel;
int heigh;
int width;
Ptr<FaceRecognizer> model;

Displayone::Displayone()
{

}

Displayone::~Displayone()
{

}
void Displayone::DetectFace(Mat frame)
{
    Mat gray, dst;
    vector<Rect> faces;

    CascadeClassifier faceDetector;
    faceDetector.load(haar_face_datapath);

    flip(frame, frame, 1);
    cvtColor(frame, gray,COLOR_BGR2GRAY);
    equalizeHist(gray,gray);
    faceDetector.detectMultiScale(gray, faces, 1.1, 3, 0, Size(80, 100), Size(380, 400));
    if (faces.size()>0)
    {
//        cout<<"检测到人脸，开始验证身份"<<endl;
        for(uint i = 0;i < faces.size(); i++)
        {
            Mat roi = frame(faces[i]);
            cvtColor(roi, dst, COLOR_BGR2GRAY);
            resize(dst, testsample, testsample.size());
            int label = model->predict(testsample);
            //cout<< "label = " << label<<endl;
            //选择人员
            switch(label){
                case 13 :QMessageBox::about(NULL, "人员信息","张万玉") ;break;
                default :QMessageBox::about(NULL, "警告", "非法人员!!!");
                //未添加人员信息
            }
        //rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
        //putText(frame, format("%s",(label == 19 ?"zhangwanyu":"Unknow")), faces[i].tl(),FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 2, 255), 2, 8);
        }
    }
    else
    {
//        cout<< "正在检测人脸...." << endl;
    }

}
void Displayone::DetectPerson(Mat image)
{
    vector<Rect> found, detectNMS;//储存检测框
    Mat gray;
    HOGDescriptor hog;
    char name[100];// 用来保存图像的名字

    //1.行人检测
    cvtColor(image, gray, CV_BGR2GRAY);//转灰度图片，减少运算
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    hog.detectMultiScale(gray, found, 0, Size(8, 8), Size(32, 32), 1.02, 2);

    if(found.size()>0)//判断此时是已经检测到行人
    {
        //2.实现画框
        for (uint i = 0; i<found.size(); i++)
        {
            Rect r = found[i];
            uint j = 0;
            for (; j<found.size(); j++)
            {
                if (j != i && (r & found[j]) == r)//判断是否与其他矩形框是覆盖关系
                {
                    break;
                }
            }
            if (j == found.size())
                detectNMS.push_back(r);
        }
        //3.优化绘制检测窗口
        for (uint i = 0; i<detectNMS.size(); i++)
        {
            Rect r = detectNMS[i];
            r.x += cvRound(r.width*0.1);//cvRound()：返回跟参数最接近的整数值，即四舍五入
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.06);
            r.height = cvRound(r.height*0.9);
            rectangle(image, r.tl(), r.br(),Scalar(0, 0, 255), 2);//
        }
        //4.存贮检测到的图片
        if(g_num == 0)
        {
            //cout<< "正式检测进入人员，开始后台保存行人照片" <<endl;
            g_num += 1;
        }
        else
        {
            sprintf(name, "/home/gavin/NotoBook/photo/img%d.png", g_num);
            g_num += 1;
            imwrite(name, image);
        }
    }
}

Mat Displayone::MoveDetect(Mat temp, Mat frame)
{
    Mat result = frame.clone();
    //1.高斯平滑处理
    //前一帧的高斯平滑
    //IplImage* tempimg_src;
    IplImage* tempimg_dst;
    IplImage tmp1 = IplImage(temp);
    IplImage* tempimg_src = &tmp1;
    //tempimg_src = &IplImage(temp);
    tempimg_dst = cvCreateImage(cvGetSize(tempimg_src), 8, 3);//创建目标图像的内存
    cvSmooth(tempimg_src, tempimg_dst, CV_BLUR, 3, 3, 0, 0);//高斯平滑

    //当前帧的高斯平滑
    //IplImage *frame_src;
    IplImage *frame_dst;
    //frame_src = &IplImage(frame);
    IplImage tmp2 = IplImage(frame);
    IplImage *frame_src = &tmp2;
    frame_dst = cvCreateImage(cvGetSize(frame_src), 8, 3);
    cvSmooth(frame_src, frame_dst, CV_BLUR, 3, 3, 0, 0);

    Mat temp1, frame1;
    temp1 = cvarrToMat(tempimg_dst);
    frame1 = cvarrToMat(frame_dst);

    //2.灰度化
    Mat gray1, gray2;
    cvtColor(temp1, gray1, CV_BGR2GRAY);
    cvtColor(frame1, gray2, CV_BGR2GRAY);

    //2.做差分
    Mat diff;
    absdiff(gray1, gray2, diff);
    //imshow("帧差图", diff);

    //3.得到核函数
    Mat diff_thresh;
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(3, 3));

    //4.二值化
    threshold(diff, diff_thresh, 50, 255, CV_THRESH_BINARY);
    //imshow("二值化后", diff_thresh);

    //5.膨胀
    dilate(diff_thresh, diff_thresh, kernel_dilate);
    //imshow("膨胀后", diff_thresh);

    //6.腐蚀
    erode(diff_thresh, diff_thresh, kernel_erode);
    //imshow("腐蚀后", diff_thresh);

    //7.查找轮廓
    vector< vector<Point> > contours;
    //vector<Rect> found, detectNMs;
    findContours(diff_thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //7.过滤多余轮廓
    drawContours(result, contours,-1,Scalar(0, 0, 0), 2, 8);
    //cout<< "数量：" << contours.size() << endl;

    if (contours.size() > 0)
    {
        g_flag1 += 1;
        if(g_flag1 > 10)
        {
            g_flag1 = 0;
            g_flag2 += 1;
            cout<< "检测有异常" <<endl;
        }
    }
    else
    {
        g_flag3 += 1;
        if(g_flag3 == 20)
        {
          g_flag3 = 0;
          g_flag2 = 0;
          cout<< "未发现异常" << endl;
        }
    }
    return result;
}
void Displayone::ProcessDate()
{

    QMessageBox::about(NULL, "Notice" ,"Updating database!");

    //1.打开人脸数据集
    string filename = string("/home/gavin/NoteBook/picture1/mylist.csv");
    ifstream file(filename.c_str(), ifstream::in);
    if(!file)
    {
        QMessageBox::about(NULL, "Error", "Can't open the datebase of face!");
    }
    string line, path, classlabel;
    char separtor = ';';

    while(getline(file, line))
    {
        stringstream liness(line);
        getline(liness, path, separtor);
        getline(liness, classlabel);
        if(!path.empty()&&!classlabel.empty())
        {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }

    }
    if(images.size()<1 || labels.size()<1)
    {
        QMessageBox::about(NULL, "Error", "Route Error!");
    }
    heigh = images[0].rows;
    width = images[0].cols;

    //2.创建测试样本
    testsample = images[images.size()-1];
    testlabel = labels[labels.size()-1];
    images.pop_back();
    labels.pop_back();
    model = createEigenFaceRecognizer();
    model->train(images, labels);
    QMessageBox::about(NULL, "Notice","Updated database!");
}
