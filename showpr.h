#ifndef SHOWPR_H
#define SHOWPR_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QProcess>
#include <QString>
#include <QDateTime>
#include "logolabel.h"
#include <QApplication>
#include <iostream>
#include "include/easypr.h"
#include "include/easypr/util/switch.hpp"
#include "include/easypr/core/plate.hpp"
#include <QDir>
#include <QFileDialog>
#include <QStringList>
#include <QDateTime>
#include "thirdparty/xmlParser/xmlParser.h"
#include "include/easypr/util/kv.h"
#include "include/easypr/util/util.h"
#include "test/config.hpp"
#include "test/result.hpp"
#include <QDebug>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <numeric>
#include <unordered_map>
#include "include/easypr/core/core_func.h"
#include "include/easypr/core/params.h"
#include <QMenu>
#include <QMenuBar>


namespace Ui {
class showpr;
}

class showpr : public QMainWindow
{
    Q_OBJECT

public:
    explicit showpr(QWidget *parent = 0);

    char* DEFAULT_TEST_FILE = "/Users/zhangfeng/slns/LPR/resources/image/general_test";
    //char* DEFAULT_TEST_FILE = "/Users/zhangfeng/Desktop/show";
    ~showpr();

private:
    Ui::showpr *ui;
    QString dirs;
    QDateTime time;
    QAction* accTest;
    QMenu* testMenu;
    QMenuBar* menuBar;
    int num_now;
    QString dir;
    int num_cliked;
    easypr::Result res;

public slots:
    void ReleaseClicked();

    void PressClicked();

    void ReleaseClicked_8();

    void PressClicked_8();

    void ReleaseClicked_6();

    void PressClicked_6();

    void ReleaseClicked_7();

    void PressClicked_7();

    void Resnigez(QString targ_dir);

    void ListRowNum(int);

    int getGroundTruth(map<string, vector<easypr::CPlate>>& xmlMap, const char* path);
    void accuracyTest();
private slots:
    void on_listWidget_clicked(const QModelIndex &index);
};

#endif // SHOWPR_H
