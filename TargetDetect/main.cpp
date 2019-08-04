#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;
void Draw(vector<Rect> &detectNMS, Mat &img);
vector<Rect> DetectAndDraw(HOGDescriptor &hog, Mat &img);
//主函数
int main(int argc, char *argv[])
{
    char name[100];// 用来保存图像的名字
    int i = 0;
    vector<Rect> r;
    int flag1 = 0;
    int flag = 0;//记录帧输的标志

    //double scale = 4;
    //1.Hog特征检测器
    HOGDescriptor hog;
    //2.打开摄像头，读取数据
    //VideoCapture cap(0);
    //cap.set(CV_CAP_PROP_FPS, 60);//帧率 帧/秒
    //cap.open("http://admin:admin@10.153.25.136:8081/");
    VideoCapture cap("/home/gavin/Videos/1.flv");//获取本地视频
    Mat frame;//存储视频中的每一帧的数据

    if (!cap.isOpened())
    {
       cout<< "open video failer!" <<endl;
       waitKey(1000);
    }
    //3.得到分类器
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    //hog.setSVMDetector(GetSvm());

    while(1)
    {
        cap.read(frame);
        flag1 += 1;
         //4.判断图片是否已经读取
        if(frame.empty())
        {
            cout<<"Cannot read a frame from video stream!"<<endl;
            break;
        }
//        flag += 1;
        //5.检测并且标定行
//        if (flag == 10)
//        {
//            i += 1;
//
//            sprintf(name, "/home/gavin/GProject/photo/before/img%d.png", i);
//            imwrite(name, frame);//        flag += 1;

//        }
        //5.per10帧保存一张图片到文件
        if(flag1 == 24)
        {
            r = DetectAndDraw(hog, frame);
            flag1 = 0;
        }
        Draw(r, frame);
//        if (flag == 10)
//        {
//            flag = 0 ;
//
//            sprintf(name, "/home/gavin/GProject/photo/after/img%d.png", i);
//            imwrite(name, frame);
//        }
        //6.显示图片
        namedWindow("Detect Win", WINDOW_NORMAL);

        imshow("Detect Win", frame);
        //cout<< "Fps" << cap.get(CV_CAP_PROP_FPS )<<"ms"<<endl;
        //7.退出窗口
        int c =(waitKey(cap.isOpened() ? 30:0)) & 255;
        if (c == 'q'|| c == 'Q' || c == 27)
            break;
    }

    cap.release();//释放摄像头
    destroyAllWindows();

    return 0;
}
vector<Rect> DetectAndDraw(HOGDescriptor &hog,Mat &img)
{
    double t = 0;
    Mat gray, person;
    //返回 width*heigh from x,y
    vector<Rect> found, detectNMs;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    //优化
   // Mat gray, person;
   // double fx = 1/scale;
    //cvtColor(img, person, COLOR_BGR2GRAY);// 将源图像转为灰度图
   // resize(gray, person,Size(), fx, fx, INTER_LINEAR);//缩放图像
    resize(gray, person, Size(64, 128),0, 0, INTER_LINEAR);
    //equalizeHist(gray, person);	// 直方图均衡化，提高图像质量

    t = (double) getTickCount();
    //多目标检测
    hog.detectMultiScale(img, found, 0.5, Size(4, 4), Size(32, 32), 1.03, 2);
   // cout<<"当前窗口数目:"<< found.size()<<"个"<< endl;

    t = (double)getTickCount() - t;//获得处理的时间
    printf( "Detection time = %g ms\n", t*1000/getTickFrequency());

    for (uint i = 0; i<found.size(); i++)
    {
        //第几个矩形框的大小
        Rect r = found[i];
        uint j = 0;
        for (; j<found.size(); j++)
        {
            if (j != i && (r & found[j]) == r)//判断是否与其他矩形框是覆盖关系
            {
                break;
            }
        }
        //如果只有一个窗口
        if (j == found.size())
            detectNMs.push_back(r);
    }

    return detectNMs;
}

void Draw(vector<Rect> &detectNMS, Mat &img)
{
    //绘制检测窗口
    for (uint i = 0; i<detectNMS.size(); i++)
    {
        Rect r = detectNMS[i];
        r.x += cvRound(r.width*0.1);//cvRound()：返回跟参数最接近的整数值，即四舍五入
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.06);
        r.height = cvRound(r.height*0.9);
        rectangle(img, r.tl(), r.br(),Scalar(255, 0, 0), 2);
    }
}
