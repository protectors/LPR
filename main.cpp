#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("车牌识别系统"));
    w.show();

//    selectwindow w;
//    w.setWindowTitle(QString("车牌识别模式选择"));
//    w.show();


//    test w;
//    w.setWindowTitle(QString("车牌识别调试模式"));
//    w.show();

//    showpr w;
//    w.setWindowTitle(QString("车牌识别演示模式"));
//    w.show();
    return a.exec();
}


//#include"opencv2/core/core.hpp"
//#include"opencv2/highgui/highgui.hpp"
//#include"easypr.h"
//using namespace cv;
//using namespace easypr;
//int main(int argc, char *argv[])
//{
//   cv::Mat image=cv::imread("/Users/zhangfeng/Pictures/feng.jpg");

//   cv::namedWindow("aaa");

//   cv::imshow("myimage",image);

//   cv::waitKey(50000);

//    return 0;
//}


//#include "include/easypr.h"
//#include "include/easypr/util/switch.hpp"

//#include "test/accuracy.hpp"
//#include "test/chars.hpp"
//#include "test/plate.hpp"


//namespace easypr {

//    namespace demo {

//    // interactions

//    int accuracyTestMain() {
//      std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
//      kv->load("/Users/zhangfeng/slns/LPR/resources/text/chinese_mapping");

//      bool isExit = false;
//      while (!isExit) {
//        easypr::Utils::print_file_lines("/Users/zhangfeng/slns/LPR/resources/text/batch_test_menu");
//        std::cout << kv->get("make_a_choice") << ":";

//        int select = -1;
//        bool isRepeat = true;
//        Result result;

//        while (isRepeat) {
//          std::cin >> select;
//          isRepeat = false;
//          switch (select) {
//          case 1:
//            accuracyTest("resources/image/general_test", result);
//            break;
//          case 2:
//            accuracyTest("resources/image/native_test", result);
//            break;
//          case 3:
//            gridSearchTest("resources/image/general_test");
//            break;
//          case 4:
//            isExit = true;
//            break;
//          default:
//            std::cout << kv->get("input_error") << ":";
//            isRepeat = true;
//            break;
//          }
//        }
//      }
//      return 0;
//    }

//    int trainChineseMain() {
//      std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
//      kv->load("/Users/zhangfeng/slns/LPR/resources/text/chinese_mapping");

//      bool isExit = false;
//      while (!isExit) {
//        easypr::Utils::print_file_lines("resources/text/train_menu");
//        std::cout << kv->get("make_a_choice") << ":";

//        int select = -1;
//        bool isRepeat = true;
//        while (isRepeat) {
//          std::cin >> select;
//          isRepeat = false;
//          switch (select) {
//          case 1:
//              {
//                easypr::AnnChTrain ann("tmp/annCh", "tmp/annCh.xml");
//                ann.setNumberForCount(100);
//                ann.train();
//              }
//            break;
//          case 2:
//              {
//                easypr::AnnChTrain ann("tmp/annCh", "tmp/annCh.xml");
//                ann.setNumberForCount(350);
//                ann.train();
//              }
//            break;
//          case 3:
//              {
//                easypr::AnnChTrain ann("tmp/annCh", "tmp/annCh.xml");
//                ann.setNumberForCount(700);
//                ann.train();
//              }
//            break;
//          case 4:
//              {
//                easypr::AnnChTrain ann("tmp/annCh", "tmp/annCh.xml");
//                ann.setNumberForCount(1000);
//                ann.train();
//              }
//            break;
//          case 5:
//              {
//                easypr::AnnChTrain ann("tmp/annCh", "tmp/annCh.xml");
//                ann.setNumberForCount(1500);
//                ann.train();
//              }
//            break;
//          case 6:
//            isExit = true;
//            break;
//          default:
//            std::cout << kv->get("input_error") << ":";
//            isRepeat = true;
//            break;
//          }
//        }
//      }
//      return 0;
//    }

