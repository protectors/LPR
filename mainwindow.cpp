#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //时间
    mtimer = new QTimer;
    mpro = new QProcess;
    connect(mtimer,SIGNAL(timeout()),this,SLOT(up_time()));
    mtimer->start(1000);

    //窗口动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(40, -600, 100, 30));
    animation->setEndValue(QRect(40, 30, 100, 30));

    QPropertyAnimation *animations = new QPropertyAnimation(this, "windowOpacity");
    animations->setDuration(1000);
    animations->setStartValue(0);
    animations->setEndValue(1);
    animation->start();
    animations->start();

    //按钮动画————————旋转无敌转圈圈
    ui->clear->setImageSize(80,80);
    ui->clear->setQPixmapPath(":/new/prefix1/pictures/clear_off.png");
    ui->clear->setMagnify(false);
    ui->clear->setImageTransparency(255);

    ui->close->setImageSize(80,80);
    ui->close->setQPixmapPath(":/new/prefix1/pictures/close_off.png");
    ui->close->setMagnify(false);
    ui->close->setImageTransparency(255);

    ui->label_5->setImageSize(80,80);
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/go_off.png");
    ui->label_5->setMagnify(false);
    ui->label_5->setImageTransparency(255);

    connect(ui->clear, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked()));
    connect(ui->clear, SIGNAL(clicked()), this, SLOT(PressClicked()));
    connect(ui->close, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_8()));
    connect(ui->close, SIGNAL(clicked()), this, SLOT(PressClicked_8()));
    connect(ui->label_5, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_9()));
    connect(ui->label_5, SIGNAL(clicked()), this, SLOT(PressClicked_9()));

    ui->lineEdit->setText("zf");
    ui->lineEdit_2->setText("123");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*时间更新槽函数*/
void MainWindow::up_time()
{
    ui->label_4->setText(QTime::currentTime().toString("hh:mm"));
}

//清除按钮
void MainWindow::PressClicked(void)
{
    ui->clear->setQPixmapPath(":/new/prefix1/pictures/clear_on.png");
}
void MainWindow::ReleaseClicked(void)
{
    ui->clear->setQPixmapPath(":/new/prefix1/pictures/clear_off.png");
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

//关机按钮
void MainWindow::PressClicked_8(void)
{
    ui->close->setQPixmapPath(":/new/prefix1/pictures/close_on.png");
}
void MainWindow::ReleaseClicked_8(void)
{
    ui->close->setQPixmapPath(":/new/prefix1/pictures/close_off.png");
    int ret = QMessageBox::warning(this,"提示","是否真的要退出系统？",QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::Yes)
        this->close();
}

//登录按钮
void MainWindow::PressClicked_9(void)
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/go_on.png");
}
void MainWindow::ReleaseClicked_9(void)
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/go_off.png");

    QString user = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();

    /*判断账号密码是否正确*/
    if(user.isEmpty() || pass.isEmpty())
    {
        QMessageBox::warning(this,"提示","请输入账号或密码!",QMessageBox::Ok);
    }
    else if(user == "zf" && pass == "123")
    {
        w = new selectwindow(this);
        w->show();
        this->hide();
       // ui->lineEdit->clear();
       // ui->lineEdit_2->clear();
    }
    else
    {
        int ret = QMessageBox::warning(this,"提示","账号或密码错误，请重新输入!",QMessageBox::Ok);
        if(ret == QMessageBox::Ok)
        {
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
}
