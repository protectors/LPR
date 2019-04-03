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
#include <QDebug>
#include <QIODevice>
#include <QApplication>
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
    ~test();

private:
    Ui::test *ui;

public slots:
    void ReleaseClicked();

    void PressClicked();

    void ReleaseClicked_1();

    void PressClicked_1();

};

#endif // TEST_H
