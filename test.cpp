#include "test.h"
#include "ui_test.h"
#include <cv.h>
#include <opencv2/opencv.hpp>

using namespace easypr;
using namespace cv;
using namespace std;

test::test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
     this->setWindowTitle(QString("车牌识别调试部分"));
        statusBar = new QStatusBar(this);
        menuBar = new QMenuBar(this);

        testact[0] = new QAction("车牌定位",this);
        testact[1] = new QAction("车牌判断",this);
        testact[2] = new QAction("车牌检测",this);
        testact[3] = new QAction("字符分割",this);
        testact[4] = new QAction("字符鉴别",this);
        testact[5] = new QAction("字符识别",this);
        testact[6] = new QAction("车牌识别",this);

        trainact[0] = new QAction("SVM训练",this);
        trainact[1] = new QAction("ANN训练",this);
        trainact[2] = new QAction("中文字符训练",this);
        trainact[3] = new QAction("生成字符",this);

        preact[0] = new QAction("高斯模糊",this);
        preact[1] = new QAction("灰度化",this);

        preact[2] = new QAction("二值化",this);
        preact[3] = new QAction("闭操作",this);
        preact[4] = new QAction("取轮廓",this);
        preact[5] = new QAction("矩形旋转",this);
        preact[6] = new QAction("统一尺寸",this);
        preact[7] = new QAction("Sobel算子",this);
        preact[8] = new QAction("Roberts算子",this);
        preact[9] = new QAction("Prewitt算子",this);

        menu[0] = new QMenu("预处理");
        menu[0]->addAction(preact[0]);
        menu[0]->addAction(preact[1]);
        menu[3] = menu[0]->addMenu("形态学");
                menu[3]->addAction(preact[7]);
                menu[3]->addAction(preact[8]);
                menu[3]->addAction(preact[9]);
        menu[0]->addAction(preact[2]);
        menu[0]->addAction(preact[3]);
        menu[0]->addAction(preact[4]);
        menu[0]->addAction(preact[5]);
        menu[0]->addAction(preact[6]);
        //menu[0]->addAction(preact[7]);

        // menu[0]->addSeparator();//添加分割线
        menu[1] = new QMenu("测试");
        menu[1]->addAction(testact[0]);
        menu[1]->addAction(testact[1]);
        menu[1]->addAction(testact[2]);
        menu[1]->addAction(testact[3]);
        menu[1]->addAction(testact[4]);
        menu[1]->addAction(testact[5]);
        menu[1]->addAction(testact[6]);

        menu[2] = new QMenu("训练");
        menu[2]->addAction("车牌判断");
        menu[2]->addAction(trainact[0]);
        menu[2]->addAction(trainact[1]);
        menu[2]->addAction(trainact[2]);
        menu[2]->addAction(trainact[3]);

