#ifndef TEST_H
#define TEST_H

#pragma comment(lib,"Qt5Widgetsd.lib")
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QProcess>
#include <QString>
#include <QDateTime>
#include "logolabel.h"
#include <QFileDialog>
#include <QFile>
#include <vector>
#include <QDebug>
#include <QIODevice>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDirIterator>
#include <iostream>
#include <string>
#include "include/easypr.h"
#include "include/easypr/util/switch.hpp"
#include "include/easypr/core/plate.hpp"
#include "include/easypr/core/chars_segment.h"


namespace Ui {
class test;
}

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    QMenu* preMenu; //预处理目录
    QMenu* sobelMenu;   //算子目录
    QMenu* morphMenu;   //形态学目录
    QMenu* locateMenu;  //定位目录
    QMenu* segmentMenu; //分割目录
    QMenu* detectMenu;  //检测目录
    QMenu* testallMenu; //最终测试
    QAction* testall;
    QAction* testAct[20];
    QAction* trainAct[20];
    QAction* preAct[20];
    QAction* locateAct[20];
    QAction* segmentAct[20];
    QAction* detectAct[20];
    QMenuBar* menuBar ;
    QStatusBar* statusBar;

    String filename;
    String imgname;
    easypr::CPlateRecognize pr;
    easypr::CPlateLocate pl;
    vector<cv::Mat> matVec;
    vector<easypr::CPlate> plateVec;
    vector<RotatedRect> outRects;
    vector<cv::Mat> JudgeResultVec; //判断结果输出
    vector<cv::Mat> SegResultVec;
    easypr::CPlate plate;
    Mat src;        //读入的初始图
    Mat pre_tmp;    //预处理的中间过程
    Mat pre_suanzi; //进行算子比对是使用的中间变量，用于存储处理灰度化的结果
    Mat pre_octmp;  //进行开笔操作运算的临时存储
    Mat platesrc;   //经过定位后得到的切割后的车牌图片
    Mat seg_tmp;    //分割临时图像

    ~test();

    String DEFAULT_FILE = "/Users/zhangfeng/slns/LPR/resources/";

    static const int DEFAULT_GAUSSIANBLUR_SIZE = 5;
    static const int SOBEL_SCALE = 1;
    static const int SOBEL_DELTA = 0;
    static const int SOBEL_DDEPTH = CV_16S;
    static const int SOBEL_X_WEIGHT = 1;
    static const int SOBEL_Y_WEIGHT = 0;
    static const int DEFAULT_MORPH_SIZE_WIDTH = 17;  // 17
    static const int DEFAULT_MORPH_SIZE_HEIGHT = 3;  // 3

    static const int WIDTH = 136;
    static const int HEIGHT = 36;
    static const int TYPE = CV_8UC3;


    static const int DEFAULT_VERIFY_MIN = 1;   // 3
    static const int DEFAULT_VERIFY_MAX = 24;  // 20

    static const int DEFAULT_ANGLE = 60;  // 30


    static const int DEFAULT_DEBUG = 1;

private:
    Ui::test *ui;

public slots:
    void clearTempFiles(const QString& temp_path);
    void show3(Mat src, QImage::Format format,bool bgr=false);
    void show4(Mat src, QImage::Format format,bool bgr=false);
    void ReleaseClicked();

    void PressClicked();

    void ReleaseClicked_1();

    void PressClicked_1();

    //void trigerMenu(QAction *act);

    void pre_Gaussian();
    void pre_gray();
    void pre_sobel();
    void pre_Roberts();
    void pre_Prewitt();
    void pre_binary();
    void pre_open();
    void pre_close();
    void pre_lunkuo();
    void pre_change();
    void pre_normal();

    void test_locate();
    void test_judge();
    void test_detect();
    void test_segment();
    void test_identify();
    void test_recognise();
    void act_recognise();

    void train_svm();
    void train_ann();
    void train_ch();
    void train_genchar();

    void locate_color();
    void locate_morph();
    void locate_judge();

    void segment_test();
    void segment_gray();
    void segment_binary();
    void segment_clearMaoDing();
    void segment_lunkuo();
    void segment_waijie();
    void segment_roi();
    void detect_test();

    void test_all();
};

#endif // TEST_H
