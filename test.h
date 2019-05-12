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
#include <QStatusBar>
#include <iostream>
#include "include/easypr.h"
#include "include/easypr/util/switch.hpp"
#include "include/easypr/core/plate.hpp"


namespace Ui {
class test;
}

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    QMenu* menu[10];
    QAction* testact[20];
    QAction* trainact[20];
    QAction* preact[20];
    QMenuBar* menuBar ;
    QStatusBar* statusBar;

    String filename;
    easypr::CPlateRecognize pr;
    easypr::CPlateLocate pl;
    vector<easypr::CPlate> plateVec;
    vector<RotatedRect> outRects;
    easypr::CPlate plate;
    Mat src;
    Mat pre_tmp;    //预处理的中间过程
    Mat pre_suanzi; //进行算子比对是使用的中间变量，用于存储处理灰度化的结果
    ~test();

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

};

#endif // TEST_H