//        menu[3] = new QMenu("形态学");
//        menu[3]->addAction(preact[7]);
//        menu[3]->addAction(preact[8]);
//        menu[3]->addAction(preact[9]);

        //act[0][2] = new QAction("显示窗口",this);
        //act[0][2]->setCheckable(true);//设置checkbox

       // menu[2] = new QMenu("窗口");
       // menu[2]->addAction(act[0]);
       // menu[2]->addAction("关闭窗口");

       // menu[1]->addMenu(menu[2]);//添加菜单

        menuBar->setGeometry(0,0,this->width(),23);//从左上角坐标开始，设置宽度，高度;设置菜单栏位置
        menuBar->addMenu(menu[0]);
        menuBar->addMenu(menu[1]);

       // connect(menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));//对所有act点击事件有效，快捷键事件无效
        connect(preact[0] ,SIGNAL(triggered()),this,SLOT(pre_Gaussian()));
        connect(preact[1] ,SIGNAL(triggered()),this,SLOT(pre_gray()));

        connect(preact[2] ,SIGNAL(triggered()),this,SLOT(pre_binary()));
        connect(preact[3] ,SIGNAL(triggered()),this,SLOT(pre_close()));
        connect(preact[4] ,SIGNAL(triggered()),this,SLOT(pre_lunkuo()));
        connect(preact[5] ,SIGNAL(triggered()),this,SLOT(pre_change()));
        connect(preact[6] ,SIGNAL(triggered()),this,SLOT(pre_normal()));
        connect(preact[7] ,SIGNAL(triggered()),this,SLOT(pre_sobel()));
        connect(preact[8] ,SIGNAL(triggered()),this,SLOT(pre_Roberts()));
        connect(preact[9] ,SIGNAL(triggered()),this,SLOT(pre_Prewitt()));

        connect(testact[0] ,SIGNAL(triggered()),this,SLOT(test_locate()));
        connect(testact[1] ,SIGNAL(triggered()),this,SLOT(test_judge()));
        connect(testact[2] ,SIGNAL(triggered()),this,SLOT(test_detect()));
        connect(testact[3] ,SIGNAL(triggered()),this,SLOT(test_segment()));
        connect(testact[4] ,SIGNAL(triggered()),this,SLOT(test_identify()));
        connect(testact[5] ,SIGNAL(triggered()),this,SLOT(test_recognise()));
        connect(testact[6] ,SIGNAL(triggered()),this,SLOT(act_recognise()));

        connect(trainact[0] ,SIGNAL(triggered()),this,SLOT(train_svm()));
        connect(trainact[1] ,SIGNAL(triggered()),this,SLOT(train_ann()));
        connect(trainact[2] ,SIGNAL(triggered()),this,SLOT(train_ch()));
        connect(trainact[3] ,SIGNAL(triggered()),this,SLOT(train_genchar()));

        //connet(menuBar)

        statusBar->setGeometry(2,this->height()-30,this->width(),30);//设置状态栏位置


        //窗口动画
        QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
        animation->setDuration(1000);
        animation->setStartValue(QRect(2000, 30, 100, 30));
        animation->setEndValue(QRect(40, 30, 100, 30));

        QPropertyAnimation *animations = new QPropertyAnimation(this, "windowOpacity");
        animations->setDuration(1000);
        animations->setStartValue(0);
        animations->setEndValue(1);
        animation->start();
        animations->start();

        //按钮效果
        ui->label_5->setImageSize(80,80);
        ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_off.png");
        ui->label_5->setRotate(false);
        ui->label_5->setMagnify(false);
        ui->label_5->setImageTransparency(255);

        ui->label_6->setImageSize(101,31);
        ui->label_6->setQPixmapPath(":/new/prefix1/pictures/image_off.png");
        ui->label_6->setRotate(false);
        ui->label_6->setMagnify(false);
        ui->label_6->setImageTransparency(255);


        connect(ui->label_5, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked()));
        connect(ui->label_5, SIGNAL(clicked()), this, SLOT(PressClicked()));
        connect(ui->label_6, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_1()));
        connect(ui->label_6, SIGNAL(clicked()), this, SLOT(PressClicked_1()));


}


test::~test()
{
    delete ui;
}

void test::PressClicked()
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_on.png");
}
void test::ReleaseClicked()
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_off.png");
    this->parentWidget()->show();
    QPropertyAnimation *animation = new QPropertyAnimation(this->parentWidget(), "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(-1240, 25, 100, 30));
    animation->setEndValue(QRect(40, 25, 100, 30));

    QPropertyAnimation *animations = new QPropertyAnimation(this->parentWidget(), "windowOpacity");
    animations->setDuration(1000);
    animations->setStartValue(0);
    animations->setEndValue(1);
    animation->start();
    animations->start();
    this->close();
}

