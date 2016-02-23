/*
 * Line2DImageTools_test.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: tiagotrocoli
 */

#include <string>

#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Line2DImageTools_test"
//VERY IMPORTANT - include this last

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/line2dtoolspackage/Line2DImageTools.h>
#include <TestTools.h>

//*******************************
// EXTRACT LINE2D FROM FOREGROUND
//*******************************

std::vector<Line2D> reduceVectorLine2DPrecision(std::vector<Line2D> vector,
                                                int precision = 3) {

  std::vector<Line2D> lines;
  for (uint64 j = 0; j < vector.size(); ++j) {
    cv::Point2d p1, p2;
    p1.x = TestTools::setDigits((vector[j].bottonPoint().x), 3);
    p1.y = TestTools::setDigits((vector[j].bottonPoint().y), 3);
    p2.x = TestTools::setDigits((vector[j].topPoint().x), 3);
    p2.y = TestTools::setDigits((vector[j].topPoint().y), 3);
    Line2D line(p1, p2);
    lines.push_back(line);
  }
  return lines;
}

std::vector<Line2D> extractLine2DFromForegroundGT() {

  std::vector<Line2D> vector_ground_truth = { Line2D(
      cv::Point2d(209.153, 507.74), cv::Point2d(164.107, 335.456)), Line2D(
      cv::Point2d(397.491, 163.577), cv::Point2d(397.746, 123.124)), Line2D(
      cv::Point2d(504.355, 172.357), cv::Point2d(505.777, 121.127)), Line2D(
      cv::Point2d(344.762, 148.146), cv::Point2d(339.655, 119.84)), Line2D(
      cv::Point2d(369.734, 163.843), cv::Point2d(376.917, 114.163)), Line2D(
      cv::Point2d(26.158, 271.657), cv::Point2d(22.204, 112.825)), Line2D(
      cv::Point2d(132.026, 196.576), cv::Point2d(121.467, 105.654)), Line2D(
      cv::Point2d(696.435, 545.242), cv::Point2d(639.709, 398.6)), Line2D(
      cv::Point2d(46.386, 405.003), cv::Point2d(39.884, 321.415)), Line2D(
      cv::Point2d(178.777, 366.744), cv::Point2d(166.449, 311.485)), Line2D(
      cv::Point2d(396.329, 373.562), cv::Point2d(412.882, 298.981)), Line2D(
      cv::Point2d(378.744, 315.884), cv::Point2d(364.901, 276.478)), Line2D(
      cv::Point2d(344.21, 295.087), cv::Point2d(336.356, 268.301)), Line2D(
      cv::Point2d(340.018, 495.152), cv::Point2d(343.654, 339.896)), Line2D(
      cv::Point2d(41.892, 363.732), cv::Point2d(34.123, 257.124)) };
  return vector_ground_truth;
}

BOOST_AUTO_TEST_CASE(extractLine2DFromForegroundTestCase) {

  int size_paths = 4;
  std::vector<std::string> paths(size_paths);
  paths[0] = BW_FOREGROUND_IMAGE_01;
  paths[1] = BW_FOREGROUND_IMAGE_02;
  paths[2] = BW_FOREGROUND_IMAGE_03;
  paths[3] = BW_FOREGROUND_IMAGE_04;

  std::vector<Line2D> vector, temp;
  std::string path = PATH_RELATIVE_ROOT_TESTBIN;
  std::string path_resource = LINE2D_RESOURCE_PATH;

  for (int i = 0; i < size_paths; ++i) {
    cv::Mat testImage = cv::imread(path + path_resource + paths[i],
                                   CV_LOAD_IMAGE_GRAYSCALE);
    testImage = testImage > 200;
    Line2DImageTools::extractLine2DFromForeground(testImage, &vector);
  }

  temp = reduceVectorLine2DPrecision(vector, 3);
  vector = extractLine2DFromForegroundGT();
  BOOST_CHECK_EQUAL_COLLECTIONS(temp.begin(), temp.end(), vector.begin(),
                                vector.end());
}