//    int testMain() {
//      std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
//      kv->load("/Users/zhangfeng/slns/LPR/resources/text/chinese_mapping");

//      bool isExit = false;
//      while (!isExit) {
//        Utils::print_file_lines("/Users/zhangfeng/slns/LPR/resources/text/test_menu");
//        std::cout << kv->get("make_a_choice") << ":";

//        int select = -1;
//        bool isRepeat = true;
//        while (isRepeat) {
//          std::cin >> select;
//          isRepeat = false;
//          switch (select) {
//            case 1:
//              assert(test_plate_locate() == 0);
//              break;
//            case 2:
//              assert(test_plate_judge() == 0);
//              break;
//            case 3:
//              assert(test_plate_detect() == 0);
//              break;
//            case 4:
//              assert(test_chars_segment() == 0);
//              break;
//            case 5:
//              assert(test_chars_identify() == 0);
//              break;
//            case 6:
//              assert(test_chars_recognise() == 0);
//              break;
//            case 7:
//              assert(test_plate_recognize() == 0);
//              break;
//            case 8:
//              assert(test_plate_locate() == 0);
//              assert(test_plate_judge() == 0);
//              assert(test_plate_detect() == 0);

//              assert(test_chars_segment() == 0);
//              assert(test_chars_identify() == 0);
//              assert(test_chars_recognise() == 0);

//              assert(test_plate_recognize() == 0);
//              break;
//            case 9:
//              isExit = true;
//              break;
//            default:
//              std::cout << kv->get("input_error") << ":";
//              isRepeat = true;
//              break;
//          }
//        }
//      }

//      return 0;
//    }

//    }  // namespace demo

//}  // namespace easypr


//int main(int argc, const char* argv[]) {
//  std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
//  kv->load("/Users/zhangfeng/slns/LPR/resources/text/chinese_mapping");

//  if (argc > 1) {
//    // handle command line execution.
//    command_line_handler(argc, argv);
//    return 0;
//  }

//  bool isExit = false;
//  while (!isExit) {
//    easypr::Utils::print_file_lines("/Users/zhangfeng/slns/LPR/resources/text/test_menu");
//    std::cout << kv->get("make_a_choice") << ":";

//    int select = -1;
//    bool isRepeat = true;
//    while (isRepeat) {
//      std::cin >> select;
//      isRepeat = false;
//      switch (select) {
//        case 1:
//          easypr::demo::testMain();
//          break;
//        case 2:
//          easypr::demo::accuracyTestMain();
//          break;
//        case 3:
//          std::cout << "Run \"demo svm\" for more usage." << std::endl;
//          {
//            easypr::SvmTrain svm("tmp/svm", "tmp/svm.xml");
//            svm.train();
//          }
//          break;
//        case 4:
//          std::cout << "Run \"demo ann\" for more usage." << std::endl;
//          {
//            easypr::AnnTrain ann("tmp/ann", "tmp/ann.xml");
//            ann.train();
//          }
//          break;
//        case 5:
//          easypr::demo::trainChineseMain();
//          break;
//        case 6: {
//          //TODO: genenrate gray characters
//          easypr::demo::accuracyCharRecognizeTest("resources/image/tmp/plates_200k");
//          break;
//        }
//        case 7:
//          isExit = true;
//          break;
//        default:
//          std::cout << kv->get("input_error") << ":";
//          isRepeat = true;
//          break;
//      }
//    }
//  }
//  return 0;
//}


//int main(int argc, const char* argv[]) {
//	  std::shared_ptr<easypr::Kv> kv(new easypr::Kv);
//	  kv->load("resources/text/chinese_mapping");

//	  easypr::CPlateRecognize pr;
//	  pr.setResultShow(false);
//	  pr.setDetectType(easypr::PR_DETECT_CMSER);

//	  vector<easypr::CPlate> plateVec;
//	  Mat src = imread("D:\1.jpg");
//	  cv::imshow("test", src);
//	  int result = pr.plateRecognize(src, plateVec);
//	  std::cout << result << std::endl;
//	  return 0;
//	}
