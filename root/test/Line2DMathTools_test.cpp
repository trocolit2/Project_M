#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "LineTools_test"
//VERY IMPORTANT - include this last

#include <iostream>

#include <vector>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <cmath>
#include <library/line2dtoolspackage/Line2DMathTools.h>

#include <TestTools.h>

std::vector<cv::Scalar> groundsTruthPoints(std::vector<cv::Scalar> *inputs) {

    std::vector<cv::Scalar> groundsTruths;

    //case1
    inputs->push_back(cv::Scalar(1, 1, 0, 0));
    groundsTruths.push_back(cv::Scalar(1, -1, 0));

    //case2
    inputs->push_back(cv::Scalar(0, 1, 0, 0));
    groundsTruths.push_back(cv::Scalar(-1.0, 0, 0));

    //case3
    inputs->push_back(cv::Scalar(1, 0, 0, 0));
    groundsTruths.push_back(cv::Scalar(0, -1.0, 0));

    //case4
    inputs->push_back(cv::Scalar(-11, 0, 0, 0));
    groundsTruths.push_back(cv::Scalar(0, -1.0, 0));

    //case5
    inputs->push_back(cv::Scalar(-11, 3, 1, 2));
    groundsTruths.push_back(cv::Scalar(-0.083333333333333329, -1, 2.0833333333333335));

    //case6
    inputs->push_back(cv::Scalar(0, 4.0 / 3, 21.0 / 5, 11));
    groundsTruths.push_back(cv::Scalar(2.3015873015873014, -1, 1.3333333333333333));

    return groundsTruths;
}

BOOST_AUTO_TEST_CASE(calcLineEquationLine2DTestCase) {

    std::vector<cv::Scalar> inputs, groundsTruths = groundsTruthPoints(&inputs);

    for (uint i = 0; i < groundsTruths.size(); ++i) {
        //	std::cout << " GT = " << groundsTruths[i] << std::endl;
        cv::Point2d pt2(inputs[i][0], inputs[i][1]);
        cv::Point2d pt1(inputs[i][2], inputs[i][3]);
        cv::Scalar output = Line2DMathTools::calcLineEquation2D(pt1, pt2);
        BOOST_CHECK_EQUAL(groundsTruths[i], output);

    }
}

BOOST_AUTO_TEST_CASE(calcNormLineEquationLine2DTestCase) {

    std::vector<cv::Scalar> inputs, groundsTruths = groundsTruthPoints(&inputs);

    for (uint i = 0; i < groundsTruths.size(); ++i) {
        groundsTruths[i];
        double norm = sqrt(groundsTruths[i][0] * groundsTruths[i][0] + groundsTruths[i][1] * groundsTruths[i][1]);
        cv::Scalar temp(groundsTruths[i][0] / norm, groundsTruths[i][1] / norm, groundsTruths[i][2] / norm);
        cv::Scalar outLineEquation = Line2DMathTools::calcNormlizeLineEquation(groundsTruths[i]);
        BOOST_CHECK_EQUAL(outLineEquation, temp);

    }
}

BOOST_AUTO_TEST_CASE(calcAngleTestCase) {

    std::vector<cv::Scalar> inputs, equationLines = groundsTruthPoints(&inputs);
    std::vector<double> anglesGrountruth(inputs.size());
    anglesGrountruth[0] = 45;
    anglesGrountruth[1] = 90;
    anglesGrountruth[2] = 0;
    anglesGrountruth[3] = 0;
    anglesGrountruth[4] = 175.23635830927381;
    anglesGrountruth[5] = 66.515884709495126;
    double outAngle;
    for (uint i = 0; i < anglesGrountruth.size(); ++i) {
        outAngle = Line2DMathTools::calcAngle(equationLines[i]);
        //std::cout << " OUT ANGLE =" << outAngle << std::endl;
        BOOST_CHECK_EQUAL(anglesGrountruth[i], outAngle);
    }
}

BOOST_AUTO_TEST_CASE(calcCenterFrom2PointsTestCase) {

    std::vector<cv::Scalar> inputs;
    inputs.push_back(cv::Scalar(1, 0, 0, 0));
    inputs.push_back(cv::Scalar(10, 0, 5, 0));
    inputs.push_back(cv::Scalar(0, 0, 0, 4));
    inputs.push_back(cv::Scalar(1, 1, 5, 5));
    inputs.push_back(cv::Scalar(10, 15, 30, 20));

    cv::Point2d outCenter, gtCenter;

    for (uint i = 0; i < inputs.size(); ++i) {
        cv::Point2d pt1(inputs[i][0], inputs[i][1]);
        cv::Point2d pt2(inputs[i][2], inputs[i][3]);
        outCenter = Line2DMathTools::calcCenterFrom2Points(pt1, pt2);
        //std::cout << " OUT ANGLE =" << outCenter << std::endl;
        gtCenter.x = (pt1.x - pt2.x) / 2 + pt2.x;
        gtCenter.y = (pt1.y - pt2.y) / 2 + pt2.y;
        BOOST_CHECK_EQUAL(outCenter, gtCenter);
    }
}

BOOST_AUTO_TEST_CASE(calcLenghtFrom2PointsTestCase) {

    std::vector<cv::Scalar> inputs;
    inputs.push_back(cv::Scalar(1, 0, 0, 0));
    inputs.push_back(cv::Scalar(10, 0, 5, 0));
    inputs.push_back(cv::Scalar(0, 0, 0, 4));
    inputs.push_back(cv::Scalar(1, 1, 5, 5));
    inputs.push_back(cv::Scalar(10, 15, 30, 20));

    double outSize = 0, size = 0;
    for (uint i = 0; i < inputs.size(); ++i) {
        cv::Point2d pt1(inputs[i][0], inputs[i][1]);
        cv::Point2d pt2(inputs[i][2], inputs[i][3]);
        outSize = Line2DMathTools::calcLenghtFrom2Points(pt1, pt2);
        //std::cout << " OUT ANGLE =" << outSize << std::endl;
        size = (pt1.x - pt2.x) * (pt1.x - pt2.x);
        size += (pt1.y - pt2.y) * (pt1.y - pt2.y);
        size = sqrt(size);
        BOOST_CHECK_EQUAL(outSize, size);
    }
}

void inputCalcDistanceLine2Point(std::vector<cv::Scalar> *lines, std::vector<cv::Point2f> *points, std::vector<double> *distances) {

    lines->push_back(cv::Scalar(-2, 3, 4));
    lines->push_back(cv::Scalar(6, -5, 10));
    lines->push_back(cv::Scalar(3, 4, -6));

    points->push_back(cv::Point2f(5, 6));
    points->push_back(cv::Point2f(-3, 7));
    points->push_back(cv::Point2f(-1, 3));

    distances->push_back(3.328);
    distances->push_back(5.505);
    distances->push_back(0.6);
}

BOOST_AUTO_TEST_CASE(calcDistanceLine2PointTestCase) {

    uint precision = 1000;
    std::vector<cv::Scalar> lines;
    std::vector<cv::Point2f> points;
    std::vector<double> distances;
    inputCalcDistanceLine2Point(&lines, &points, &distances);

    for (uint i = 0; i < lines.size(); ++i) {

        double out = Line2DMathTools::calcDistanceLine2Point(lines[i], points[i]);
        BOOST_CHECK_EQUAL((uint )(out * precision), (uint )(distances[i] * precision));

        cv::Point2f outPoint;
        out = Line2DMathTools::calcDistanceLine2Point(lines[i], points[i], &outPoint);
        BOOST_CHECK_EQUAL((uint )(out * precision), (uint )(distances[i] * precision));
    }
}
