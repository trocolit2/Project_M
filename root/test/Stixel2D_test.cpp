/*
 * Stixel2D_test.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Stixel2D_test"
//VERY IMPORTANT - include this last

#include <vector>
#include <cmath>

#include <opencv2/core/core.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/stixelPackage/Stixel2D.h>
#include <library/stixelPackage/LineTools.h>

BOOST_AUTO_TEST_CASE(initStixel2DTestCase) {

	std::vector<cv::Scalar> inputs;
	inputs.push_back(cv::Scalar(0, 0, 0, 0));
	inputs.push_back(cv::Scalar(10, 0, 0, 0));
	inputs.push_back(cv::Scalar(10, 14, 2, 3));
	inputs.push_back(cv::Scalar(10, 14, 0, 15));
	inputs.push_back(cv::Scalar(1, 0, 5, 15));

	for (uint i = 0; i < inputs.size(); ++i) {
		cv::Point2d top(inputs[i][0], inputs[i][1]);
		cv::Point2d botton(inputs[i][2], inputs[i][3]);
		if (top.y > botton.y) {
			cv::Point2d temp = top;
			top = botton;
			botton = temp;
		}
		cv::Scalar lineEquation = LineTools::calcLineEquation2D(top, botton);
		Stixel2D stixel(top, botton);

		BOOST_CHECK_EQUAL(stixel.getAngle(),
				LineTools::calcAngle(lineEquation));
		BOOST_CHECK_EQUAL(stixel.getSize(),
				LineTools::calcLenghtFrom2Points(top, botton));
		BOOST_CHECK_EQUAL(stixel.getLineEquation(), lineEquation);
		BOOST_CHECK_EQUAL(stixel.getCenter(),
				LineTools::calcCenterFrom2Points(top, botton));
		BOOST_CHECK_EQUAL(stixel.getTopPoint(), top);
		BOOST_CHECK_EQUAL(stixel.getBottonPoint(), botton);
	}
}

