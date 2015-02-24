/*
 * StixelExtraction.h
 *
 *  Created on: Jan 20, 2015
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_STIXELPACKAGE_STIXELTOOLS_H_
#define SRC_LIBRARY_STIXELPACKAGE_STIXELTOOLS_H_

#include "Stixel2D.h"

#include <opencv2/core/core.hpp>
#include <vector>

class StixelTools {
public:
	static cv::Mat extractStixelFromForeground(cv::Mat foreground,
			std::vector<Stixel2D> *stixeis, uint64 minPoints = 4,
			cv::Mat showImage = cv::Mat::zeros(0, 0, CV_8UC3));

	static cv::Mat extractStixelFromBackground(cv::Mat background,
			std::vector<Stixel2D> *stixeis,
			cv::Mat showImage = cv::Mat::zeros(0, 0, CV_8UC3));

	static std::vector<uint> histogramAngleStixel2D(
			std::vector<Stixel2D> stixeis, uint beans, cv::Mat *image = 0);

	static std::vector<Stixel2D> gethistogramAngleInterval(
			std::vector<Stixel2D> mainVector, std::vector<uint> histogram,
			uint midleBean, uint intevalSides,
			std::vector<Stixel2D>* residualVector = 0);

	static std::vector<Stixel2D> getMaxBeanAngleInteval(
			std::vector<Stixel2D> mainVector, std::vector<uint> histogram,
			uint intevalSides, std::vector<Stixel2D>* residualVector = 0);

private:
	static std::vector<std::vector<cv::Point> > filterByNumberPoints(
			std::vector<std::vector<cv::Point> > contours, uint64 numberPoints);

	static std::vector<Stixel2D> getStixelFromLSD(cv::Mat background);

	static cv::Mat drawHistogramAngleStixel2D(std::vector<uint> histgram,
			cv::Size size = cv::Size(640, 480));
};

#endif /* SRC_LIBRARY_STIXELPACKAGE_STIXELTOOLS_H_ */