//打开目录并识别车牌
void test::PressClicked_1(void)
{
    ui->label_6->setQPixmapPath(":/new/prefix1/pictures/image_on.png");
}
void test::ReleaseClicked_1(void)
{
     ui->label_6->setQPixmapPath(":/new/prefix1/pictures/image_off.png");

     //目录字符串处理
     QString targ_dir = QFileDialog::getOpenFileName(this);
     if(targ_dir.isEmpty ())
         return;
     ui->lineEdit->setText(targ_dir);
//     String num_data;
     filename = targ_dir.toStdString();

     //车牌读取
//     CPlateRecognize pr;
     pr.setDetectType(PR_DETECT_CMSER | PR_DETECT_COLOR);
//     vector<CPlate> plateVec;
     src = imread(filename);
     pr.setLifemode(true);  //开启生活模式，增加鲁棒性
     pr.setMaxPlates(4);    //识别车牌数目
     int result = pr.plateRecognize(src, plateVec);
     if(result) {
         QMessageBox::warning(this,"错误","无法识别车牌信息，请重新输入图像！",QMessageBox::Yes);
         return;
     }
     pr.setResultShow(false);
     pr.getDetectShow();
     plate= plateVec.at(0);
     //图片显示
     cvtColor(src,src,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
     QImage showImage((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
     ui->label_2->setPixmap(QPixmap::fromImage(showImage));
     qDebug()<<"添加图片成功！";
     pre_tmp=src.clone();
     qDebug()<<"完成副本创建";
}

//test-车牌定位
void test::test_locate(){
    qDebug()<<"车牌定位";
    ui->label_3->clear();
    Mat src=imread(filename);
    vector<Mat> resultVec;
    int result=pl.plateLocate(src,resultVec);
    if(result==0){
        size_t num=resultVec.size();
        for(size_t j=0;j<num;j++){
            Mat resMat=resultVec[j];
            cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
            QImage showImage((const uchar*)resMat.data,resMat.cols,resMat.rows,resMat.cols*resMat.channels(),QImage::Format_RGB888);
            ui->label_3->setPixmap(QPixmap::fromImage(showImage));
        }
    }

}
//test-车牌判断
void test::test_judge(){
    qDebug()<<"车牌判断";
    ui->label_3->clear();
    Mat src=imread(filename);
    vector<Mat> matVec;
    vector<Mat> resVec;
    pl.setDebug(1);
    pl.setLifemode(true);
    int respl=pl.plateLocate(src,matVec);
    if(respl!=0){
        QMessageBox::warning(this,"错误","无法识别车牌信息，请重新输入图像！",QMessageBox::Yes);
        return;
    }
    size_t num=matVec.size();
    for(size_t j=0;j<num;j++){
        Mat resMat=matVec[j];
        cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
        QImage showImage((const uchar*)resMat.data,resMat.cols,resMat.rows,resMat.cols*resMat.channels(),QImage::Format_RGB888);
        ui->label_3->setPixmap(QPixmap::fromImage(showImage));
    }

//    int resJu=easypr::PlateJudge::instance()->plateJudge(matVec,resVec);
//    if(0!=resJu){
//        QMessageBox::warning(this,"错误","无法识别车牌信息，请重新输入图像！",QMessageBox::Yes);
//        return;
//    }
//    size_t num=matVec.size();
//    for(size_t j=0;j<num;j++){
//        Mat resMat=matVec[j];
//        cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
//        QImage showImage((const uchar*)resMat.data,resMat.cols,resMat.rows,resMat.cols*resMat.channels(),QImage::Format_RGB888);
//        ui->label_3->setPixmap(QPixmap::fromImage(showImage));
//    }
}


//test-车牌检测
void test::test_detect(){
    qDebug()<<"车牌检测";
    ui->label_3->clear();
    Mat src=imread(filename);
    vector<easypr::CPlate> resVec;
    easypr::CPlateDetect pd;
    pd.setPDLifemode(true);
    int result=pd.plateDetect(src,resVec);
    if(result==0){
        size_t num=resVec.size();
        for(size_t j=0;j<num;j++){
            easypr::CPlate res=resVec[j];
            Mat resMat=res.getPlateMat();
            cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
            QImage showImage((const uchar*)resMat.data,resMat.cols,resMat.rows,resMat.cols*resMat.channels(),QImage::Format_RGB888);
            ui->label_3->setPixmap(QPixmap::fromImage(showImage));
        }
    }
}
//test-字符分割
void test::test_segment(){
    qDebug()<<"字符分割";
    ui->label_3->clear();
    Mat src=imread(filename);
    vector<Mat> resultVec;
    easypr::CCharsSegment plate;
    int result=plate.charsSegment(src,resultVec);
    if(result==0){
        size_t num=resultVec.size();
        for(size_t j=0;j<num;j++){
            Mat resMat=resultVec[j];
            cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
            QImage showImage((const uchar*)resMat.data,resMat.cols,resMat.rows,resMat.cols*resMat.channels(),QImage::Format_RGB888);
            ui->label_3->setPixmap(QPixmap::fromImage(showImage));
        }
    }
}
//test-字符鉴别
void test::test_identify(){
    qDebug()<<"字符鉴别";
    ui->label_3->clear();
    Mat src=imread(filename);
    vector<Mat> matChars;
    string license;
    easypr::CCharsSegment cs;
    int result=cs.charsSegment(src,matChars);
    if(result==0){
        size_t num=matChars.size();
        for(size_t j=0;j<num;j++){
            auto block=matChars[j];
            if(j==0){
                auto chars=easypr::CharsIdentify::instance()->identify(block,true);
                license.append(chars.second);
            }
            else{
                auto chars=easypr::CharsIdentify::instance()->identify(block,false);
                license.append(chars.second);
            }
        }

        string platelicense="苏E771H6";
        QString s=QString::fromStdString(license);
        ui->label_3->setText(s);
        if(platelicense!=license){
            ui->label_4->setText("识别错误！");
        }
        else ui->label_4->setText("识别正确！");
    }
}
//test-字符识别
void test::test_recognise(){
    qDebug()<<"字符识别";
    ui->label_3->clear();
    Mat src=imread(filename);
    easypr::CPlateRecognize pr;
    pr.setLifemode(true);
    pr.setDebug(false);
    pr.setMaxPlates(1);
    pr.setDetectType(easypr::PR_DETECT_CMSER);

    vector<easypr::CPlate> plateVec;
    int result=pr.plateRecognize(src,plateVec);
    if(result==0){
        size_t num=plateVec.size();
        for(size_t j=0;j<num;j++){
            string res=plateVec[j].getPlateStr();
            QString s=QString::fromStdString(res);
            ui->label_3->setText(s);
        }
    }
    if(result!=0){
        QMessageBox::warning(this,"错误","无法识别车牌信息，请重新输入图像！",QMessageBox::Yes);
        return;
    }

}
//test-车牌识别
void test::act_recognise(){
    qDebug()<<"车牌识别";
    ui->label_3->clear();
    Mat plateMat = plate.getPlateMat();  //车牌截取图片读取
    string license = plate.getPlateStr();
    QString lice1 = QString::fromLocal8Bit(license.c_str());
     //车牌截取显示
     cvtColor(plateMat,plateMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
     QImage showImage_1((const uchar*)plateMat.data,plateMat.cols,plateMat.rows,plateMat.cols*plateMat.channels(),QImage::Format_RGB888);
     ui->label_3->setPixmap(QPixmap::fromImage(showImage_1));

     //识别信息显示
     ui->label_4->setText(lice1);

}
//train-SVM训练
void test::train_svm(){
    qDebug()<<"SVM";
}
//train-ANN训练
void test::train_ann(){
    qDebug()<<"ANN";
}
//train-中文字符训练
void test::train_ch(){
    qDebug()<<"中文字符";
}
//train-生成字符
void test::train_genchar(){
    qDebug()<<"生成字符";
}

/******************/
void test::pre_Gaussian(){
    qDebug()<<"高斯模糊";
    ui->label_3->clear();
    int blurSize=5;
    Mat pre_Gauss=pre_tmp.clone();
    GaussianBlur(pre_Gauss, pre_tmp, Size(blurSize, blurSize), 0, 0, BORDER_DEFAULT);
    cvtColor(pre_tmp,pre_tmp,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_RGB888);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
}
void test::pre_gray(){
    qDebug()<<"灰度化";
    Mat pre_gay=pre_tmp.clone();
    cvtColor(pre_gay, pre_tmp,CV_BGR2GRAY);
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
    pre_suanzi=pre_tmp;
}
void test::pre_sobel(){
    qDebug()<<"Sobel算子";
    ui->label_3->clear();
    Mat tmp=pre_suanzi.clone();
    int scale = SOBEL_SCALE;
    int delta = SOBEL_DELTA;
    int ddepth = SOBEL_DDEPTH;

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    Sobel(tmp, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    addWeighted(abs_grad_x, SOBEL_X_WEIGHT, 0, 0, 0, tmp);
    QImage showImage((const uchar*)tmp.data,tmp.cols,tmp.rows,tmp.cols*tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
    pre_tmp=tmp;
}
void test::pre_Roberts(){
    qDebug()<<"Roberts算子";
    ui->label_3->clear();
    Mat srcImage = pre_suanzi.clone();
    Mat dstImage = srcImage.clone();
    int nRows = dstImage.rows;
    int nCols = dstImage.cols;
    for (int i = 0; i < nRows - 1; i++){
        for (int j = 0; j < nCols - 1; j++){
            //根据公式计算
            int t1 = (srcImage.at<uchar>(i, j) -
                      srcImage.at<uchar>(i + 1, j + 1))*
                     (srcImage.at<uchar>(i, j) -
                      srcImage.at<uchar>(i + 1, j + 1));
            int t2 = (srcImage.at<uchar>(i+1, j) -
                      srcImage.at<uchar>(i , j + 1))*
                     (srcImage.at<uchar>(i+1, j) -
                      srcImage.at<uchar>(i , j + 1));
            //计算g（x,y）
            dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
        }
    }
    pre_tmp=dstImage;
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));

}
void test::pre_Prewitt(){
    qDebug()<<"Prewitt算子";
    ui->label_3->clear();
    Mat imageP=pre_suanzi.clone();
    float prewittx[9] =
    {
        -1,0,1,
        -1,0,1,
        -1,0,1
    };
    float prewitty[9] =
    {
        1,1,1,
        0,0,0,
        -1,-1,-1
    };
    Mat px=Mat(3,3,CV_32F,prewittx);
    cout<<px<<endl;
    Mat py=Mat(3,3,CV_32F,prewitty);
    cout<<py<<endl;
    Mat dstx=Mat(imageP.size(),imageP.type(),imageP.channels());
    Mat dsty=Mat(imageP.size(),imageP.type(),imageP.channels());
    Mat dst=Mat(imageP.size(),imageP.type(),imageP.channels());
    filter2D(imageP,dstx,imageP.depth(),px);
    filter2D(imageP,dsty,imageP.depth(),py);
    float tempx,tempy,temp;
    for(int i=0;i<imageP.rows;i++)
    {
        for(int j=0;j<imageP.cols;j++)
        {
            tempx=dstx.at<uchar>(i,j);
            tempy=dsty.at<uchar>(i,j);
            temp=sqrt(tempx*tempx+tempy*tempy);
            dst.at<uchar>(i,j)=temp;
        }
    }
    pre_tmp=dst;
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));

}
void test::pre_binary(){
    qDebug()<<"二值化";
    ui->label_3->clear();
    threshold(pre_tmp, pre_tmp, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
}
void test::pre_close(){
    qDebug()<<"闭操作";
    ui->label_3->clear();
    int morphW=17;
    int morphH=3;
    Mat element = getStructuringElement(MORPH_RECT, Size(morphW, morphH));
    morphologyEx(pre_tmp, pre_tmp, MORPH_CLOSE, element);
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_Indexed8);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
}
void test::pre_lunkuo(){
    qDebug()<<"取外轮廓";
    ui->label_3->clear();

    vector<vector<Point>> contours;
    findContours(pre_tmp,
                 contours,               // a vector of contours
                 CV_RETR_EXTERNAL,      //提取外部轮廓
                 CV_CHAIN_APPROX_NONE);  // all pixels of each contours

    vector<vector<Point>>::iterator itc = contours.begin();
    Mat image=src.clone();
    while (itc != contours.end()) {
      RotatedRect mr = minAreaRect(Mat(*itc));

      if (!pl.verifySizes(mr))
        itc = contours.erase(itc);
      else {
        ++itc;
        outRects.push_back(mr);
        Point2f v[4];
        mr.points(v);
        for (int i = 0; i < 4; i++)
            line(image, v[i], v[(i + 1) % 4], Scalar(0, 255, 0),2);
        cvtColor(image,image,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
        QImage showImage((const uchar*)image.data,image.cols,image.rows,image.cols*image.channels(),QImage::Format_RGB888);
        ui->label_3->setPixmap(QPixmap::fromImage(showImage));
      }
    }
}
void test::pre_change(){
    qDebug()<<"仿射变换";
    ui->label_3->clear();
    Mat img_rotated;

    RotatedRect minRect = outRects[1];
    if(pl.verifySizes(minRect)){
        float r = (float)minRect.size.width / (float)minRect.size.height;
        float angle = minRect.angle;
        Size rect_size = minRect.size;
        if (r < 1){
            angle = 90 + angle;
            swap(rect_size.width, rect_size.height);
        }
        Mat rotmat = getRotationMatrix2D(minRect.center, angle, 1);
        warpAffine(src, img_rotated, rotmat, src.size(), CV_INTER_CUBIC);
    }
    pre_tmp=img_rotated;
    cvtColor(pre_tmp,pre_tmp,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    QImage showImage((const uchar*)pre_tmp.data,pre_tmp.cols,pre_tmp.rows,pre_tmp.cols*pre_tmp.channels(),QImage::Format_RGB888);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));

}
void test::pre_normal(){
    qDebug()<<"归一化";
    ui->label_3->clear();
    Mat out;
    //getRectSubPix(src, Size(outRects[1].size.width, outRects[1].size.height),outRects[1].center, out);
    out=src;
    cvtColor(src,src,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    QImage showImage((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
}
