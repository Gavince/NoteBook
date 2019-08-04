## Opencv+Qt(实现行人检测)

[Qt+opencv2.4.9安装](<https://blog.csdn.net/qq_15947787/article/details/77628705>)

[行人检测参考代码1](<https://blog.csdn.net/GoJawee/article/details/72831660>)

[行人检测参考代码2](https://blog.csdn.net/y1054765649/article/details/88781462)

[行人检测参考代码3](https://blog.csdn.net/myclass1312/article/details/80762855)

- **参考博客**
  1.  [Hog+OpenCv](<https://blog.csdn.net/qq_34106574/article/details/81982628>)
  2.  [利用Hog特征和SVM分类器进行行人检测](<https://blog.csdn.net/qq_26898461/article/details/46786033>)
  3.   [sliding window](<https://www.cnblogs.com/klitech/p/5727880.html>)
  4.  [HOG人体特征提取+SVM分类器训练进行人体检测](<https://blog.csdn.net/Hdu_lc14015312/article/details/66475251>)
  5.  [训练SVM分类器](<https://blog.csdn.net/chaipp0607/article/details/68067098>)
  6.  [opencv中SVM和HOG封装语句介绍](<https://juejin.im/post/5b0e70686fb9a00a1451c8e7#heading-2>)
  7.  [行人检测***](<http://www.mashangxue123.com/opencv/1063667049.html>)
  8.  [添加额外的包](<https://blog.csdn.net/qq_34360180/article/details/66978979>)
  9.  

---

- **出现的问题**

1. **Qt5 #include<QMessageBox> : No such file or directory**

   > 解决方法：pro文件中添加QT += widgets

2. **HIGHGUI ERROR: V4L/V4L2: VIDIOC_S_CROP**

   >[链接]()（<https://blog.csdn.net/ygxqt/article/details/79944136>）

3. **一些基本的操作**

   >CV_CAP_PROP_POS_MSEC 视频当前点的毫秒值或视频捕捉的时间戳
   >
   >CV_CAP_PROP_POS_FRAMES 下次将被捕获的0基索引的帧
   >CV_CAP_PROP_POS_AVI_RATIO 视频文件的相关位置: 0 - start of the film, 1 - end of the film.
   >CV_CAP_PROP_FRAME_WIDTH 视频流帧的宽度
   >CV_CAP_PROP_FRAME_HEIGHT 视频流帧的高.
   >CV_CAP_PROP_FPS 帧率.
   >CV_CAP_PROP_FOURCC 4字符编码的编码器.
   >CV_CAP_PROP_FRAME_COUNT 视频文件的帧数.
   >CV_CAP_PROP_FORMAT 由retrieve()返回矩阵对象的格式 .
   >CV_CAP_PROP_MODE 后端指定值指示当前捕捉的模式.
   >CV_CAP_PROP_BRIGHTNESS 图像亮度 (只对摄像头).
   >CV_CAP_PROP_CONTRAST 图像对比度 (only for cameras).
   >CV_CAP_PROP_SATURATION 图像饱和度 (only for cameras).
   >CV_CAP_PROP_HUE 色调 (only for cameras).
   >CV_CAP_PROP_GAIN 增益(only for cameras).
   >CV_CAP_PROP_EXPOSURE 曝光(only for cameras).
   >CV_CAP_PROP_CONVERT_RGB 布尔型标记图像是否应该被转换为RGB.
   >CV_CAP_PROP_WHITE_BALANCE 白平衡（目前不支持）

4. **OpenCV的Rect矩形类用法**

   >[链接](<https://blog.csdn.net/u013270326/article/details/72956402>)

5. **sprintf函数的作用及用法**

   >[链接](<https://blog.csdn.net/Adusts/article/details/81637631>)

6. **‘Mat’ was not declared in this scope opencv**

   >[链接](<https://stackoverflow.com/questions/51858028/mat-was-not-declared-in-this-scope-opencv>)

7. **undefined reference to `cv::HOGDescriptor::setSVMDetector**

   >opencv库文件没有添加全（为避免错误，应该全部添加）

8. **public CvSVM的问题**

   >OpenCv2上还存在CvSVM,OpenCv3已经不再支持

9. **不能读出本地视频**

   >[链接1](<https://blog.csdn.net/sinat_36138358/article/details/52846617>)
   
10. **优化opencv读取视频的卡顿问题**

    >[链接](<https://blog.csdn.net/qq_30155503/article/details/79637231>
    
11.  **libpng error: IDAT: invalid distance too far back错误**

    > [链接](<https://blog.csdn.net/qq_33375598/article/details/89182785>)
    
12. **hog.detectMultiScale()**

    > 	构造了一个尺度scale=1.05的图像金字塔，以及一个分别在x方向和y方向步长为(4,4)像素大小的滑窗scale的尺度设置得越大，在图像金字塔中层的数目就越少，相应的检测速度就越快，但是尺度太大会导致行人出现漏检；同样的，如果scale设置得太小，将会急剧的增加图像金字塔的层数，这样不仅耗费计算资源，而且还会急剧地增加检测过程中出现的假阳数目(也就是不是行人的被检测成行人)。这表明，scale是在行人检测过程中它是一个重要的参数，需要对scale进行调参。我会在后面的文章中对detectMultiScale中的每个参数做些调研
    >
    > 	[链接](<https://www.cnblogs.com/klitech/p/5747895.html>)
    
13.  **直方图均衡化的优缺点**

    >　这种方法对于背景和前景都太亮或者太暗的图像非常有用，这种方法尤其是可以带来X光图像中更好的骨骼结构显示以及曝光过度或者曝光不足照片中更好的细节。这种方法的一个主要优势是它是一个相当直观的技术并且是可逆操作，如果已知均衡化函数，那么就可以恢复原始的直方图，并且计算量也不大。
    >
    >​	这种方法的一个缺点是它对处理的数据不加选择，它可能会增加背景杂讯的对比度并且降低有用信号的对比度；变换后图像的灰度级减少，某些细节消失；某些图像，如直方图有高峰，经处理后对比度不自然的过分增强.
    
14. **opencv打不开本地视频**

    >[链接1(未能解决)equalizeHist](<https://www.cnblogs.com/fariver/p/6502199.html>)
    >
    >2.4.9Ubuntu缺少一个解码库， 未能正确安装。以至于不能解决， 待以后解决。
    
15. **膨胀、腐蚀、开闭运算**

    > [链接](<http://www.cnblogs.com/skyfsm/p/6874274.html>)

16. **getStructuringElement()函数的介绍**

    >[链接](<https://blog.csdn.net/dcrmg/article/details/52089538>)

17. **IplImage*指针类型的使用**

    >[链接](<https://www.cnblogs.com/codingmengmeng/p/6559724.html>)

18. **cvCreateImage函数说明**

    > [链接](<https://blog.csdn.net/breeze5428/article/details/30050327>)
    
19. **C++中的全局变量声明和定义**

    >[链接](<https://blog.csdn.net/whocarea/article/details/84887401>)
    
20. **format函数**

    > [链接](<https://blog.csdn.net/fanjiule/article/details/81606874>

### 人脸识别

1. **生成csv文件**

   - 代码

     ```c++
     #include<iostream>
     #include<vector>
     #include<io.h>
     #include<fstream>
     
     using namespace std;
     
     void getFiles(string path, vector<string>& files)
     {
         //文件句柄  
         long   hFile = 0;
         //文件信息  
         struct _finddata_t fileinfo;
         string p;
         if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
         {
             do
             {
                 //如果是目录,迭代之  
                 //如果不是,加入列表  
                 if ((fileinfo.attrib &  _A_SUBDIR))
                 {
                     if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                         getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
                 }
                 else
                 {
                     files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                 }
             } while (_findnext(hFile, &fileinfo) == 0);
             _findclose(hFile);
         }
     }
     
     int main(){
         char* filepath = "F:\\opencv\\DATA\\orl";
         vector<string> files;
         ofstream off("csv.txt",ios::out);
         getFiles(filepath,files);
         char str[30];
         int size = files.size();
         for (int i = 1; i < size; i++){
             off << files[i].c_str();
             off << "\n";
         }
         off.close();
         return 0;
     }
     
     ```
  ```
   
   - [链接](<https://blog.csdn.net/u013812682/article/details/52013074>)
   
   - [Ubuntu链接](<https://blog.csdn.net/u012679707/article/details/79519143>)
   
   - 代码
   
     ```C++
     #include <opencv2/core/core.hpp>
     #include <opencv2/imgproc/imgproc.hpp>
     #include <opencv2/highgui/highgui.hpp>
     #include <opencv2/opencv.hpp>
     #include<opencv2/face/facerec.hpp>
     #include <opencv2/ml/ml.hpp>
     #include <iostream>
     #include <vector>
     #include <stdio.h>
     
     using namespace cv;
     using namespace cv::face;
     using namespace std;
     
     static int g_flag1;
     static int g_flag2;
     static int g_num;
     vector<Mat> images;
     vector<int> labels;
     static Mat testsample;
     static int testlabel;
     static int heigh;
     static int width;
     string haar_face_datapath = "/home/gavin/Software/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_alt2.xml";
     
     void ProcessDate();
     
     void DetectPerson(Mat image);
     Mat MoveDetect(Mat temp, Mat frame);
     void Detectpersion(Mat frame)
     {
         Mat gray, dst;
         vector<Rect> faces;
         Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
         model->train(images, labels);
         CascadeClassifier faceDetector;
         faceDetector.load(haar_face_datapath);
     
         flip(frame, frame, 1);
         cvtColor(frame, gray,COLOR_BGR2GRAY);
         equalizeHist(gray,gray);
         faceDetector.detectMultiScale(gray, faces, 1.1, 4, 0, Size(80, 100), Size(380, 400));
     
         for(int i = 0;i < faces.size(); i++)
         {
             Mat roi = frame(faces[i]);
             cvtColor(roi, dst, COLOR_BGR2GRAY);
             resize(dst, testsample, testsample.size());
             int label = model->predict(testsample);
             if(label  == 19)
             {
                 cout<< "张万玉" <<endl;
             }
             //cout<< "label:" << label << endl;
             //rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
             //putText(frame, format("%s",(label == 19 ?"zhangwanyu":"Unknow")), faces[i].tl(),FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 2, 255), 2, 8);
         }
     //    imshow("face_recongnize", frame);
     //    char c = waitKey(10);
     }
     int main(int argc, char *argv[])
     {
             //VideoCapture cap("/home/gavin/Videos/2.mp4");
             VideoCapture cap(0);
             ProcessDate();//处理数据
             g_num = 0;//初始化照片的顺序
             g_flag1 = 0;
             g_flag2 = 0;
             int flag = 0;//标记要检查的帧
             if (!cap.isOpened())
             {
                 cout<< "无法打开视频" <<endl;
                 return -1;
             }
     
             while(1)
             {
                 int frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);//获得总帧数
                 double FPS = cap.get(CV_CAP_PROP_FPS);//获得帧数
                 Mat frame; //获取视频中的每一帧
                 Mat temp;//获取前一帧的数据
                 Mat result;
                 //处理每一帧的数据
                 for(int i = 0; i< 10000; i++)
                 {
                     cap>>frame;//获得每一帧
                     //imshow("frame", frame);
                     if(frame.empty())
                     {
                         cout<< "获不到视频中的帧" <<endl;
                         break;
                     }
     
                     flag += 1;
                     //g_flag += 1;
     
                     if (i == 0)//第一帧 没有先前的帧
                     {
                         result = MoveDetect(frame, frame);
                     }
                     else
                     {
                         result = MoveDetect(temp, frame);
                         //cout<< "flag" << flag << endl;
                         if((flag % 24 == 0) && ( g_flag2 > 3) )
                         {
                             DetectPerson(frame);
                             Detectpersion(frame);
                             flag = 0;
                         }
                     }
                     imshow("result", result);//显示最终处理结果
                     if(waitKey(1000.0 / FPS) == 27)
                     {
                         destroyAllWindows();
                         cap.release();
                         cout << "退出检测" << endl;
                         return 0;
                     }
     
                     temp = frame.clone();//获得前一帧的数据
                 }
             }
     }
     
     Mat MoveDetect(Mat temp, Mat frame)
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
         drawContours(result, contours,-1,Scalar(255,0,0), 2, 8);
         //cout<< "数量：" << contours.size() << endl;
         if (contours.size() > 0)
         {
             g_flag1 += 1;
             if(g_flag1 > 20)
             {
                 g_flag1 = 0;
                 g_flag2 += 1;
                 cout<< "检测有异常，正在进行身份验证" <<endl;
             }
         }
     //    vector<Moments> mu(contours.size() );
     //    for(int k = 0; k < (int)contours.size(); k++)
     //    {
     //        mu[k] = moments( contours[k], false );
     //        if (mu[k].m00>1000)
     //
     //    }
         //drawContours(result, contours, -1, Scalar(0, 0, 255), 2, 8);
         //drawContours(result, contours, -1, Scalar(255), CV_FILLED);
     
         /**************************HOG+SVM*******************************/
     //    if(flag == 24)
     //    {
     //        HOGDescriptor hog;
     //        hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
     //        hog.detectMultiScale(diff_thresh, found,0 ,Size(8, 8), Size(32, 32), 1.05, 2);
     //        for (uint i = 0; i<found.size(); i++)
     //        {
     //            //第几个矩形框的大小
     //            Rect r = found[i];
     //            uint j = 0;
     //            for (; j<found.size(); j++)
     //            {
     //                if (j != i && (r & found[j]) == r)//判断是否与其他矩形框是覆盖关系
     //                {
     //                    break;
     //                }
     //            }
     //
     //            //如果只有一个窗口
     //            if (j == found.size())
     //                detectNMs.push_back(r);
     //        }
     //
     //        //绘制检测窗口
     //        for (uint i = 0; i<detectNMs.size(); i++)
     //        {
     //            Rect r = detectNMs[i];
     //            r.x += cvRound(r.width*0.1);//cvRound()：返回跟参数最接近的整数值，即四舍五入
     //            r.width = cvRound(r.width*0.8);
     //            r.y += cvRound(r.height*0.06);
     //            r.height = cvRound(r.height*0.9);
     //            rectangle(result, r.tl(), r.br(),Scalar(0, 255, 0), 2);
     //
     //        }
     //    }
     
     //    }
         /************************************************************/
     
     
     
         /*******************************Contours特征检测**************************/
         //7.查找到外界矩形
     //    vector<Rect> boundRect(contours.size());
     //    vector<Rect> detectNMS;
     //    cout<< "Contours size:" << contours.size()<<endl;
     //    cout<< "BoundRect" << boundRect.size() <<endl;
     //    	for (int i = 0; i < contours.size(); i++)
     //	{
     //		boundRect[i] = boundingRect(contours[i]);
     //		rectangle(result, boundRect[i], Scalar(0, 255, 0), 2);//在result上绘制正外接矩形
     //    }
         /**********************************************************/
     
     
     
         /******************************NMS****************************/
     //    //out<< "Contours :" << contours.reference << endl;
     //    for(int i = 0; i < contours.size(); i++)
     //    {
     //        boundRect[i] = boundingRect(contours[i]);
     //
     //        Rect r = boundRect[i];
     //        int j = 0;
     //        cout<< "执行NMS111111" <<endl;
     //        for(; boundRect.size(); j++)
     //        {
     //            if(j != i && (r & boundRect[j]) == r)
     //            {
     //                break;
     //            }
     //        }
     //        cout<< "执行NMS222222222" <<endl;
     //        if (j == boundRect.size())
     //        {
     //            detectNMS.push_back(r);
     //        }
     //        //rectangle(result, boundRect[i], Scalar(0, 255, 0), 2);//画框
     //    }
     //    cout<< "执行NMS的次数" << detectNMS.size()<<endl;
     //
     //    for (int i = 0; i<detectNMS.size(); i++)
     //    {
     //        cout<< "执行NMS的次数" << detectNMS.size()<<endl;
     //        Rect r = detectNMS[i];
     //        r.x += cvRound(r.width*0.1);//cvRound()：返回跟参数最接近的整数值，即四舍五入
     //        r.width = cvRound(r.width*0.8);
     //        r.y += cvRound(r.height*0.06);
     //        r.height = cvRound(r.height*0.9);
     //        rectangle(result, r.tl(), r.br(),Scalar(0, 255, 0), 2);
     //    }
         /*****************************************************************/
     
     
         return result;
     }
     void DetectPerson(Mat image)
     {
         vector<Rect> found, detectNMS;
         Mat gray;
         HOGDescriptor hog;
         char name[100];// 用来保存图像的名字
     
         //1.行人检测
         cvtColor(image, gray, CV_BGR2GRAY);//转灰度图片，减少运算
         hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
         hog.detectMultiScale(gray, found,0 ,Size(8, 8), Size(32, 32), 1.03, 2);
     
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
                 rectangle(image, r.tl(), r.br(),Scalar(0, 0, 0), 2);
     
             }
     
             //4.c存贮检测到的图片
             sprintf(name, "/home/gavin/GProject/photo/after/img%d.png", g_num);
             g_num += 1;
             imwrite(name, image);
             cout<< "检测到有人，已经完成保存图片" <<endl;
         }
     }
     void ProcessDate()
     {
         //1.打开人脸数据集
         string filename = string("/home/gavin/GProject/Detectface/list.csv");
     
         ifstream file(filename.c_str(), ifstream::in);
         if(!file)
         {
             cout<< "Can't open!" <<endl;
             //return -1;
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
                 //cout<< "path:" << path.c_str()<<endl;
                 images.push_back(imread(path, 0));//读取灰度图片
                 labels.push_back(atoi(classlabel.c_str()));
             }
     
         }
         if(images.size()<1 || labels.size()<1)
         {
             cout<< "路径错误！" << endl;
             //return -1;
         }
     
         heigh = images[0].rows;
         width = images[0].cols;
         //cout<< "Heigh:" << heigh << "\nWidth" << width <<endl;
         //2.创建测试样本
         testsample = images[images.size()-1];
         testlabel = labels[labels.size()-1];
         images.pop_back();
         labels.pop_back();
     }
     void Detectpersion(Mat frame)
     {
         Mat gray, dst;
         vector<Rect> faces;
         Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
         model->train(images, labels);
         CascadeClassifier faceDetector;
         faceDetector.load(haar_face_datapath);
     
         flip(frame, frame, 1);
         cvtColor(frame, gray,COLOR_BGR2GRAY);
         equalizeHist(gray,gray);
         faceDetector.detectMultiScale(gray, faces, 1.1, 4, 0, Size(80, 100), Size(380, 400));
     
         for(int i = 0;i < faces.size(); i++)
         {
             Mat roi = frame(faces[i]);
             cvtColor(roi, dst, COLOR_BGR2GRAY);
             resize(dst, testsample, testsample.size());
             int label = model->predict(testsample);
             if(label  == 19)
             {
                 cout<< "张万玉" <<endl;
             }
             //cout<< "label:" << label << endl;
             //rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
             //putText(frame, format("%s",(label == 19 ?"zhangwanyu":"Unknow")), faces[i].tl(),FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 2, 255), 2, 8);
         }
     }
  ```

​     



