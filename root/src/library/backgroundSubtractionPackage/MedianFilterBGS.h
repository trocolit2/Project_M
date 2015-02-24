/*
 * MedianFilterBGS.h
 *
 *  Created on: Dec 19, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_BACKGROUNDSUBTRACTIONPACKAGE_MEDIANFILTERBGS_H_
#define SRC_LIBRARY_BACKGROUNDSUBTRACTIONPACKAGE_MEDIANFILTERBGS_H_

#pragma once

#include "IBGS.h"
#include <iostream>
#include <opencv2/opencv.hpp>

class MedianFilterBGS: public IBGS {
private:
	double threshold;
	double alpha;
	cv::Mat background;

public:
	MedianFilterBGS(double threshold, double alpha);
	MedianFilterBGS();
	~MedianFilterBGS();

	void process(const cv::Mat &img_input, cv::Mat &img_output,
			cv::Mat &img_bgmodel);

private:

	void saveConfig();
	void loadConfig();

};

#endif /* SRC_LIBRARY_BACKGROUNDSUBTRACTIONPACKAGE_MEDIANFILTERBGS_H_ */