//*******************************
// EXTRACT LINE2D FROM BACKGROUND
//*******************************

void checkVectorLine2DBackground(std::string input_path,
                                 std::vector<Line2D> vector_gt) {

  std::vector<Line2D> vector, temp;
  std::string path = PATH_RELATIVE_ROOT_TESTBIN;
  std::string path_resource = LINE2D_RESOURCE_PATH;

  cv::Mat test_image = cv::imread(path + path_resource + input_path);
  Line2DImageTools::extractLine2DFromBackground(test_image, &vector);

  for (uint64 i = 0; i < 5; ++i) {
    cv::Point2d p1, p2;
    p1.x = TestTools::setDigits((vector[i].bottonPoint().x), 3);
    p1.y = TestTools::setDigits((vector[i].bottonPoint().y), 3);
    p2.x = TestTools::setDigits((vector[i].topPoint().x), 3);
    p2.y = TestTools::setDigits((vector[i].topPoint().y), 3);
    Line2D line(p1, p2);
    temp.push_back(line);
  }

  BOOST_CHECK_EQUAL_COLLECTIONS(temp.begin(), temp.begin() + 5,
                                vector_gt.begin(), vector_gt.end());
}

std::vector<std::vector<Line2D> > extractLine2DFromBackgroundGT() {

  std::vector<std::vector<Line2D> > vector_ground_truth(4);
  vector_ground_truth[0] = {Line2D(cv::Point2d(192.226, 414.253), cv::Point2d(185.401, 394.452)),
    Line2D(cv::Point2d(372.632, 386.803), cv::Point2d(368.866, 346.805)),
    Line2D(cv::Point2d(613.123, 425.886), cv::Point2d(488.133, 425.257)),
    Line2D(cv::Point2d(113.111, 436.791), cv::Point2d(131.766, 433.715)),
    Line2D(cv::Point2d(214.583, 420.816), cv::Point2d(225.779, 419.194))};

  vector_ground_truth[1] = {Line2D(cv::Point2d(426.641, 136.975), cv::Point2d(440.822, 134.096)),
    Line2D(cv::Point2d(445.6, 133.006), cv::Point2d(483.287, 125.152)),
    Line2D(cv::Point2d(606.894, 199.982), cv::Point2d(586.836, 199.37)),
    Line2D(cv::Point2d(576.621, 189.559), cv::Point2d(554.375, 185.623)),
    Line2D(cv::Point2d(611.748, 202.219), cv::Point2d(638.351, 198.492))};

  vector_ground_truth[2] = {Line2D(cv::Point2d(296.545, 282.035), cv::Point2d(324.374, 278.119)),
    Line2D(cv::Point2d(404.416, 145.068), cv::Point2d(389.405, 143.958)),
    Line2D(cv::Point2d(429.481, 236.896), cv::Point2d(430.547, 170.623)),
    Line2D(cv::Point2d(588.49, 203.141), cv::Point2d(590.338, 163.054)),
    Line2D(cv::Point2d(391.897, 160.755), cv::Point2d(393.182, 148.259))};

  vector_ground_truth[3] = {Line2D(cv::Point2d(380.119, 235.633), cv::Point2d(380.515, 200.623)),
    Line2D(cv::Point2d(379.472, 255.665), cv::Point2d(379.995, 238.106)),
    Line2D(cv::Point2d(379.351, 274.399), cv::Point2d(379.604, 261.879)),
    Line2D(cv::Point2d(384.126, 43.434), cv::Point2d(367.381, 29.993)),
    Line2D(cv::Point2d(284.324, 40.125), cv::Point2d(300.66, 38.478))};

  return vector_ground_truth;
}

