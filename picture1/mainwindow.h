#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "display.h"
#include "state.h"
#include <QString>
#include <QTimer>
#include <QImage>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void ReadFrame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture cap;
    Mat frame;
    Mat result_frame;

};

#endif // MAINWINDOW_H
