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

        testAct[0] = new QAction("车牌定位",this);
        testAct[1] = new QAction("车牌判断",this);
        testAct[2] = new QAction("车牌检测",this);
        testAct[3] = new QAction("字符分割",this);
        testAct[4] = new QAction("字符鉴别",this);
        testAct[5] = new QAction("字符识别",this);
        testAct[6] = new QAction("车牌识别",this);

        trainAct[0] = new QAction("SVM训练",this);
        trainAct[1] = new QAction("ANN训练",this);
        trainAct[2] = new QAction("中文字符训练",this);
        trainAct[3] = new QAction("生成字符",this);

        //预处理操作
        preAct[0] = new QAction("高斯模糊",this);
        preAct[1] = new QAction("灰度化",this);    //算子操作为789
        preAct[2] = new QAction("二值化",this);
        preAct[3] = new QAction("闭操作",this);    //开操作为10
        preAct[4] = new QAction("取轮廓",this);
        preAct[5] = new QAction("矩形旋转",this);
        preAct[6] = new QAction("统一尺寸",this);
        preAct[7] = new QAction("Sobel算子",this);
        preAct[8] = new QAction("Roberts算子",this);
        preAct[9] = new QAction("Prewitt算子",this);
        preAct[10] = new QAction("开操作",this);

        //定位操作
        locateAct[0] = new QAction("基于颜色定位",this);
        locateAct[1] = new QAction("基于形态学定位",this);
        locateAct[2] = new QAction("基于SVM判断车牌",this);

        //字符分割
        segmentAct[0] = new QAction("字符分割",this);
        segmentAct[1] = new QAction("灰度化",this);
        segmentAct[2] = new QAction("二值化",this);
        segmentAct[3] = new QAction("去铆钉",this);
        segmentAct[4] = new QAction("取轮廓",this);
        segmentAct[5] = new QAction("外界矩形",this);
        segmentAct[6] = new QAction("截取图块",this);

        //字符检测
        detectAct[0] = new QAction("字符识别",this);

        //test_all
        testall = new QAction("测试",this);

        preMenu = new QMenu("预处理");
        preMenu->addAction(preAct[0]);
        preMenu->addAction(preAct[1]);
        sobelMenu = preMenu->addMenu("算子运算");
            sobelMenu->addAction(preAct[7]);
            sobelMenu->addAction(preAct[8]);
            sobelMenu->addAction(preAct[9]);
        //preMenu->addAction(preAct[2]);

        preMenu->addAction(preAct[4]);
        //preMenu->addAction(preAct[5]);
        //preMenu->addAction(preAct[6]);

        // preMenu->addSeparator();//添加分割线

        locateMenu = new QMenu("车牌定位");
        locateMenu->addAction(locateAct[0]);
        morphMenu = locateMenu->addMenu("形态学");
            morphMenu->addAction(preAct[10]);   //open
            morphMenu->addAction(preAct[3]);    //close
            morphMenu->addAction(preAct[2]);
            morphMenu->addAction(locateAct[1]);
        locateMenu->addAction(locateAct[2]);

        segmentMenu = new QMenu("字符分割");
        segmentMenu->addAction(segmentAct[1]);
        segmentMenu->addAction(segmentAct[2]);
        segmentMenu->addAction(segmentAct[3]);
        segmentMenu->addAction(segmentAct[4]);
        segmentMenu->addAction(segmentAct[5]);
        segmentMenu->addAction(segmentAct[0]);


        detectMenu = new QMenu("字符识别");
        detectMenu->addAction(detectAct[0]);

        testallMenu = new QMenu("结果展示");
        testallMenu->addAction(testall);
        //act[0][2] = new QAction("显示窗口",this);
        //act[0][2]->setCheckable(true);//设置checkbox

       // locateMenu = new QMenu("窗口");
       // locateMenu->addAction(act[0]);
       // locateMenu->addAction("关闭窗口");

       // menu[1]->addMenu(locateMenu);//添加菜单

        menuBar->setGeometry(0,0,this->width(),23);//从左上角坐标开始，设置宽度，高度;设置菜单栏位置
        menuBar->addMenu(preMenu);
        //menuBar->addMenu(menu[1]);
        menuBar->addMenu(locateMenu);
        menuBar->addMenu(segmentMenu);
        //menuBar->addMenu(detectMenu);
        menuBar->addMenu(testallMenu);


       // connect(menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));//对所有act点击事件有效，快捷键事件无效
        connect(preAct[0] ,SIGNAL(triggered()),this,SLOT(pre_Gaussian()));
        connect(preAct[1] ,SIGNAL(triggered()),this,SLOT(pre_gray()));
            connect(preAct[7] ,SIGNAL(triggered()),this,SLOT(pre_sobel()));
            connect(preAct[8] ,SIGNAL(triggered()),this,SLOT(pre_Roberts()));
            connect(preAct[9] ,SIGNAL(triggered()),this,SLOT(pre_Prewitt()));
        connect(preAct[2] ,SIGNAL(triggered()),this,SLOT(pre_binary()));
            connect(preAct[10] ,SIGNAL(triggered()),this,SLOT(pre_open()));
            connect(preAct[3] ,SIGNAL(triggered()),this,SLOT(pre_close()));
        connect(preAct[4] ,SIGNAL(triggered()),this,SLOT(pre_lunkuo()));
        connect(preAct[5] ,SIGNAL(triggered()),this,SLOT(pre_change()));
        connect(preAct[6] ,SIGNAL(triggered()),this,SLOT(pre_normal()));

        connect(testAct[0] ,SIGNAL(triggered()),this,SLOT(test_locate()));
        connect(testAct[1] ,SIGNAL(triggered()),this,SLOT(test_judge()));
        connect(testAct[2] ,SIGNAL(triggered()),this,SLOT(test_detect()));
        connect(testAct[3] ,SIGNAL(triggered()),this,SLOT(test_segment()));
        connect(testAct[4] ,SIGNAL(triggered()),this,SLOT(test_identify()));
        connect(testAct[5] ,SIGNAL(triggered()),this,SLOT(test_recognise()));
        connect(testAct[6] ,SIGNAL(triggered()),this,SLOT(act_recognise()));

        connect(trainAct[0] ,SIGNAL(triggered()),this,SLOT(train_svm()));
        connect(trainAct[1] ,SIGNAL(triggered()),this,SLOT(train_ann()));
        connect(trainAct[2] ,SIGNAL(triggered()),this,SLOT(train_ch()));
        connect(trainAct[3] ,SIGNAL(triggered()),this,SLOT(train_genchar()));

        connect(locateAct[0] ,SIGNAL(triggered()),this,SLOT(locate_color()));
        connect(locateAct[1] ,SIGNAL(triggered()),this,SLOT(locate_morph()));
        connect(locateAct[2] ,SIGNAL(triggered()),this,SLOT(locate_judge()));

        connect(segmentAct[0] ,SIGNAL(triggered()),this,SLOT(segment_test()));
        connect(segmentAct[1] ,SIGNAL(triggered()),this,SLOT(segment_gray()));
        connect(segmentAct[2] ,SIGNAL(triggered()),this,SLOT(segment_binary()));
        connect(segmentAct[3] ,SIGNAL(triggered()),this,SLOT(segment_clearMaoDing()));
        connect(segmentAct[4] ,SIGNAL(triggered()),this,SLOT(segment_lunkuo()));
        connect(segmentAct[5] ,SIGNAL(triggered()),this,SLOT(segment_waijie()));
        connect(segmentAct[6] ,SIGNAL(triggered()),this,SLOT(segment_roi()));

        connect(detectAct[0] ,SIGNAL(triggered()),this,SLOT(detect_test()));

        connect(testall ,SIGNAL(triggered()),this,SLOT(test_all()));

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
     if(targ_dir.isEmpty ()){
         QMessageBox::warning(this,"错误","请重新输入图像！",QMessageBox::Yes);
         return;
     }
     ui->lineEdit->setText(targ_dir);
