/*
 * MedianFilterBGS.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: tiagotrocoli
 */

#include "MedianFilterBGS.h"
#include <vector>

MedianFilterBGS::MedianFilterBGS() :
		threshold(45.0 / 255), alpha(0.5 / 255) {
}

MedianFilterBGS::MedianFilterBGS(double threshold, double alpha) :
		threshold(20.0 / 255), alpha(1.0 / 255) {
	this->threshold = threshold / 255;
	this->alpha = alpha * 1.0 / 255;
}

MedianFilterBGS::~MedianFilterBGS() {
	// TODO Auto-generated destructor stub
}

void MedianFilterBGS::process(const cv::Mat& img_input, cv::Mat& img_output,
		cv::Mat& img_bgmodel) {

	cv::Mat mat, logic;
	std::vector<cv::Mat> channels;

	if (this->background.empty())
		img_input.convertTo(this->background, CV_32FC3, 1.0 / 255);

	img_input.convertTo(mat, CV_32FC3, 1.0 / 255);
	logic = cv::abs(mat - this->background) > this->threshold;

	cv::split(logic, channels);

	cv::bitwise_or(channels[0], channels[1], logic);
	cv::bitwise_or(logic, channels[2], logic);

	channels[0] = channels[1] = channels[2] = logic;

	cv::merge(channels, logic);
	cv::cvtColor(logic, img_output, CV_BGR2GRAY);

	mat = mat > this->background;
	mat.convertTo(mat, CV_32FC3, 1.0 / 255);
	logic = this->alpha * mat;
	absdiff(1.0, mat, mat);
	mat.convertTo(mat, CV_32FC3, 1.0 / 255);
	mat = this->alpha * mat;

	this->background += logic - mat;

	this->background.convertTo(img_bgmodel, CV_8UC3, 255);

}

void MedianFilterBGS::saveConfig() {
}

void MedianFilterBGS::loadConfig() {
}
