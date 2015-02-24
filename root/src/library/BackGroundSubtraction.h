/*
 * BackGroundSubtraction.h
 *
 *  Created on: Dec 10, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_BACKGROUNDSUBTRACTION_H_
#define SRC_BACKGROUNDSUBTRACTION_H_

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>

#include "backgroundSubtractionPackage/IBGS.h"

// methods to apply the subtraction
#define METHOD_ADAPTIVE_BACKGROUND_LEARNING 0
#define METHOD_MIXTURE_OF_GAUSSIAN_V1BGS 1
#define METHOD_LB_ADAPTIVE_SOM 2
#define METHOD_MULTILAYER_BGS 3
#define METHOD_MEDIAN_FILTER 4

class BackGroundSubtraction {
public:
	/*
	 * Background Subtraction Class
	 * Init Background Subtration with:
	 *  @parameter - uint method - choose the method do apply the background subtraction:
	 *	 REWRITE THE METHODS
	 *
	 *  @parameter - cv::Mat initBackground - init the background image
	 *  @parameter - vector of setting for each method:
	 *
	 *
	 */
	BackGroundSubtraction(uint method, cv::Mat initBackground,
			std::vector<double> settings = std::vector<double>(),
			std::vector<double> mophologicSettings = std::vector<double>());
	virtual ~BackGroundSubtraction();

	/*
	 * Apply Subtraction
	 * @parameter	- cv::Mat	- current frame
	 * @return		- cv::Mat	- actual foreground frame
	 */
	cv::Mat applySubtraction(cv::Mat currentFrame);
	/*
	 * Get background image	 *
	 * @return		- cv::Mat	- actual background image
	 */
	cv::Mat getImageBackground();
	/*
	 * INIT Image Background	 *
	 * @return		- cv::Mat	- actual background image
	 */
	void initImageBackground(cv::Mat initBackground);

	BackGroundSubtraction clone();

	//tools methods
	static cv::Mat applyDialateAndErode(cv::Mat image, double dilate,
			double erode, uint morph = cv::MORPH_ELLIPSE);
	cv::Mat applyDialateAndErode(cv::Mat image);

private:

	uint selectdMethod;
	std::vector<double> settings;
	std::vector<double> morphologicSettings;
	cv::Mat imageBackground;
	cv::Ptr<IBGS> ptr;

	cv::Mat dilateElement;
	cv::Mat erodeElement;

	void initMorphologyOpeation();

	// init Methods
	void initAdaptiveBackgroundLearning(std::vector<double> settings);
	void initMixtureOfGaussianV1BGS(std::vector<double> settings);
	void initLBAdaptiveSOM(std::vector<double> settings);
	void initMultiLayerBGS(std::vector<double> settings);
	void initMedianFilterrBGS(std::vector<double> settings);

};

#endif /* SRC_BACKGROUNDSUBTRACTION_H_ */