//     String num_data;
     filename = targ_dir.toStdString();
     //车牌读取
     //pr.setDetectType(PR_DETECT_CMSER | PR_DETECT_COLOR);
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
     qDebug()<<"添加图片成功！";
     pre_tmp=src.clone();
     pre_octmp=src.clone();
     qDebug()<<"完成副本创建";
     //图片显示
     Mat src_show=src.clone();
     cvtColor(src,src_show,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
     QImage showImage((const uchar*)src_show.data,src_show.cols,src_show.rows,src_show.cols*src_show.channels(),QImage::Format_RGB888);
     ui->label_2->setPixmap(QPixmap::fromImage(showImage));

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
            //imshow("test",resMat);
            waitKey(0);
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
    pl.setDebug(0);
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
    plate=plateVec.at(0);
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

/**********************************************************************************************************/
void test::clearTempFiles(const QString& temp_path)
{
    QDir dir(temp_path);
    if(dir.isEmpty())
    {
        return;
    }
    QStringList filter; //过滤器
    filter.append("*");
    QDirIterator it(temp_path, filter, QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext())//若容器中还有成员，继续执行删除操作
        dir.remove(it.next());
}
void test::show3(Mat tsrc, QImage::Format format,bool bgr){
    if(bgr){
        cvtColor(tsrc,src,CV_BGR2RGB);
    }
    QImage showImage((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),format);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage));
}
void test::show4(Mat tsrc, QImage::Format format,bool bgr){
    if(bgr){
        cvtColor(tsrc,src,CV_BGR2RGB);
    }
    QImage showImage((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),format);
    ui->label_4->setPixmap(QPixmap::fromImage(showImage));
}
void test::pre_Gaussian(){
    qDebug()<<"高斯模糊";
    ui->label_3->clear();
    int blurSize=3;
    Mat pre_Gauss=src.clone();
    GaussianBlur(pre_Gauss, pre_tmp, Size(blurSize, blurSize), 0, 0, BORDER_DEFAULT);
    cvtColor(pre_tmp,pre_tmp,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    show3(pre_tmp,QImage::Format_RGB888);
}
void test::pre_gray(){
    qDebug()<<"灰度化";
    Mat pre_gay=pre_tmp.clone();
    cvtColor(pre_gay, pre_tmp,CV_BGR2GRAY);
    show3(pre_tmp,QImage::Format_Indexed8);
    pre_suanzi=pre_tmp.clone(); //算子操作前进行备份
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
    show3(tmp,QImage::Format_Indexed8);
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
    show3(pre_tmp,QImage::Format_Indexed8);
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
    show3(pre_tmp,QImage::Format_Indexed8);
}
void test::pre_binary(){
    qDebug()<<"二值化";
    ui->label_3->clear();
    threshold(pre_tmp, pre_tmp, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
    show3(pre_tmp,QImage::Format_Indexed8);
    pre_octmp=pre_tmp.clone();  //开闭操作前的操作
}
void test::pre_open(){
    qDebug()<<"开操作";
    ui->label_3->clear();
    int morphW=17;
    int morphH=3;
    Mat tmp=pre_octmp.clone();
    Mat element = getStructuringElement(MORPH_RECT, Size(morphW, morphH));
    morphologyEx(pre_octmp,tmp, MORPH_OPEN, element);
    show3(tmp,QImage::Format_Indexed8);
    pre_tmp=tmp;
}
void test::pre_close(){
    qDebug()<<"闭操作";
    ui->label_3->clear();
    int morphW=17;
    int morphH=3;
    Mat tmp=pre_octmp.clone();
    Mat element = getStructuringElement(MORPH_RECT, Size(morphW, morphH));
    morphologyEx(pre_octmp, tmp, MORPH_CLOSE, element);
    show3(tmp,QImage::Format_Indexed8);
    pre_tmp=tmp;
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
        show3(image,QImage::Format_RGB888);
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

//车牌定位
void test::locate_morph(){
    qDebug()<<"形态学定位";
    ui->label_3->clear();
    plateVec.clear();
    String imgfile=DEFAULT_FILE+"/locate/locate_morph/";
    matVec.clear();

    Mat src=imread(filename);
    int result=pl.plateSobelLocate(src,plateVec);
    if(result==0){
        size_t num=plateVec.size();
        qDebug()<<"形态学定位----识别成功:"<<num;
        if(num==0) {
            QMessageBox::warning(this,"警告","未识别到车牌！",QMessageBox::Yes);
            return;
        }
        else{
            QMessageBox::warning(this,"警告",tr("成功识别到%1张车牌并保存至locate_morph!!").arg(num),QMessageBox::Yes);
            clearTempFiles(QString::fromStdString(imgfile));
        }
        if(num==1){
            Mat resMat=plateVec[0].getPlateMat();
            show3(resMat,QImage::Format_RGB888,true);
        }
        for(size_t j=0;j<num;j++){
            Mat resMat=plateVec[j].getPlateMat();
            //cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
            //show3(resMat,QImage::Format_RGB888);
            matVec.push_back(resMat);
            imgname=imgfile+to_string(j)+".jpg";
            imwrite(imgname,resMat);
        }
    }
}
void test::locate_color(){
    qDebug()<<"颜色学定位";
    ui->label_3->clear();
    plateVec.clear();
    String imgfile=DEFAULT_FILE+"/locate/locate_color/";
    matVec.clear();

    Mat src=imread(filename);
    int result=pl.plateColorLocate(src,plateVec);
    result=pl.plateMserLocate(src,plateVec);
    if(result==0){
        size_t num=plateVec.size();
        qDebug()<<"颜色学定位----识别成功:"<<num;
        if(num==0) {
            QMessageBox::warning(this,"警告","未识别到车牌！",QMessageBox::Yes);
            return;
        }
        else{
            QMessageBox::warning(this,"警告",tr("成功识别到%1张车牌并保存至locate_color!!").arg(num),QMessageBox::Yes);
            clearTempFiles(QString::fromStdString(imgfile));
        }
        if(num==1){
            Mat resMat=plateVec[0].getPlateMat();
            show3(resMat,QImage::Format_RGB888,true);
        }
        for(size_t j=0;j<num;j++){
            Mat resMat=plateVec[j].getPlateMat();
            matVec.push_back(resMat);
            //imshow("test",resMat);
            //cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
            //show3(resMat,QImage::Format_RGB888);
            imgname=DEFAULT_FILE+"/locate/locate_color/"+to_string(j)+".jpg";
            imwrite(imgname,resMat);
        }
    }
}
void test::locate_judge() {
    qDebug()<<"车牌判断";
    ui->label_3->clear();
    String imgfile=DEFAULT_FILE+"/locate/locate_judge/";
    if(matVec.size()==0){
        matVec.clear();
        Mat src=imread(filename);
        pl.setLifemode(true);
        pl.plateLocate(src,matVec);
    }
    int resultJu = PlateJudge::instance()->plateJudge(matVec,JudgeResultVec);
    if(resultJu==0){
        size_t num=JudgeResultVec.size();
        qDebug()<<"车牌定位----识别成功:"<<num;
        if(num==0) {
            QMessageBox::warning(this,"警告","未识别到车牌！",QMessageBox::Yes);
            return;
        }
        else{
            QMessageBox::warning(this,"警告",tr("成功识别到%1张车牌并保存至locate_judge!!").arg(num),QMessageBox::Yes);
            clearTempFiles(QString::fromStdString(imgfile));
        }
        if(num==1){
            Mat resMat=plateVec[0].getPlateMat();
            show3(resMat,QImage::Format_RGB888);
        }
        for(size_t j=0;j<num;j++){
            Mat resMat=JudgeResultVec[j];

            imgname=DEFAULT_FILE+"/locate/locate_judge/"+to_string(j)+".jpg";
            imwrite(imgname,resMat);
           // show4(resMat,QImage::Format_RGB888,true);
        }
    }

}

//字符分割
void test::segment_gray(){
    qDebug()<<"分割-灰度化";
    platesrc=imread("/Users/zhangfeng/slns/LPR/resources/locate/locate_judge/0.jpg");

    show3(platesrc,QImage::Format_RGB888,true);

    seg_tmp=platesrc.clone();
    cvtColor(seg_tmp, seg_tmp,CV_RGB2GRAY);
    show4(seg_tmp,QImage::Format_Indexed8);
}
void test::segment_binary(){
    qDebug()<<"分割-二值化";
    ui->label_4->clear();
    Mat img_threshold;
    img_threshold = seg_tmp.clone();
    spatial_ostu(img_threshold, 8, 2);
    show4(img_threshold,QImage::Format_Indexed8);
    seg_tmp=img_threshold;
}
void test::segment_clearMaoDing(){
    qDebug()<<"分割-去铆钉";
    int p=clearLiuDing(seg_tmp);
    show4(seg_tmp,QImage::Format_Indexed8);
}
void test::segment_lunkuo(){
    qDebug()<<"分割-取轮廓";
    CCharsSegment Cseg;
    Mat img_contours;
    seg_tmp.copyTo(img_contours);

    vector<vector<Point> > contours;
    findContours(img_contours,
                 contours,               // a vector of contours
                 CV_RETR_EXTERNAL,       // retrieve the external contours
                 CV_CHAIN_APPROX_NONE);  // all pixels of each contours

    vector<vector<Point> >::iterator itc = contours.begin();
    vector<Rect> vecRect;

    while (itc != contours.end()) {
        Rect mr = boundingRect(Mat(*itc));
        Mat auxRoi(seg_tmp, mr);

        if (Cseg.verifyCharSizes(auxRoi)==true) vecRect.push_back(mr);
        ++itc;
    }


    if (vecRect.size() == 0) return;

    vector<Rect> sortedRect(vecRect);
    std::sort(sortedRect.begin(), sortedRect.end(),
              [](const Rect& r1, const Rect& r2) { return r1.x < r2.x; });

    size_t specIndex = 0;

    specIndex = Cseg.GetSpecificRect(sortedRect);

    Rect chineseRect;
    if (specIndex < sortedRect.size())
        chineseRect = GetChineseRect(sortedRect[specIndex]);
    else return;



    rectangle(seg_tmp, chineseRect, Scalar(255));
    show4(seg_tmp,QImage::Format_Indexed8);

}
void test::segment_waijie(){
    qDebug()<<"分割-外接矩形";
}
void test::segment_roi(){
    qDebug()<<"分割-截取图块";
}

void test::segment_test(){
    qDebug()<<"分割测试";
    ui->label_3->clear();
    String imgfile=DEFAULT_FILE+"/segment/";
    //cv::Mat src = cv::imread("/Users/zhangfeng/slns/LPR/resources/locate/locate_judge/5.jpg");
    //Mat src=imread(filename);

    size_t JRVnum=JudgeResultVec.size();
    qDebug()<<"车牌分割----分割成功:"<<JRVnum;
    if(JRVnum==0) {
        QMessageBox::warning(this,"警告","未识别到车牌！",QMessageBox::Yes);
        return;
    }
    else{
        QMessageBox::warning(this,"警告","成功分割车牌并保存至segment!!",QMessageBox::Yes);
        clearTempFiles(QString::fromStdString(imgfile));
    }
    for(size_t i=0;i<JRVnum;i++){
        vector<Mat> resultVec;
        easypr::CCharsSegment plate;
        int result=plate.charsSegment(JudgeResultVec[i],resultVec);
        if(result==0){
            size_t num=resultVec.size();
            if(num>7) num=7;
            for(size_t j=0;j<num;j++){
                Mat resMat=resultVec[j];
                //cvtColor(resMat,resMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
                //show4(resMat,QImage::Format_RGB888);
                //imshow("test",resMat);
                imgname=DEFAULT_FILE+"segment/"+to_string(i)+"_"+to_string(j)+".jpg";
                imwrite(imgname,resMat);
            }
        }
        //in the i for
    }
}

void test::detect_test(){
    qDebug()<<"识别测试";
}

void test::test_all(){
    qDebug()<<"结果展示";
    ui->label_3->clear();
    size_t num=plateVec.size();
    if(num==1){
        qDebug()<<"结果展示--单车牌展示";
        plate=plateVec.at(0);
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
    else{
        qDebug()<<"结果展示--多车牌展示";
        //ui->label_4->setText("显示已保存至test_all");
        string platetext="";
        for(size_t j=0;j<num;j++){
            plate=plateVec.at(j);
            Mat plateMat = plate.getPlateMat();  //车牌截取图片读取
            string license = plate.getPlateStr()+'\n';
            platetext+=license;
        }
        QString lice= QString::fromLocal8Bit(platetext.c_str());
        //识别信息显示
        ui->label_3->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->label_3->setText(lice);
    }
}
