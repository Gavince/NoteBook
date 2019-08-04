//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//#include <opencv2/opencv.hpp>
//#include <opencv2/ml/ml.hpp>
//#include<iostream>
//#include <iostream>
//#include<time.h>
//#include <fstream>
//#include <QApplication>
//#include<QMessageBox>
//#include<QtDebug>
//
//using namespace std;
//using namespace cv;
//
//class MySVM : public SVM
//{
//    public:
//        获得SVM的决策函数中的alpha数组
//        double * get_alpha_vector()
//        {
//            return this->decision_func->alpha;
//        }
//
//        获得SVM的决策函数中的rho参数,即偏移量
//        float get_rho()
//        {
//            return this->decision_func->rho;
//        }
//};
//vector<float> GetSvm();
//void DetectAndDraw(HOGDescriptor &hog,Mat &img, double scale);
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    char s[100];// 用来保存图像的名字
//    int i = 0;
//    int flag = 0;//记录帧输的标志
//
//    double scale = 2;
//    1.Hog特征检测器
//    HOGDescriptor hog;
//    2.打开摄像头，读取数据
//    VideoCapture cap(0);
//    cap.set(CV_CAP_PROP_FPS, 60);//帧率 帧/秒
//    cap.open("http://admin:admin@10.153.25.136:8081/");
//    VideoCapture cap("/home/gavin/Videos/1.flv");//获取本地视频
//    Mat frame;//存储视频中的每一帧的数据
//
//    if (!cap.isOpened())
//    {
//        QMessageBox mesg;
//        mesg.about(NULL, "notice", "open video failer!");
//        waitKey(1000);
//    }
//    3.得到分类器
//    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
//    hog.setSVMDetector(GetSvm());
//
//    while(1)
//    {
//        cap.read(frame);
//         4.判断图片是否已经读取
//        if(frame.empty())
//        {
//            QMessageBox mesg;
//            mesg.about(NULL,"提示","Cannot read a frame from video stream");
//            break;
//        }
//        flag += 1;
//        5.检测并且标定行人
//        if (flag == 10)
//        {
//            flag = 0;//重新计数
//            i += 1;
//            sprintf(name, "/home/gavin/GProject/photo/before/" + "img" + "%d", i);
//            imwrite(name, frame);
//        }
//        5.没10帧保存一张图片到文件
//        DetectAndDraw(hog, frame, scale);
//        6.显示图片
//        namedWindow("Detect Win", WINDOW_NORMAL);
//        imshow("Detect Win", frame);
//        cout<< "Fps" << cap.get(CV_CAP_PROP_FPS )<<"ms"<<endl;
//        7.退出窗口
//        int c =(waitKey(cap.isOpened() ? 30:0)) & 255;
//        if (c == 'q'|| c == 'Q' || c == 27)
//            break;
//    }
//
//    cap.release();//释放摄像头
//    destroyAllWindows();
//
//    return a.exec();
//}
//
//vector<float> GetSvm()
//{
//   MySVM svm;
//   svm.load("/home/gavin/GProject/data/detect.xml");//加载特征向量
//
//   int DescriptorDim;//Hog 描述子
//   DescriptorDim = svm.get_var_count();//特征向量的维数，即HOG描述子的维数
//   cout<< "Dimensions:" << DescriptorDim <<endl;
//   int supportVectorNum = svm.get_support_vector_count();//支持向量的个数
//   cout<<"支持向量个数："<<supportVectorNum<<endl;
//
//   Mat alphaMat = Mat::zeros(1, supportVectorNum, CV_32FC1);//alpha向量，长度等于支持向量个数
//   Mat supportVectorMat = Mat::zeros(supportVectorNum, DescriptorDim, CV_32FC1);//支持向量矩阵
//   Mat resultMat = Mat::zeros(1, DescriptorDim, CV_32FC1);//alpha向量乘以支持向量矩阵的结果
//
//    将支持向量的数据复制到supportVectorMat矩阵中
//   for(int i=0; i<supportVectorNum; i++)
//   {
//       const float *pSVData = svm.get_support_vector(i);//返回第i个支持向量的数据指针
//       for(int j=0; j<DescriptorDim; j++)
//       {
//           supportVectorMat.at<float>(i,j) = pSVData[j];
//       }
//   }
//   将alpha向量的数据复制到alphaMat中
//   cout<<svm.get_alpha_vector()<<endl;
//   double *pAlphaData = svm.get_alpha_vector();//返回SVM的决策函数中的alpha向量
//
//   for(int i=0; i<supportVectorNum; i++)
//   {
//       alphaMat.at<float>(0,i) = pAlphaData[i];
//   }
//
//   resultMat = -1 * alphaMat * supportVectorMat;
//   得到最终的setSVMDetector(const vector<float>& detector)参数中可用的检测子
//   vector<float>  myDetector;
//   将resultMat中的数据复制到数组myDetector中
//   for(int i=0; i<DescriptorDim; i++)
//   {
//       myDetector.push_back(resultMat.at<float>(0,i));
//   }
//   最后添加偏移量rho，得到检测子
//   myDetector.push_back(svm.get_rho());
//   cout<<"检测子维数："<<myDetector.size()<<endl;
//
//    保存检测子参数到文件
//   ofstream fout("/home/gavin/GProject/data/detect1.txt");
//   for(uint i=0; i<myDetector.size(); i++)
//   {
//       fout<<myDetector[i]<<endl;
//   }
//
//   return myDetector;
//}
//
//void DetectAndDraw(HOGDescriptor &hog,Mat &img, double scale)
//{
//    double t = 0;
//    返回 width*heigh from x,y
//    vector<Rect> found, detectNMs;
//
//    Mat gray, person;
//    double fx = 1/scale;
//    cvtColor(img, gray, COLOR_BGR2GRAY);// 将源图像转为灰度图
//    resize(gray, person,Size(), fx, fx, INTER_LINEAR);//缩放图像
//    equalizeHist(person, person);	// 直方图均衡化，提高图像质量
//
//    t = (double) getTickCount();
//
//    多目标检测
//    hog.detectMultiScale(person, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
//    cout<<"当前窗口数目:"<< found.size()<<"个"<< endl;
//
//    t = (double)getTickCount() - t;//获得处理的时间
//    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
//
//    for (uint i = 0; i<found.size(); i++)
//    {
//        第几个矩形框的大小
//        Rect r = found[i];
//        uint j = 0;
//        for (; j<found.size(); j++)
//        {
//            if (j != i && (r & found[j]) == r)//判断是否与其他矩形框是覆盖关系
//            {
//                break;
//            }
//        }
//
//        如果只有一个窗口
//        if (j == found.size())
//            detectNMs.push_back(r);
//    }
//
//    绘制检测窗口
//    for (uint i = 0; i<detectNMs.size(); i++)
//    {
//        Rect r = detectNMs[i];
//        r.x += cvRound(r.width*0.1);
//        r.width = cvRound(r.width*0.8);
//        r.y += cvRound(r.height*0.06);
//        r.height = cvRound(r.height*0.9);
//        rectangle(img, r.tl(), r.br(),Scalar(0, 255, 0), 2);
//    }
//}
//
//