BOOST_AUTO_TEST_CASE(extractLine2DFromBackgroundCaseTest) {

  std::vector<std::string> paths(4);
  paths[0] = BACKGROUND_IMAGE_01;
  paths[1] = BACKGROUND_IMAGE_02;
  paths[2] = BACKGROUND_IMAGE_03;
  paths[3] = BACKGROUND_IMAGE_04;

  std::vector<std::vector<Line2D> > vector_ground_truth;
  vector_ground_truth = extractLine2DFromBackgroundGT();

  for (uint i = 0; i < vector_ground_truth.size(); ++i) {
    checkVectorLine2DBackground(paths[i], vector_ground_truth[i]);
  }
}

//******************
// LINE2D HISTOGRAM
//******************

BOOST_AUTO_TEST_CASE(histogramAngleLine2DSimpleTestCase) {

    std::vector<Line2D> lines;
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(0, 1)));
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(1, 0)));
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(1, 1)));
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(0, 1)));
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(1, 0)));
    lines.push_back(Line2D(cv::Point2d(0, 0), cv::Point2d(1, 1)));

    std::vector<uint> out = Line2DImageTools::histogramAngleLine2D(lines, 18);
    std::vector<uint> gtOut = { 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 };

    BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(), out.end(), gtOut.begin(), gtOut.end());
}

BOOST_AUTO_TEST_CASE(histogramAngleLine2DTestCase) {

    std::vector<Line2D> lines;
    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
    std::string path_resource = LINE2D_RESOURCE_PATH;
    std::string input_path = BACKGROUND_IMAGE_01;
    uint stixel_total = 0;

    cv::Mat test_image = cv::imread(path + path_resource + input_path);
    Line2DImageTools::extractLine2DFromBackground(test_image, &lines);

    std::vector<uint> out = Line2DImageTools::histogramAngleLine2D(lines, 18);
    std::vector<uint> gt_out = { 119, 60, 17, 3, 4, 7, 6, 34, 327, 43, 3, 4, 2, 6, 4, 8, 39, 95 };

    stixel_total = lines.size();

    for (uint i = 0; i < out.size(); ++i)
        stixel_total -= out[i];

    BOOST_CHECK_EQUAL(0, stixel_total);
    BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(), out.end(), gt_out.begin(), gt_out.end());
}

//BOOST_AUTO_TEST_CASE(histogramAngleStixel2DDrawTestCase) {
//
//    std::vector<Stixel2D> stixeis1;
//    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
//    std::string path_resource = STIXEL_RESOURCE_PATH;
//    std::string inputPath = BACKGROUND_IMAGE_01;
//
////    cv::Mat testImage = cv::imread(path + path_resource + inputPath);
//
//    std::string tempPath = "/home/tiagotrocoli/Documents/Mestrado/datasets-tracking/pets_2007/S06-BAG_STEAL_2/3/";
//    std::string fileName = "BACKGROUND_FOR_PAPER.jpeg";
//    cv::Mat testImage = cv::imread(tempPath+fileName);
//    StixelTools::extractStixelFromBackground(testImage, &stixeis1);
//
////    cv::Mat gtImageHist10Beans = cv::imread(path + path_resource + "histAngleStixel2D10Beans.jpeg");
////    cv::Mat gtImageHist20Beans = cv::imread(path + path_resource + "histAngleStixel2D20Beans.jpeg");
////    cv::Mat gtImageHist180Beans = cv::imread(path + path_resource + "histAngleStixel2D180Beans.jpeg");
//
//    cv::Mat bigImage(300, 180*5, CV_8UC3);
//    std::string nameImage = "actualHistogram.jpeg";
//
//    StixelTools::histogramAngleStixel2D(stixeis1, 18, &bigImage);
//    cv::imshow("HIST 18", bigImage);
//    TestTools::writeImageJpeg(tempPath+"hist_18beans.jpg", bigImage);
////    TestTools::writeImageJpeg(nameImage, bigImage);
////    bigImage = cv::imread(nameImage);
//
////    cv::Scalar gtCheck = cv::sum(gtImageHist10Beans);
////    cv::Scalar outCheck = cv::sum(bigImage);
////
////    BOOST_CHECK_EQUAL(gtCheck, outCheck);
//
//    StixelTools::histogramAngleStixel2D(stixeis1, 20, &bigImage);
//    cv::imshow("HIST 20", bigImage);
//    TestTools::writeImageJpeg(tempPath+"hist_20beans.jpg", bigImage);
////    TestTools::writeImageJpeg(nameImage, bigImage);
////    bigImage = cv::imread(nameImage);
//
////    gtCheck = cv::sum(gtImageHist20Beans);
////    outCheck = cv::sum(bigImage);
////
////    BOOST_CHECK_EQUAL(gtCheck, outCheck);
//
//    StixelTools::histogramAngleStixel2D(stixeis1, 180, &bigImage);
//    cv::imshow("HIST 180", bigImage);
//    TestTools::writeImageJpeg(tempPath+"hist_180beans.jpg", bigImage);
//    cv::waitKey();
//    TestTools::writeImageJpeg(nameImage, bigImage);
//    bigImage = cv::imread(nameImage);
//
//    gtCheck = cv::sum(gtImageHist180Beans);
//    outCheck = cv::sum(bigImage);
//
//    BOOST_CHECK_EQUAL(gtCheck, outCheck);
//}

