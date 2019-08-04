#ifndef DISPLAY_H
#define DISPLAY_H
#ifndef MAIN_H
#define MAIN_H

#endif // MAIN_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;

class Displayone
{
public:
    Displayone();
    void ProcessDate();//更新数据库
    void DetectPerson(Mat image);//
    Mat MoveDetect(Mat temp, Mat frame);
    void DetectFace(Mat frame);
    ~Displayone();
};

#endif // DISPLAY_H
