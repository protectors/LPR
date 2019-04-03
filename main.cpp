#include "mainwindow.h"
#include <QApplication>
//#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("车牌识别系统"));
    w.show();
    return a.exec();
}

/*
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
using namespace cv;
int main(int argc, char *argv[])
{
   cv::Mat image=cv::imread("/Users/zhangfeng/Pictures/feng.jpg");

   cv::namedWindow("aaa");

   cv::imshow("myimage",image);

   cv::waitKey(50000);

    return 0;
}
*/
