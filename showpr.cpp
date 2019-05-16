#include "showpr.h"
#include "ui_showpr.h"

using namespace easypr;
using namespace cv;
using namespace std;

showpr::showpr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::showpr)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("车牌识别演示部分"));

    accTest = new QAction("测试",this);
    testMenu = new QMenu("批量测试");
    testMenu->addAction(accTest);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(0,0,this->width(),23);//从左上角坐标开始，设置宽度，高度;设置菜单栏位置
    menuBar->addMenu(testMenu);
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

    ui->label_4->setImageSize(60,60);
    ui->label_4->setQPixmapPath(":/new/prefix1/pictures/start_off.png");
    ui->label_4->setRotate(false);
    ui->label_4->setMagnify(false);
    ui->label_4->setImageTransparency(255);

    ui->label_5->setImageSize(60,60);
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_off_s.png");
    ui->label_5->setRotate(false);
    ui->label_5->setMagnify(false);
    ui->label_5->setImageTransparency(255);

    ui->label_6->setImageSize(41,61);
    ui->label_6->setQPixmapPath(":/new/prefix1/pictures/l_off.png");
    ui->label_6->setRotate(false);
    ui->label_6->setMagnify(false);
    ui->label_6->setImageTransparency(255);

    ui->label_7->setImageSize(41,61);
    ui->label_7->setQPixmapPath(":/new/prefix1/pictures/r_off.png");
    ui->label_7->setRotate(false);
    ui->label_7->setMagnify(false);
    ui->label_7->setImageTransparency(255);

    connect(ui->label_4, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked()));
    connect(ui->label_4, SIGNAL(clicked()), this, SLOT(PressClicked()));
    connect(ui->label_5, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_8()));
    connect(ui->label_5, SIGNAL(clicked()), this, SLOT(PressClicked_8()));
    connect(ui->label_6, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_6()));
    connect(ui->label_6, SIGNAL(clicked()), this, SLOT(PressClicked_6()));
    connect(ui->label_7, SIGNAL(rmclicked()), this, SLOT(ReleaseClicked_7()));
    connect(ui->label_7, SIGNAL(clicked()), this, SLOT(PressClicked_7()));

    connect(accTest,SIGNAL(triggered()),this,SLOT(accuracyTest()));

    ui->label_6->setEnabled(false);
    ui->label_7->setEnabled(false);

    //获取listWidget 的当前行行号
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(ListRowNum(int)));
}

showpr::~showpr()
{
    delete ui;
}

//开始按钮
void showpr::PressClicked(void)
{
    ui->label_4->setQPixmapPath(":/new/prefix1/pictures/start_on.png");
}
void showpr::ReleaseClicked(void)
{
    ui->label_4->setQPixmapPath(":/new/prefix1/pictures/start_off.png");

    //获取文件路径
    dir = QFileDialog::getExistingDirectory(this);
    if(dir.isEmpty())
        return;
    //过滤文件并显示在列表中
    QDir Dir(dir);
    QStringList filter;  //过滤器
    filter<<"*.png"<<"*.jpg";
    QStringList files = Dir.entryList(filter);
    if(files.isEmpty())
        return;
    ui->label_6->setEnabled(true);
    ui->label_7->setEnabled(true);
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget->addItems(files);
    ui->listWidget->setCurrentRow(0);
    //识别列表第一个
    dirs = dir;
    dirs.append("/");
    dirs.append(ui->listWidget->item(0)->text());
    Resnigez(dirs);
    num_now = 0;
}

