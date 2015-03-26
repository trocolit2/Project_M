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

cv::Point2f stixeisInputConvergePoint(std::vector<Stixel2D>* goodStixeis = 0, std::vector<Stixel2D>* badStixeis = 0) {

    if (goodStixeis != 0) {
        //good Stixel
        goodStixeis->push_back(Stixel2D(cv::Point2f(2, 13), cv::Point2f(8, 8)));
        goodStixeis->push_back(Stixel2D(cv::Point2f(8, 14), cv::Point2f(8, 2)));
        goodStixeis->push_back(Stixel2D(cv::Point2f(2, 2), cv::Point2f(9, 9)));
        goodStixeis->push_back(Stixel2D(cv::Point2f(8, 8), cv::Point2f(9, 5)));
        goodStixeis->push_back(Stixel2D(cv::Point2f(8, 8), cv::Point2f(5, 1)));
        goodStixeis->push_back(Stixel2D(cv::Point2f(0, 8), cv::Point2f(3, 8)));
    }
    if (badStixeis != 0) {
        //bad Stixel
        badStixeis->push_back(Stixel2D(cv::Point2f(13, 13), cv::Point2f(13, 4)));
        badStixeis->push_back(Stixel2D(cv::Point2f(1, 14), cv::Point2f(1, 8)));
        badStixeis->push_back(Stixel2D(cv::Point2f(4, 8), cv::Point2f(3, 4)));
        badStixeis->push_back(Stixel2D(cv::Point2f(8, 0), cv::Point2f(13, 2)));
        badStixeis->push_back(Stixel2D(cv::Point2f(4, 13), cv::Point2f(50, 4)));
        badStixeis->push_back(Stixel2D(cv::Point2f(1, 15), cv::Point2f(13, 5)));
        badStixeis->push_back(Stixel2D(cv::Point2f(12, 4), cv::Point2f(32, 21)));
        badStixeis->push_back(Stixel2D(cv::Point2f(13, 25), cv::Point2f(23, 12)));
    }

    return cv::Point2f(8, 8);

}

BOOST_AUTO_TEST_CASE(convertStixeisToPointSimpleTesteCase) {

    std::vector<Stixel2D> stixeis;
    cv::Point gtPoint, outPoint;

    gtPoint = stixeisInputConvergePoint(&stixeis);
    outPoint = VPTools::convergeStixeisToPointBySVD(stixeis);
    BOOST_CHECK_EQUAL(gtPoint, outPoint);

    stixeisInputConvergePoint(0, &stixeis);
    outPoint = VPTools::convergeStixeisToPointBySVD(stixeis);
    outPoint = gtPoint - outPoint;
    bool check = outPoint != cv::Point(0, 0);
    BOOST_CHECK_EQUAL(check, true);

}