//BOOST_AUTO_TEST_CASE(gethistogramAngleIntervalTestCase) {
//
//    std::vector<Stixel2D> stixeis;
//    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
//    std::string path_resource = STIXEL_RESOURCE_PATH;
//    std::string inputPath = BACKGROUND_IMAGE_01;
//
//    cv::Mat testImage = cv::imread(path + path_resource + inputPath);
//    StixelTools::extractStixelFromBackground(testImage, &stixeis);
//
//    std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18, &testImage);
//
//    std::vector<Stixel2D> stixeis1, stixeis2, stixeis3, residual;
//
//    stixeis1 = StixelTools::gethistogramAngleInterval(stixeis, hist, 9, 2);
//    stixeis2 = StixelTools::gethistogramAngleInterval(stixeis, hist, 0, 2);
//    stixeis3 = StixelTools::gethistogramAngleInterval(stixeis, hist, 17, 2, &residual);
//
//    std::vector<uint> hist1 = StixelTools::histogramAngleStixel2D(stixeis1, 18);
//    std::vector<uint> hist2 = StixelTools::histogramAngleStixel2D(stixeis2, 18);
//    std::vector<uint> hist3 = StixelTools::histogramAngleStixel2D(stixeis3, 18);
//    std::vector<uint> hist4 = StixelTools::histogramAngleStixel2D(residual, 18);
//
//    std::vector<uint> gtHist1 = { 0, 0, 0, 0, 0, 0, 0, 34, 327, 43, 3, 4, 0, 0, 0, 0, 0, 0 };
//    std::vector<uint> gtHist2 = { 119, 60, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 39, 95 };
//    std::vector<uint> gtHist3 = { 119, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 39, 95 };
//    std::vector<uint> gtHist4 = { 0, 0, 17, 3, 4, 7, 6, 34, 327, 43, 3, 4, 2, 6, 4, 0, 0, 0 };
//    BOOST_CHECK_EQUAL_COLLECTIONS(hist1.begin(), hist1.end(), gtHist1.begin(), gtHist1.end());
//    BOOST_CHECK_EQUAL_COLLECTIONS(hist2.begin(), hist2.end(), gtHist2.begin(), gtHist2.end());
//    BOOST_CHECK_EQUAL_COLLECTIONS(hist3.begin(), hist3.end(), gtHist3.begin(), gtHist3.end());
//    BOOST_CHECK_EQUAL_COLLECTIONS(hist4.begin(), hist4.end(), gtHist4.begin(), gtHist4.end());
//}
//
//BOOST_AUTO_TEST_CASE(getMaxBeanAngleIntevalTestCase) {
//
//    std::vector<Stixel2D> stixeis, stixeis1;
//    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
//    std::string path_resource = STIXEL_RESOURCE_PATH;
//    std::string inputPath = BACKGROUND_IMAGE_01;
//
//    cv::Mat testImage = cv::imread(path + path_resource + inputPath);
//    StixelTools::extractStixelFromBackground(testImage, &stixeis);
//
//    std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18);
//
//    stixeis1 = StixelTools::getMaxBeanAngleInteval(stixeis, hist, 4);
//    std::vector<uint> hist1 = StixelTools::histogramAngleStixel2D(stixeis1, 18);
//
//    std::vector<uint> gtHist1 = { 0, 0, 0, 0, 4, 7, 6, 34, 327, 43, 3, 4, 2, 0, 0, 0, 0, 0 };
//
//    BOOST_CHECK_EQUAL_COLLECTIONS(gtHist1.begin(), gtHist1.end(), hist1.begin(), hist1.end());
//}
//
//BOOST_AUTO_TEST_CASE(getMaxBeanAngleIntevalsAdaptativeTestCase) {
//
//    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
//    std::string path_resource = STIXEL_RESOURCE_PATH;
//
//    std::vector<std::string> strVector(4);
//    strVector[0] = BACKGROUND_IMAGE_01;
//    strVector[1] = BACKGROUND_IMAGE_02;
//    strVector[2] = BACKGROUND_IMAGE_03;
//    strVector[3] = BACKGROUND_IMAGE_04;
//
//    std::vector<std::vector<uint> > vector1(4);
//    vector1[0]= {0, 0, 0, 0, 0, 0, 6, 34, 327, 43, 3, 0, 0, 0, 0, 0, 0, 0};
//    vector1[1]= {0, 0, 0, 0, 0, 1, 1, 3, 100, 89, 10, 2, 0, 0, 0, 0, 0, 0};
//    vector1[2]= {0, 0, 0, 0, 0, 0, 0, 3, 52, 182, 8, 5, 0, 0, 0, 0, 0, 0};
//    vector1[3]= {0, 0, 0, 0, 0, 0, 0, 3, 36, 126, 8, 1, 0, 0, 0, 0, 0, 0};
//
//    std::vector<std::vector<uint> > vector2(4);
//    vector2[0]= {119, 60, 17, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 39, 95};
//    vector2[1]= {88, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 33, 78};
//    vector2[2]= {83, 37, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 13, 75};
//    vector2[3]= {105, 28, 21, 14, 5, 3, 2, 0, 0, 0, 0, 0, 3, 3, 5, 17, 20, 78};
//
//    for (uint i = 0; i < strVector.size(); ++i) {
//        std::vector<Stixel2D> stixeis, stixeis1, stixeis2, residual, residual2;
//
//        //std::cout << "IMAGE " << strVector[i] << std::endl;
//        cv::Mat testImage = cv::imread(path + path_resource + strVector[i]);
//        StixelTools::extractStixelFromBackground(testImage, &stixeis);
//
//        std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18);
//
//        stixeis1 = StixelTools::getMaxBeanAngleIntevalsAdaptative(stixeis, hist, &residual);
//        std::vector<uint> hist1 = StixelTools::histogramAngleStixel2D(stixeis1, 18);
//        std::vector<uint> resid = StixelTools::histogramAngleStixel2D(residual, 18);
//        stixeis2 = StixelTools::getMaxBeanAngleIntevalsAdaptative(residual, resid, &residual2);
//        std::vector<uint> hist2 = StixelTools::histogramAngleStixel2D(stixeis2, 18);
//
//        BOOST_CHECK_EQUAL_COLLECTIONS(hist1.begin(), hist1.end(), vector1[i].begin(), vector1[i].end());
//        BOOST_CHECK_EQUAL_COLLECTIONS(hist2.begin(), hist2.end(), vector2[i].begin(), vector2[i].end());
//    }
//
//}