//返回按钮
void showpr::PressClicked_8(void)
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_on_s.png");
}
void showpr::ReleaseClicked_8(void)
{
    ui->label_5->setQPixmapPath(":/new/prefix1/pictures/back_off_s.png");
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

//上一张图片按钮
void showpr::PressClicked_6(void)
{
    ui->label_6->setQPixmapPath(":/new/prefix1/pictures/l_on.png");
}
void showpr::ReleaseClicked_6(void)
{
    ui->label_6->setQPixmapPath(":/new/prefix1/pictures/l_off.png");
    int num;
    int num_up;
    num = ui->listWidget->count(); //获取图片数目
    //是否是第一个，是就跳到最后一个循环
    if(num_cliked == 0)
    {
        num_cliked = num;
        num_cliked--;
        num_up = num_cliked;
    }
    else
    {
        num_cliked--;
        num_up = num_cliked;
    }

    //进行车牌识别并显示
    dirs = dir;
    dirs.append("/");
    dirs.append(ui->listWidget->item(num_up)->text());
    Resnigez(dirs);
    ui->listWidget->setCurrentRow(num_cliked);
}

//下一张图片按钮
void showpr::PressClicked_7(void)
{
    ui->label_7->setQPixmapPath(":/new/prefix1/pictures/r_on.png");
}
void showpr::ReleaseClicked_7(void)
{
    ui->label_7->setQPixmapPath(":/new/prefix1/pictures/r_off.png");
    int num;
    int num_down;
    num = ui->listWidget->count(); //获取图片数目
    //是否是最后一个，是就跳到第一个循环
    if(num_cliked == (num-1))
    {
        num_cliked = 0;
        num_down = num_cliked;
    }
    else
    {
        num_cliked++;
        num_down = num_cliked;
    }

    //进行车牌识别并显示
    dirs = dir;
    dirs.append("/");
    dirs.append(ui->listWidget->item(num_down)->text());
    Resnigez(dirs);
    ui->listWidget->setCurrentRow(num_cliked);
}

//识别车牌函数
void showpr::Resnigez(QString targ_dir)
{
    String num_data;
    num_data = targ_dir.toStdString();

    //车牌读取
    CPlateRecognize pr;
    pr.setDetectType(PR_DETECT_CMSER | PR_DETECT_COLOR);
    vector<CPlate> plateVec;
    Mat src = imread(num_data);
    pr.setLifemode(true);  //开启生活模式，增加鲁棒性
    pr.setMaxPlates(4);    //识别车牌数目
    int result = pr.plateRecognize(src, plateVec);
    if(result)
    {
        QMessageBox::warning(this,"错误","无法识别车牌信息，请重新输入图像！",QMessageBox::Yes);
        return;
    }
    pr.setResultShow(false);
    pr.getDetectShow();
    CPlate plate = plateVec.at(0);
    Mat plateMat = plate.getPlateMat();  //车牌截取图片读取
    string license = plate.getPlateStr();
    QString lice1 = QString::fromLocal8Bit(license.c_str());

    //图片显示
    cvtColor(src,src,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    QImage showImage((const uchar*)src.data,src.cols,src.rows,src.cols*src.channels(),QImage::Format_RGB888);
    ui->label_2->setPixmap(QPixmap::fromImage(showImage));

    //车牌截取显示
    cvtColor(plateMat,plateMat,CV_BGR2RGB);//opencv读取图片按照BGR方式读取，为了正常显示，所以将BGR转为RGB
    QImage showImage_1((const uchar*)plateMat.data,plateMat.cols,plateMat.rows,plateMat.cols*plateMat.channels(),QImage::Format_RGB888);
    ui->label_3->setPixmap(QPixmap::fromImage(showImage_1));

    //识别信息显示
    time = QDateTime::currentDateTime();
    ui->listWidget_2->addItem("识别结果："+lice1+"\n "+"\t"+time.toString("yyyy-MM-dd hh:mm:ss ddd"));
    ui->listWidget_2->scrollToBottom();
}

//获取当前行号
void showpr::ListRowNum(int num_now)
{
    qDebug() << "获取的行号：" << num_now;
    num_cliked = num_now;
}

//单击列表中的车牌
void showpr::on_listWidget_clicked(const QModelIndex &index)
{
    //进行车牌识别并显示
    ui->listWidget->setCurrentRow(num_cliked);
    dirs = dir;
    dirs.append("/");
    dirs.append(ui->listWidget->item(num_cliked)->text());
    Resnigez(dirs);
    ui->listWidget->setCurrentRow(num_cliked);
}

/******************************************************************************************************/
// get the groundTruth
int showpr::getGroundTruth(map<string, vector<CPlate>>& xmlMap, const char* path) {
  XMLNode::setGlobalOptions(XMLNode::char_encoding_UTF8);
  XMLNode xMainNode = XMLNode::openFileHelper(path, "tagset");
  const int n = xMainNode.nChildNode("image");
  // this prints the "coefficient" value for all the "NumericPredictor" tags:
  for (int i = 0; i < n; i++) {
    XMLNode imageNode = xMainNode.getChildNode("image", i);
    string imageName = imageNode.getChildNode("imageName").getText();

    vector<CPlate> plateVec;
    int m = imageNode.getChildNode("taggedRectangles").nChildNode("taggedRectangle");
    for (int j = 0; j < m; j++) {
      XMLNode plateNode = imageNode.getChildNode("taggedRectangles").getChildNode("taggedRectangle", j);

      int x = atoi(plateNode.getAttribute("x"));
      int y = atoi(plateNode.getAttribute("y"));
      int width = atoi(plateNode.getAttribute("width"));
      int height = atoi(plateNode.getAttribute("height"));
      int angle = atoi(plateNode.getAttribute("rotation"));

      string plateStr = plateNode.getText();
      if (width < height) {
        std::swap(width, height);
        angle = angle + 90;
      }

      RotatedRect rr(Point2f(float(x), float(y)), Size2f(float(width), float(height)), (float)angle);
      CPlate plate;
      plate.setPlateStr(plateStr);
      plate.setPlatePos(rr);
      plateVec.push_back(plate);
    }
    xmlMap[imageName] = plateVec;
  }
  return 0;
}

bool nature_sort_file(const std::string& f1, const std::string& f2) {
  std::string file1 = Utils::getFileName(f1);
  std::string file2 = Utils::getFileName(f2);

  std::size_t found1 = file1.find_last_of("_");
  std::size_t found2 = file2.find_last_of("_");

  int index1 = atoi(file1.substr(found1 + 1).c_str());
  int index2 = atoi(file2.substr(found2 + 1).c_str());
  return index1 < index2;
}
//批量测试
void showpr::accuracyTest() {
    char* test_path=DEFAULT_TEST_FILE;

    bool useParams=true;
    // find the right gt file for the platform
    string gtfile_postfix = "";

    XMLNode::setGlobalOptions(XMLNode::char_encoding_UTF8);
    gtfile_postfix = "_others";

    // result xml
    XMLNode xMainNode = XMLNode::createXMLTopNode("tagset");
    std::string path_result = "/Users/zhangfeng/slns/LPR/resources/result/Result.xml";

    // find text mapping, for compatiable withe utf-8 and GBK
    std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
    kv->load("/Users/zhangfeng/slns/LPR/resources/text/chinese_mapping");

    // find groundTruth, for compatiable withe utf-8(Linux/Mac) and GBK(Windows)
    map<string, vector<CPlate>> xmlMap;
    string path(test_path);
    path = path + "/GroundTruth" + gtfile_postfix + ".xml";
    getGroundTruth(xmlMap, path.c_str());

    // parameters
    const bool filesNatureSort = true;
    const int max_plates = 4;
    const int isGenerateGT = 1;

    // set the parameters of CPlateRecognize
    CPlateRecognize pr;
    pr.setResultShow(false);
    pr.setLifemode(true);
    pr.setDetectType(PR_DETECT_COLOR | PR_DETECT_CMSER);
    pr.setMaxPlates(4);

    // load the maching learning model
    pr.LoadSVM("/Users/zhangfeng/slns/LPR/model/svm_hist.xml");
    pr.LoadANN("/Users/zhangfeng/slns/LPR/model/ann.xml");
    pr.LoadChineseANN("/Users/zhangfeng/slns/LPR/model/ann_chinese.xml");

    pr.LoadGrayChANN("/Users/zhangfeng/slns/LPR/model/annCh.xml");
    pr.LoadChineseMapping("/Users/zhangfeng/slns/LPR/model/province_mapping");

    // find all the test files (images)
    // then sort them by image index
    auto files = Utils::getFiles(test_path);
    if (filesNatureSort)
        std::sort(files.begin(), files.end(), nature_sort_file);

    int size = files.size();
    if (0 == size) {
        qDebug() << "No File Found in general_test/native_test!" << endl;
        return;
    }
    qDebug() << "Begin to test the easypr accuracy!" << endl;

    int count_all = 0;
    int count_err = 0;
    int count_nodetect = 0;
    int count_norecogn = 0;


    std::list<std::string> not_recognized_files;

    // all the ground-truth plates
    float all_plate_count = 0;

    // all the characters are right
    float non_error_count = 0;
    float non_error_rate = 0;

    // only one character is wrong
    float one_error_count = 0;
    float one_error_rate = 0;

    // chinese character is wrong
    float chinese_error_count = 0;
    float chinese_error_rate = 0;
    float chinese_precise_rate = 0;

    // calucate the detect precise and recall
    // use icdar 2003 evalution protoocal
    vector<float> icdar2003_recall_all;
    icdar2003_recall_all.reserve(size * max_plates);
    vector<float> icdar2003_precise_all;
    icdar2003_precise_all.reserve(size * max_plates);

    // use to generate the plate trainging data, for training end2end chars recognize model
    std::stringstream plate_ss(std::stringstream::in | std::stringstream::out);
    int batch_i = 3;
    int plate_out_i = 0;

    time_t begin, end;
    std::time(&begin);

    // use openmp to paraller process these test images
#pragma omp parallel for
    for (int i = 0; i < size; i++) {
        string filepath = files[i].c_str();
        Mat src = imread(filepath);
        if (!src.data) continue;

        // calucate the detect recall
        // use icdar 2003 evalution protoocal
        vector<float> icdar2003_recall;
        icdar2003_recall.reserve(max_plates);
        vector<float> icdar2003_precise;
        icdar2003_precise.reserve(max_plates);

        int all_plate_count_s = 0;
        int non_error_count_s = 0;
        int one_error_count_s = 0;
        int chinese_error_count_s = 0;
        int count_norecogn_s = 0;
        int count_nodetect_s = 0;

        std::stringstream img_ss(std::stringstream::in | std::stringstream::out);
        img_ss << "------------------" << endl;
        string imageName = Utils::getFileName(filepath);
        img_ss << kv->get("original_image") << ":" << imageName << endl;

        XMLNode xNode, rectangleNodes;
        if (isGenerateGT) {
            xNode = xMainNode.addChild("image");
            xNode.addChild("imageName").addText(imageName.c_str());
            rectangleNodes = xNode.addChild("taggedRectangles");
        }

        // get the ground truth and compare it with the detect list;
        vector<CPlate> plateVecGT;
        bool hasGroundTruth = true;
#pragma omp critical
        {
            map<string, vector<CPlate>>::iterator it;
            it = xmlMap.find(imageName);
            if (it != xmlMap.end()) {
                plateVecGT = it->second;
            }
            else {
                hasGroundTruth = false;
                img_ss << "No ground truth found!" << endl;
            }
        }

        // core method, detect and recognize the plates
        vector<CPlate> plateVec;
        int result = pr.plateRecognize(src, plateVec, i);

        // calucate the detect recall
        // use icdar 2003 evalution protoocal
        for (auto plate_g : plateVecGT) {
            // if isGenerateG, then writes the text string of plate license
            XMLNode rectangleNode = rectangleNodes.addChild("taggedRectangle");
            if (isGenerateGT) {
                RotatedRect rr = plate_g.getPlatePos();
                rectangleNode.addAttribute("x", to_string((int)rr.center.x).c_str());
                rectangleNode.addAttribute("y", to_string((int)rr.center.y).c_str());
                rectangleNode.addAttribute("width", to_string((int)rr.size.width).c_str());
                rectangleNode.addAttribute("height", to_string((int)rr.size.height).c_str());
                rectangleNode.addAttribute("rotation", to_string((int)rr.angle).c_str());
                std::string plateDefault = "蓝牌:苏A88888";

                rectangleNode.addText(plateDefault.c_str());
            }

            float bestmatch = 0.f;
            CPlate* matchPlate = NULL;

            RotatedRect platePos_g = plate_g.getPlatePos();
            Rect_<float> plateRect_g;
            calcSafeRect(platePos_g, src, plateRect_g);

            size_t t = 0;
            for (CPlate plate_d : plateVec) {
                RotatedRect platePos_d = plate_d.getPlatePos();
                Rect_<float> plateRect_d;
                calcSafeRect(platePos_d, src, plateRect_d);

                Rect interRect = plateRect_g & plateRect_d;
                float match = 2 * (interRect.area()) / (plateRect_g.area() + plateRect_d.area());
                if (match - bestmatch > 0.1f) {
                    bestmatch = match;
                    matchPlate = &(plateVec.at(t));
                }
                t++;
            }

            icdar2003_recall.push_back(bestmatch);
            string plateLicense = plate_g.getPlateStr();
            string license = Utils::splitString(plateLicense, ':').at(1);
            img_ss << plate_g.getPlateStr() << " (g)" << endl;
            all_plate_count_s++;

            // if bestmatch (IOU) > 0.5f then we consider is detected
            if (matchPlate && bestmatch > 0.5f) {
                string matchPlateLicense = matchPlate->getPlateStr();
                vector<string> spilt_plate = Utils::splitString(matchPlateLicense, ':');

                size_t size = spilt_plate.size();
                if (size == 2 && spilt_plate.at(1) != "") {
                    string matchLicense = spilt_plate.at(1);
                    // output the detected and matched plate
                    img_ss << matchPlateLicense << " (d)" << endl;

                    // if isGenerateG, then writes the text string of plate license
                    if (isGenerateGT) {
                        rectangleNode.updateText(matchPlate->getPlateStr().c_str());

                        // use to generate the plate trainging data, for training end2end chars recognize model
                        std::stringstream ss(std::stringstream::in | std::stringstream::out);
                        ss << "/Users/zhangfeng/slns/LPR/resources/image/tmp/plateMat/plate_" << batch_i << "_" << plate_out_i << ".jpg";
                        imwrite(ss.str(), matchPlate->getPlateMat());
                        plate_ss << "plate_" << batch_i << "_" << plate_out_i << ".jpg" << ":" << license << endl;
                        plate_out_i++;
                    }

                    int diff = easypr::utils::levenshtein_distance(license, matchLicense);
                    if (diff == 0) {
                        non_error_count_s++;
                        one_error_count_s++;
                    }
                    else if (diff == 1) {
                        one_error_count_s++;
                    }
                    img_ss << kv->get("diff") << ":" << diff << kv->get("char");

                    bool chineseError = (license.substr(0, 2) != matchLicense.substr(0, 2));
                    if (chineseError) {
                        chinese_error_count_s++;
                        vector<CCharacter> charVec = matchPlate->getCopyOfReutCharacters();
                        CCharacter character = charVec.at(0);
                        if (1) {
                            std::stringstream ss(std::stringstream::in | std::stringstream::out);
                            ss << "/Users/zhangfeng/slns/LPR/resources/image/tmp/chinese" << "/" << i << "_" << t << "_" << matchPlate->getChineseKey() << ".jpg";
                            imwrite(ss.str(), matchPlate->getChineseMat());
                        }
                    }
                    img_ss << "  chineseError:" << chineseError << endl;
                }
                else {
                    img_ss << "No string" << " (d)" << endl;
                    count_norecogn_s++;
                }
            }
            else {
                img_ss << kv->get("empty_plate") << endl;
                if (license != kv->get("empty_plate")) {
                    not_recognized_files.push_back(license);
                    count_nodetect_s++;
                }
            }
        }

        // calucate the detect precise
        // use icdar 2003 evalution protoocal
        for (auto plate_d : plateVec) {
            float bestmatch = 0.f;

            RotatedRect platePos_d = plate_d.getPlatePos();
            Rect_<float> plateRect_d;
            calcSafeRect(platePos_d, src, plateRect_d);

            if (!hasGroundTruth) {
                string detectPlateLicense = plate_d.getPlateStr();
                vector<string> spilt_plate = Utils::splitString(detectPlateLicense, ':');

                size_t size = spilt_plate.size();
                if (size == 2 && spilt_plate.at(1) != "") {
                    img_ss << detectPlateLicense << " (d)" << endl;
                }
            }

            for (auto plate_g : plateVecGT) {
                RotatedRect platePos_g = plate_g.getPlatePos();
                Rect_<float> plateRect_g;
                calcSafeRect(platePos_g, src, plateRect_g);

                Rect interRect = plateRect_g & plateRect_d;
                float match = 2 * (interRect.area()) / (plateRect_g.area() + plateRect_d.area());
                if (match > bestmatch)
                    bestmatch = match;
            }
            icdar2003_precise.push_back(bestmatch);
        }

        double recall_result = 0;
        if (icdar2003_recall.size() > 0) {
            recall_result = std::accumulate(icdar2003_recall.begin(),
                                            icdar2003_recall.end(), 0.0) / (double)icdar2003_recall.size();
        }

        double precise_result = 0;
        if (icdar2003_precise.size() > 0) {
            precise_result = std::accumulate(icdar2003_precise.begin(),
                                             icdar2003_precise.end(), 0.0) / (double)icdar2003_precise.size();
        }

        double fscore_result = 0;
        if (recall_result + precise_result != 0) {
            fscore_result = 2 * (recall_result * precise_result) /
                    (recall_result + precise_result);
        }

        img_ss << "Recall" << ":" << recall_result * 100 << "%" << ", ";
        img_ss << "Precise" << ":" << precise_result * 100 << "%" << ", ";
        img_ss << "Fscore" << ":" << fscore_result * 100 << "%" << "." << endl;

#pragma omp critical
        {
            qDebug() << QString::fromStdString(img_ss.str());
        }
#pragma omp critical
        {
            for (auto recall : icdar2003_recall)
                icdar2003_recall_all.push_back(recall);

            for (auto precise : icdar2003_precise)
                icdar2003_precise_all.push_back(precise);
        }
#pragma omp critical
        {
            all_plate_count += all_plate_count_s;
            non_error_count += non_error_count_s;
            one_error_count += one_error_count_s;
            chinese_error_count += chinese_error_count_s;
            count_norecogn += count_norecogn_s;
            count_nodetect += count_nodetect_s;
            count_all++;
        }
    }
    std::time(&end);

    if (isGenerateGT) {
        //the xml detection result
        xMainNode.writeToFile(path_result.c_str());
    }

    qDebug() << "------------------" << endl;
    qDebug() << "Easypr accuracy test end!" << endl;
    qDebug() << "------------------" << endl;
    qDebug() << endl;
    qDebug() << QString::fromStdString(kv->get("summaries")) << ":" << endl;
    qDebug() << QString::fromStdString(kv->get("sum_pictures")) << ": " << count_all << ",  ";
    qDebug() << "Plates count" << ":" << all_plate_count << ",  ";

    float count_detect = float(all_plate_count - count_nodetect);
    float count_rate = count_detect / all_plate_count;
    qDebug() << QString::fromStdString(kv->get("locate_rate")) << ":" << count_rate * 100 << "%  " << endl;

    float count_recogin = float(count_detect - count_norecogn);

    if (count_recogin > 0) {
        non_error_rate = non_error_count / count_recogin;
        one_error_rate = one_error_count / count_recogin;
        chinese_error_rate = chinese_error_count / count_recogin;
        chinese_precise_rate = (count_recogin - chinese_error_count) / count_recogin;
    }

    double recall_2003_result = 0;
    if (icdar2003_recall_all.size() > 0) {
        recall_2003_result = std::accumulate(icdar2003_recall_all.begin(),
                                             icdar2003_recall_all.end(), 0.0) / (double)icdar2003_recall_all.size();
    }

    double precise_2003_result = 0;
    if (icdar2003_precise_all.size() > 0) {
        precise_2003_result = std::accumulate(icdar2003_precise_all.begin(),
                                              icdar2003_precise_all.end(), 0.0) / (double)icdar2003_precise_all.size();
    }

    double fscore_2003_result = 0;
    if (recall_2003_result + precise_2003_result != 0) {
        fscore_2003_result = 2 * (recall_2003_result * precise_2003_result) /
                (recall_2003_result + precise_2003_result);
    }

    //qDebug() << "Detect quality evalution result:" << endl;
    qDebug() << QString::fromStdString(kv->get("detect_quality"))  << ": ";
    qDebug() << "Recall" << "," << recall_2003_result * 100 << "%" << "; ";
    qDebug() << "Precise" << "," << precise_2003_result * 100 << "%" << "; ";
    qDebug() << "Fscore" << "," << fscore_2003_result * 100 << "%" << ";" << endl;

    qDebug() << QString::fromStdString(kv->get("char_recongize"))  << ": ";
    //qDebug() << "Recongtion rate:" << "," << (count_recogin / count_detect) * 100 << "%;  " << endl;
    qDebug() << "0-error" << "," << non_error_rate * 100 << "%;  ";
    qDebug() << "1-error" << "," << one_error_rate * 100 << "%;  ";
    qDebug() << "Chinese-precise" << "," << chinese_precise_rate * 100 << "%  " << endl;

    double seconds = difftime(end, begin);
    double avgsec = seconds / double(count_all);

    qDebug() << QString::fromStdString(kv->get("seconds"))  << ": " << seconds << QString::fromStdString(kv->get("sec"))  << ",  ";
    qDebug() << QString::fromStdString(kv->get("seconds_average"))  << ":" << avgsec << QString::fromStdString(kv->get("sec"))  << endl;

    // set the result.
    if (useParams) {
        res.setPicturesCount(count_all);
        res.setPlatesCount((int)all_plate_count);
        res.setDetectRate((float)count_rate * 100);

        res.setDetectRecall((float)recall_2003_result * 100);
        res.setDetectPrecise((float)precise_2003_result * 100);
        res.setDetectFscore((float)fscore_2003_result * 100);

        res.setZeroError((float)non_error_rate * 100);
        res.setOneError((float)one_error_rate * 100);
        res.setChinesePreciese((float)(1 - chinese_error_rate) * 100);

        res.setSeconds((float)seconds);
        res.setAvgSeconds((float)avgsec);
    }

    qDebug() << "------------------" << endl;

    ofstream myfile("/Users/zhangfeng/slns/LPR/resources/result/accuracy.txt", ios::app);
    if (myfile.is_open()) {
        std::time_t t = std::time(0);  // get time now
        struct tm* now = localtime(&t);
        char buf[80];

        strftime(buf, sizeof(buf), "%Y-%m-%d %X", now);
        myfile << string(buf) << endl;

        myfile << kv->get("sum_pictures") << ":" << count_all << ",  ";
        myfile << "Plates count" << ":" << all_plate_count << ",  ";
        myfile << kv->get("unrecognized") << ":" << count_nodetect << ",  ";
        myfile << kv->get("locate_rate") << ":" << count_rate * 100 << "%  "
               << endl;

        myfile << "Recall" << ":" << recall_2003_result * 100 << "%" << ", ";
        myfile << "Precise" << ":" << precise_2003_result * 100 << "%" << ", ";
        myfile << "Fscore" << ":" << fscore_2003_result * 100 << "%" << "." << endl;

        myfile << "0-error" << ":" << non_error_rate * 100 << "%,  ";
        myfile << "1-error" << ":" << one_error_rate * 100 << "%,  ";
        myfile << "Chinese-precise" << ":" << chinese_precise_rate * 100 << "%  " << endl;

        myfile << kv->get("seconds") << ": " << seconds << kv->get("sec") << ",  ";
        myfile << kv->get("seconds_average") << ":" << avgsec << kv->get("sec") << endl;
        myfile.close();
    }
    else {
        qDebug() << "Unable to open file";
    }

    // use to generate the plate trainging data, for training end2end chars recognize model
    if(isGenerateGT) {
        ofstream myfile("/Users/zhangfeng/slns/LPR/resources/result/plateGroundTruth.txt", ios::app);
        if (myfile.is_open()) {
            myfile << plate_ss.str();
            myfile.close();
        }
        else {
            qDebug() << "Unable to open file";
        }
    }

}

