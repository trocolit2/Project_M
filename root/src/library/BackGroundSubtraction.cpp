/*
 * BackGroundSubtraction.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: tiagotrocoli
 */
#include <iostream>

#include "backgroundSubtractionPackage/AdaptiveBackgroundLearning.h"
#include "backgroundSubtractionPackage/MixtureOfGaussianV1BGS.h"
#include "backgroundSubtractionPackage/MedianFilterBGS.h"
#include "backgroundSubtractionPackage/lb/LBAdaptiveSOM.h"
#include "backgroundSubtractionPackage/jmo/MultiLayerBGS.h"

#include "BackGroundSubtraction.h"

BackGroundSubtraction::~BackGroundSubtraction() {
	// TODO Auto-generated destructor stub
}

BackGroundSubtraction::BackGroundSubtraction(uint method,
		cv::Mat initBackground, std::vector<double> settings,
		std::vector<double> morphologicSettings) {

	this->morphologicSettings = morphologicSettings;
	if (morphologicSettings.size() > 0)
		initMorphologyOpeation();

	this->settings = settings;
	this->selectdMethod = method;
	switch (this->selectdMethod) {
	case METHOD_ADAPTIVE_BACKGROUND_LEARNING:
		initAdaptiveBackgroundLearning(settings);
		break;
	case METHOD_MIXTURE_OF_GAUSSIAN_V1BGS:
		initMixtureOfGaussianV1BGS(settings);
		break;
	case METHOD_LB_ADAPTIVE_SOM:
		initLBAdaptiveSOM(settings);
		break;
	case METHOD_MULTILAYER_BGS:
		initMultiLayerBGS(settings);
		break;
	case METHOD_MEDIAN_FILTER:
		initMedianFilterrBGS(settings);
		break;
	default:
		std::cout << "ERROR - No subtraction method selected" << std::endl;
		exit (EXIT_FAILURE);
	}
	initBackground.copyTo(this->imageBackground);
}

cv::Mat BackGroundSubtraction::applySubtraction(cv::Mat currentFrame) {
	cv::Mat foreground;
	ptr->process(currentFrame, foreground, this->imageBackground);

	if (morphologicSettings.size() > 0)
		foreground = applyDialateAndErode(foreground);

	return foreground;
}

cv::Mat BackGroundSubtraction::getImageBackground() {
	return this->imageBackground;
}

void BackGroundSubtraction::initImageBackground(cv::Mat initBackground) {
	initBackground.copyTo(this->imageBackground);
}

void BackGroundSubtraction::initAdaptiveBackgroundLearning(
		std::vector<double> settings) {
	if (settings.size() > 1) {
		ptr = new AdaptiveBackgroundLearning((uint) settings[0], settings[1]);
	} else {
		ptr = new AdaptiveBackgroundLearning(15, 0.05);
	}
}

void BackGroundSubtraction::initMixtureOfGaussianV1BGS(
		std::vector<double> settings) {
	if (settings.size() > 1) {
		ptr = new MixtureOfGaussianV1BGS((uint) settings[0], settings[1]);
	} else {
		ptr = new MixtureOfGaussianV1BGS(15, 0.05);
	}
}

void BackGroundSubtraction::initLBAdaptiveSOM(std::vector<double> settings) {
	ptr = new LBAdaptiveSOM();
}

void BackGroundSubtraction::initMultiLayerBGS(std::vector<double> settings) {
	ptr = new MultiLayerBGS();
}

cv::Mat BackGroundSubtraction::applyDialateAndErode(cv::Mat image) {

	cv::Mat tempImage = image.clone();
	cv::dilate(tempImage, tempImage, dilateElement);
	cv::erode(tempImage, tempImage, erodeElement);

	return tempImage > 128;
}

void BackGroundSubtraction::initMorphologyOpeation() {

	double dilate = morphologicSettings[0];
	double erode = morphologicSettings[1];
	this->dilateElement = cv::getStructuringElement(cv::MORPH_ELLIPSE,
			cv::Size(2 * dilate + 1, 2 * dilate + 1),
			cv::Point(dilate, dilate));
	this->erodeElement = cv::getStructuringElement(cv::MORPH_ELLIPSE,
			cv::Size(2 * erode + 1, 2 * erode + 1), cv::Point(erode, erode));
}

void BackGroundSubtraction::initMedianFilterrBGS(std::vector<double> settings) {
	if (settings.size() > 1) {
		ptr = new MedianFilterBGS(settings[0], settings[1]);
	} else {
		ptr = new MedianFilterBGS();
	}
}

BackGroundSubtraction BackGroundSubtraction::clone() {

	return BackGroundSubtraction(this->selectdMethod, this->imageBackground,
			this->settings, this->morphologicSettings);
}

cv::Mat BackGroundSubtraction::applyDialateAndErode(cv::Mat image,
		double dilate, double erode, uint morph) {

	if (image.channels() > 1) {
		return cv::Mat();
	}

	cv::Mat tempImage = image.clone();
	cv::Mat dilateElement = cv::getStructuringElement(morph,
			cv::Size(2 * dilate + 1, 2 * dilate + 1),
			cv::Point(dilate, dilate));
	cv::Mat erodeElement = cv::getStructuringElement(morph,
			cv::Size(2 * erode + 1, 2 * erode + 1), cv::Point(erode, erode));

	cv::dilate(tempImage, tempImage, dilateElement);
	cv::erode(tempImage, tempImage, erodeElement);

	return tempImage > 128;

}
