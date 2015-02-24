/*
 * BackGroundSubtraction_test.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: tiagotrocoli
 */
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BackGroundSubtraction_test"
//VERY IMPORTANT - include this last

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/VideoTools.h>
#include <library/BackGroundSubtraction.h>
#include <library/RegexStringTools.h>

#include "tools/TestTools.h"

#define TOTAL_IMAGES "100";

void backgroundFunctioGenericTestImageSequence(std::vector<std::string> input,
		std::vector<std::string> inputGT,
		BackGroundSubtraction *backgroundPTR) {

	cv::Mat currentFrame, foreground, foregroundGT;

	BackGroundSubtraction bkSubtraction = (*backgroundPTR);
	VideoTools videoTools(input);
	VideoTools imagesGT(inputGT);

	videoTools.isNextFrame();
	bkSubtraction.initImageBackground(videoTools.getFrame());

	std::string pathWrite;
	std::vector<std::string> gtInfo;
	bool showImages = false;

	bool writeImagesGT = !imagesGT.isNextFrame();
	if (writeImagesGT) {
		std::cout << "write ground thruth" << std::endl;
		gtInfo = imagesGT.getFileInfo();
		std::string regexTemp = RegexStringTools::fillSizeDigit(
				std::stoi(inputGT[2]), std::stoi(gtInfo[4]));
		pathWrite = gtInfo[1] + "/" + gtInfo[2];
		foregroundGT = cv::Mat::zeros(videoTools.getFrame().size(), CV_8UC3);
		TestTools::writeImageJpeg(pathWrite + regexTemp + gtInfo[3],
				foregroundGT);
		showImages = true;
	}

	while (videoTools.isNextFrame()) {
		currentFrame = videoTools.getFrame();
		foreground = bkSubtraction.applySubtraction(currentFrame);
		if (foreground.channels() > 1)
			cv::cvtColor(foreground, foreground, CV_BGR2GRAY);
		foreground = foreground > 0;

		if (writeImagesGT) {
			std::string numberFrame = videoTools.getFileInfo()[5];
			std::string regexTemp = RegexStringTools::fillSizeDigit(
					std::stoi(numberFrame), std::stoi(gtInfo[4]));
			if (!foreground.empty())
				TestTools::writeImageJpeg(pathWrite + regexTemp + gtInfo[3],
						foreground);
		} else {
			imagesGT.isNextFrame();
			foregroundGT = imagesGT.getFrame();
			cv::cvtColor(foregroundGT, foregroundGT, CV_BGR2GRAY);
			foregroundGT = foregroundGT > 0;

			foreground = foreground - foregroundGT;
			BOOST_CHECK_EQUAL(cv::sum(foreground), cv::Scalar(0, 0, 0, 0));
		}
		if (showImages) {
			cv::imshow("FOREGROUND GT ", foregroundGT);
			cv::imshow("CURRENT FRAME ", currentFrame);
			if (!foreground.empty())
				cv::imshow("FOREGROUND ", foreground);
			if (!bkSubtraction.getImageBackground().empty())
				cv::imshow("BACKGROUND ", bkSubtraction.getImageBackground());
			cv::waitKey(0);
		}

	}
	cv::destroyAllWindows();
}

//==========================================
// ADAPTIVE BACKGROUND LEARNING TEST SESSION
//==========================================

BOOST_AUTO_TEST_CASE(AdaptiveBackgroundLearningPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	double threshold = 15;
	double alpha = 0.05;

	std::vector<double> setttings = { threshold, alpha };

	BackGroundSubtraction bkSubtraction(METHOD_ADAPTIVE_BACKGROUND_LEARNING,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), setttings);

	std::string prefix = "GT_ADAPTIVE_BACKGROUND_LEARNING_";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

//==========================================
// MOG1 TEST SESSION
//==========================================

BOOST_AUTO_TEST_CASE(MixtureOfGaussianV1BGSPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	double threshold = 100;
	double alpha = 0.001;

	std::vector<double> setttings = { threshold, alpha };

	BackGroundSubtraction bkSubtraction(METHOD_MIXTURE_OF_GAUSSIAN_V1BGS,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), setttings);

	std::string prefix = "GT_MIXTURE_OF_GAUSSIAN_V1BGS_";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

BOOST_AUTO_TEST_CASE(MixtureOfGaussianV1BGSWithMorphPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	double threshold = 1;
	double alpha = 0.011;

	std::vector<double> setttings = { threshold, alpha };
	std::vector<double> morph = {3,3};

	BackGroundSubtraction bkSubtraction(METHOD_MIXTURE_OF_GAUSSIAN_V1BGS,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), setttings,morph);

	std::string prefix = "GT_MIXTURE_OF_GAUSSIAN_V1BGS_WITH_MORPH";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

//==========================================
// LB ADAPTIVE SOM TEST SESSION
//==========================================

BOOST_AUTO_TEST_CASE(LBAdaptiveSOMPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	BackGroundSubtraction bkSubtraction(METHOD_LB_ADAPTIVE_SOM,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3));

	std::string prefix = "GT_LB_ADAPTIVE_SOM_";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

//==========================================
// MULTI LAYER BGS TEST SESSION
//==========================================

BOOST_AUTO_TEST_CASE(MultiLayerBGSPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	BackGroundSubtraction bkSubtraction(METHOD_MULTILAYER_BGS,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3));

	std::string prefix = "GT_MULTILAYER_BGS_";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

//==========================================
// MEDIAN FILTER BGS TEST SESSION
//==========================================

BOOST_AUTO_TEST_CASE(MedianFilterPath1TestCase) {
	std::vector<std::string> input(4), inputGT(4);

	double threshold = 50;
	double alpha = 0.5;

	std::vector<double> setttings = { threshold, alpha };

	BackGroundSubtraction bkSubtraction(METHOD_MEDIAN_FILTER,
			cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), setttings);

	std::string prefix = "GT_MEDIAN_FILTER_";

	input[0] = "-S";
	input[1] = std::string(PATH_PETS_2006_S1) + "IMG|4|.jpeg";
	input[2] = "1";
	input[3] = TOTAL_IMAGES
	;

	inputGT[0] = "-S";
	inputGT[1] = std::string(PATH_PETS_2006_S1) + prefix + "|4|.jpeg";
	inputGT[2] = "1";
	inputGT[3] = input[3];

	backgroundFunctioGenericTestImageSequence(input, inputGT, &bkSubtraction);
}

BOOST_AUTO_TEST_CASE(MorpDilateErodeTest) {

	std::string path = std::string(PATH_RELATIVE_ROOT_TESTBIN);
	path += "resource/backgrounSubtraction/dataset3/";
	cv::Mat input = cv::imread(path + "BW1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat output;
	output = BackGroundSubtraction::applyDialateAndErode(input, 7, 7, 2);
	cv::Mat gtInput = cv::imread(path + "GT1_BW1.jpeg",
			CV_LOAD_IMAGE_GRAYSCALE);
	gtInput = gtInput > 0;
	output = output - gtInput;
	BOOST_CHECK_EQUAL(cv::sum(output), cv::Scalar(0));
}

