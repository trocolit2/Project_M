/*
 * VPTools_test.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: tiagotrocoli
 */

#include <library/vanishPointPackage/VPTools.h>
#include <string>

#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "VPTools_test"
//VERY IMPORTANT - include this last

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/stixelPackage/StixelTools.h>
#include <TestTools.h>

BOOST_AUTO_TEST_CASE(convertStixeisToPointSimpleTesteCase) {

    std::vector<Stixel2D> stixeis;

    //good Stixel
    stixeis.push_back(Stixel2D(cv::Point2f(2, 13), cv::Point2f(8, 8)));
    stixeis.push_back(Stixel2D(cv::Point2f(8, 14), cv::Point2f(8, 2)));
    stixeis.push_back(Stixel2D(cv::Point2f(2, 2), cv::Point2f(9, 9)));
    stixeis.push_back(Stixel2D(cv::Point2f(8, 8), cv::Point2f(9, 5)));
    stixeis.push_back(Stixel2D(cv::Point2f(8, 8), cv::Point2f(5, 1)));
    stixeis.push_back(Stixel2D(cv::Point2f(0, 8), cv::Point2f(3, 8)));

    //bad Stixel
    stixeis.push_back(Stixel2D(cv::Point2f(13, 13), cv::Point2f(13, 4)));
    stixeis.push_back(Stixel2D(cv::Point2f(1, 14), cv::Point2f(1, 8)));
    stixeis.push_back(Stixel2D(cv::Point2f(4, 8), cv::Point2f(3, 4)));
    stixeis.push_back(Stixel2D(cv::Point2f(8, 0), cv::Point2f(13, 2)));
    stixeis.push_back(Stixel2D(cv::Point2f(4, 13), cv::Point2f(50, 4)));
    stixeis.push_back(Stixel2D(cv::Point2f(1, 15), cv::Point2f(13, 5)));
    stixeis.push_back(Stixel2D(cv::Point2f(12, 4), cv::Point2f(32, 21)));
    stixeis.push_back(Stixel2D(cv::Point2f(13, 25), cv::Point2f(23, 12)));

    float part = 0.3;

    cv::Point pointGroundThruthMedian(11, 13);
    std::vector<cv::Point2f> points = VPTools::convertStixeisToPoint(stixeis, stixeis.size() * part, 50);
    cv::Point medianPoint(0, 0);
    for (uint i = 0; i < points.size(); ++i) {
        medianPoint.x += points[i].x;
        medianPoint.y += points[i].y;
    }
    medianPoint.x = medianPoint.x / points.size();
    medianPoint.y = medianPoint.y / points.size();
    BOOST_CHECK_EQUAL(pointGroundThruthMedian, medianPoint);

    points = VPTools::convertStixeisToPoint(stixeis, stixeis.size() * part, 50, 15);
    medianPoint = cv::Point(0, 0);

    for (uint i = 0; i < points.size(); ++i) {
        medianPoint.x += points[i].x;
        medianPoint.y += points[i].y;
    }
    medianPoint.x = medianPoint.x / points.size();
    medianPoint.y = medianPoint.y / points.size();

    BOOST_CHECK_EQUAL(true, medianPoint != pointGroundThruthMedian);
}

//BOOST_AUTO_TEST_CASE(convertStixeisToPointTesteCase) {
//
//    std::vector<Stixel2D> stixeis, stixeis1;
//    std::string path = PATH_RELATIVE_ROOT_TESTBIN;
//    std::string path_resource = STIXEL_RESOURCE_PATH;
//    std::string inputPath = BACKGROUND_IMAGE_01;
//
//    cv::Mat testImage = cv::imread(path + path_resource + inputPath);
//    StixelTools::extractStixelFromBackground(testImage, &stixeis);
//    std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18);
//    stixeis1 = StixelTools::getMaxBeanAngleIntevalsAdaptative(stixeis, hist);
//
////    for (int i = 0; i < stixeis1.size(); ++i) {
////        std::cout << "index " << i << " : " << stixeis1[i] << std::endl;
////    }
//
//    uint totalPoints = 10;
//    float part = 0.3;
//    std::vector<cv::Point2f> points = StixelTools::convertStixeisToPoint(stixeis, stixeis.size() * part, totalPoints);
//
//    cv::Point2f median(0, 0);
//
//    cv::Mat matPoints(points);
//    uint imageSize = 1000;
//    double maxValue, minValue;
//
//    cv::minMaxLoc(matPoints, &minValue, &maxValue);
//    std::cout << "ABS MIN :" << abs(minValue) << " ABS MAX" << abs(maxValue) << std::endl;
//    if (abs(minValue) < abs(maxValue))
//        matPoints = matPoints / abs(maxValue);
//    else
//        matPoints = matPoints / abs(minValue);
//
//    cv::Mat3b imageTest = cv::Mat3b::zeros(imageSize, imageSize);
//
//    matPoints = (matPoints * imageSize / 2) + imageSize / 2;
//    cv::Scalar color(0, 255, 0);
//    for (uint i = 0; i < totalPoints; ++i) {
//        median.x = median.x + points[i].x;
//        median.y = median.y + points[i].y;
//        std::cout << "pi " << i << " : " << points[i] << std::endl;
//        cv::circle(imageTest, points[i], 3, color);
////        cv::imshow("TESTE", imageTest);
////        cv::waitKey();
//    }
//    median.x = median.x * imageSize / points.size();
//    median.y = median.y * imageSize / points.size();
//
//    cv::circle(imageTest, median, 5, cv::Scalar(0, 0, 255), -1);
//    cv::imshow("TESTE", imageTest);
//    cv::waitKey();
//}
