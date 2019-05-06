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
    easypr::CPlate plate;
    Mat src;

    ~test();

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
