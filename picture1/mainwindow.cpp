#include "mainwindow.h"
#include "ui_mainwindow.h"



static int num = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ReadFrame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadFrame()
{
    Displayone display = Displayone();

    //1.数据预处理
    display.ProcessDate();
    QImage img;

    int flag = 0;//标记要检查的帧
    Mat frame; //获取视频中的每一帧
    Mat temp;//获取前一帧的数据
    Mat result;
    Mat rgb;

    if (!cap.isOpened())
    {
        QMessageBox::about(NULL,"Notice","Can't open video!");
    }
    //2.处理帧数据
    while(1)
    {
        //2.1处理每一帧的数据
        for(int i = 0; i< 10000; i++)
        {
            cap>>frame;
            this->update();
            if(frame.empty())
            {
                QMessageBox::about(NULL, "Notice", "Can't catch a frame!");

            }

            flag += 1;
            if (i == 0)//第一帧 没有先前的帧
            {
                result = display.MoveDetect(frame, frame);
            }
            else
            {
                result = display.MoveDetect(temp, frame);
                if((flag % 24 == 0) && ( g_flag2 > 3) )//第一次检测六帧数据后，正式开始检测入侵人员检测
                {
                    display.DetectPerson(frame);
                    display.DetectFace(frame);
                    flag = 0;
                }
            }
            temp = frame.clone();//获得前一帧的数据，做帧差

            //2.2显示数据
            if(result.channels() == 3)    // RGB image
            {

                cvtColor(result,rgb,CV_BGR2RGB);
                img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                             rgb.cols,rgb.rows,
                             rgb.cols*rgb.channels(),   //new
                             QImage::Format_RGB888);
            }else                     // gray image
            {
                img = QImage((const uchar*)(result.data),
                             result.cols,result.rows,
                             result.cols*result.channels(),  //new
                             QImage::Format_Indexed8);
            }

          ui->label_2->setPixmap(QPixmap::fromImage(img.scaled(ui->label_2->size(), Qt::KeepAspectRatio)));//显示图像
          ui->label_2->update();
          ui->label_2->show();
          waitKey(10);
          imshow("Detect Video", result);//显示最终处理结果
        }
    }
    display.~Displayone();
}

void MainWindow::on_pushButton_3_clicked()
{
    //VideoCapture cap("/home/gavin/Videos/vtest.avi");
    cap.open(0);
    timer->start(30);
}
void MainWindow::on_pushButton_2_clicked()
{
    Mat rgb;
    char name[100];
    num = num-1;
    if(num == 0)
    {

        QMessageBox::about(NULL,"Notice", "This is frist photo!");
        num = 1;
    }
    sprintf(name, "/home/gavin/NoteBook/picture1/photo/img%d.png", num);
    Mat mat = imread(name);
    QImage img;
    if(mat.channels() == 3)    // RGB image
    {

        cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),   //new
                     QImage::Format_RGB888);
    }else                     // gray image
    {
        img = QImage((const uchar*)(mat.data),
                     mat.cols,mat.rows,
                     mat.cols*mat.channels(),  //new
                     QImage::Format_Indexed8);
    }
  ui->label->setPixmap(QPixmap::fromImage(img.scaled(ui->label->size(), Qt::KeepAspectRatio)));//显示图像

}

void MainWindow::on_pushButton_clicked()
{

    Mat rgb;
    char name[100];
    num = num+1;
    sprintf(name, "/home/gavin/NoteBook/picture1/photo/img%d.png", num);
    Mat mat = imread(name);
    if(mat.empty())
    {
//        cout<< "This is last photo!" << endl;
        QMessageBox::about(NULL, "Notice", "This is last photo!");
        num = num -1;
        sprintf(name, "/home/gavin/NoteBook/picture1/photo/img%d.png", num);
        mat = imread(name);
    }

    QImage img;
    if(mat.channels() == 3)    // RGB image
    {

        cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),  //(const unsigned char*)
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),   //new
                     QImage::Format_RGB888);
    }else                     // gray image
    {
        img = QImage((const uchar*)(mat.data),
                     mat.cols,mat.rows,
                     mat.cols*mat.channels(),  //new
                     QImage::Format_Indexed8);
    }
  ui->label->setPixmap(QPixmap::fromImage(img.scaled(ui->label->size(), Qt::KeepAspectRatio)));//显示图像
}
