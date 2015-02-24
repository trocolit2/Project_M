/*
 * BackGroundSubtraction_evaluation.cpp
 *
 *  Created on: Jan 5, 2015
 *      Author: tiagotrocoli
 */
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BackGroundSubtraction_evaluation"
//VERY IMPORTANT - include this last

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/VideoTools.h>
#include <library/BackGroundSubtraction.h>
#include <library/RegexStringTools.h>

#include "tools/EvaluationsTools.h"
#include "tools/TestTools.h"

#define GROUND_THRUTH_INTERVAL 50
#define GROUND_THRUTH_PREFIX_NAME "GT_BGS_IMG"
#define TOTAL_IMAGES "500"

std::vector<double> oneLessTPR(std::vector<cv::Scalar> tables) {

	std::vector<double> temp;
	for (uint i = 0; i < tables.size(); ++i) {
		temp.push_back(1.0 - tables[i][0]);
	}
	return temp;
}

std::vector<std::string> paths() {

	std::vector<std::string> vector;
	vector.push_back(PATH_PETS_2006_S1);
	vector.push_back(PATH_PETS_2006_S2);
	vector.push_back(PATH_PETS_2006_S3);
	vector.push_back(PATH_PETS_2006_S4);
	return vector;
}

cv::Mat loadGTImages(std::string path, std::string prefix, uint index,
		uint sizeDigit) {
	std::string frameId = RegexStringTools::fillSizeDigit(index, sizeDigit);
	path = path + "/" + prefix + frameId + ".jpeg";
	cv::Mat gtMat = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);
	gtMat = gtMat > 200;
	return gtMat;

}

double getBackgroundSegmentationResult(std::vector<std::string> input,
		BackGroundSubtraction *backgroundPTR, std::vector<cv::Scalar> *vector) {

	std::string gtPrefix = GROUND_THRUTH_PREFIX_NAME;
	std::string path;

	BackGroundSubtraction bkSubtraction = backgroundPTR->clone();

	VideoTools videoTools(input);

	path = videoTools.getFileInfo()[1];
	cv::Mat foreground;
	const clock_t begin_time = clock();
	int currentFrameInt = 0;
	while (videoTools.isNextFrame()) {
		foreground = bkSubtraction.applySubtraction(videoTools.getFrame());
		std::string currentFrameStr = videoTools.getFileInfo()[5];
		currentFrameInt = std::stoi(currentFrameStr);
		//cv::imshow("CURRENT SEGMENTATION", foreground);
		if ((currentFrameInt % GROUND_THRUTH_INTERVAL) == 0) {
			cv::Mat out;
			cv::Mat gtMat = loadGTImages(path, gtPrefix, currentFrameInt, 4);
			cv::Scalar table = EvaluationsTools::evaluationMaps(gtMat,
					foreground, &out);
			table = EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(table);
			(*vector).push_back(table);
//			cv::imshow("GROUND THRUTH", gtMat);
//			cv::imshow("OUT CHECK", out);
//			cv::waitKey();

		}
//		cv::waitKey(1);
	}
	return currentFrameInt * 1.0
			/ (double(clock() - begin_time) / CLOCKS_PER_SEC);

}

cv::Scalar evalutationROCArea(BackGroundSubtraction *backgroundPTR) {

	std::vector<cv::Scalar> results;
	std::vector<std::string> pathsVector = paths();
	double fps = 0;
	for (uint i = 0; i < pathsVector.size(); ++i) {
		std::vector<std::string> input(4);
		input[0] = "-S";
		input[1] = pathsVector[i] + "IMG|4|.jpeg";
		input[2] = "1";
		input[3] = TOTAL_IMAGES;
		fps += getBackgroundSegmentationResult(input, backgroundPTR, &results);
	}
	fps = fps / pathsVector.size();

	double area = 0;
	std::vector<double> scores = oneLessTPR(results);
	EvaluationsTools::curveROC(scores, &area);
	return cv::Scalar(area, fps);
}

BOOST_AUTO_TEST_CASE(GroundThruthTableTestCase) {

	cv::Mat gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::Mat inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::Scalar outTable, groundThruthTable(36619, 165662, 62766, 42153);

	cv::circle(gtMat, cv::Point(200, 200), 100, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(400, 400), 50, cv::Scalar(255), -1);
	cv::circle(gtMat, cv::Point(400, 200), 125, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(300, 300), 150, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(100, 50), 100, cv::Scalar(255), -1);

	outTable = EvaluationsTools::evaluationMaps(gtMat, inputMat);

	BOOST_CHECK_EQUAL(
			groundThruthTable[0] + groundThruthTable[1] + groundThruthTable[2]
					+ groundThruthTable[3],
			inputMat.size().height * inputMat.size().width);

	BOOST_CHECK_EQUAL(outTable, groundThruthTable);

}

BOOST_AUTO_TEST_CASE(GroundThruthImageTestCase) {

	cv::Mat gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::Mat inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::Mat imageCheck = cv::imread(
			std::string(PATH_RELATIVE_ROOT_TESTBIN)
					+ "resource/evaluationTest/GroundThruthImageTest.jpeg");
	cv::Mat out;

	cv::circle(gtMat, cv::Point(400, 200), 125, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(300, 300), 150, cv::Scalar(255), -1);

	std::string imageName = "outImage.jpeg";

	EvaluationsTools::evaluationMaps(gtMat, inputMat, &out);
	TestTools::writeImageJpeg(imageName, out);
	out = cv::imread(imageName);

	std::vector<uint8_t> imageCheckvector = TestTools::convertmat2vector(
			imageCheck);
	std::vector<uint8_t> outvector = TestTools::convertmat2vector(out);

	BOOST_CHECK_EQUAL_COLLECTIONS(imageCheckvector.begin(),
			imageCheckvector.end(), outvector.begin(), outvector.end());

}

BOOST_AUTO_TEST_CASE(calcTPR_FPR_PRECISION_ACCURACYTestCase) {

	cv::Mat gtMat, inputMat, out;
	cv::Scalar table, score, gtScore;

	gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::circle(gtMat, cv::Point(300, 300), 150, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(300, 300), 125, cv::Scalar(255), -1);
	gtScore = cv::Scalar(0.694, 0, 1, 0.929);
	table = EvaluationsTools::evaluationMaps(gtMat, inputMat, &out);
	score = EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(table);
	for (uint8_t i = 0; i < 4; ++i)
		score[i] = TestTools::setDigits(score[i], 3);
	BOOST_CHECK_EQUAL(score, gtScore);

	gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::circle(gtMat, cv::Point(300, 300), 125, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(300, 300), 150, cv::Scalar(255), -1);
	gtScore = cv::Scalar(0.694, 0.083, 0.694, 0.929);
	table = EvaluationsTools::evaluationMaps(gtMat, inputMat, &out);
	score = EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(table);
	for (uint8_t i = 0; i < 4; ++i)
		score[i] = TestTools::setDigits(score[i], 3);
	BOOST_CHECK_EQUAL(score, gtScore);

	gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::circle(gtMat, cv::Point(100, 100), 50, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(400, 400), 150, cv::Scalar(255), -1);
	gtScore = cv::Scalar(0, 0.193, 0, 0.785);
	table = EvaluationsTools::evaluationMaps(gtMat, inputMat, &out);
	score = EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(table);
	for (uint8_t i = 0; i < 4; ++i)
		score[i] = TestTools::setDigits(score[i], 3);
	BOOST_CHECK_EQUAL(score, gtScore);

	gtMat = cv::Mat::zeros(480, 640, CV_8UC1);
	inputMat = cv::Mat::zeros(480, 640, CV_8UC1);
	cv::circle(gtMat, cv::Point(100, 100), 50, cv::Scalar(255), -1);
	cv::circle(inputMat, cv::Point(150, 150), 75, cv::Scalar(255), -1);
	gtScore = cv::Scalar(0.173, 0.046, 0.213, 0.941);
	table = EvaluationsTools::evaluationMaps(gtMat, inputMat, &out);
	score = EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(table);
	for (uint8_t i = 0; i < 4; ++i)
		score[i] = TestTools::setDigits(score[i], 3);
	BOOST_CHECK_EQUAL(score, gtScore);

}

BOOST_AUTO_TEST_CASE(curveROC) {

	std::vector<double> vector = { 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1,
			0 };
	double area = 0;
	std::vector<cv::Point2f> points = EvaluationsTools::curveROC(vector, &area);
	BOOST_CHECK_EQUAL(0.5, area);

}

//BOOST_AUTO_TEST_CASE(MIXTURE_OF_GAUSSIAN_V1BGS_Evaluation) {
//
//	// best se [0.241025, 1, 0.011, 52.4342]
//
//	cv::Scalar threshold(1, 128, 10);
//	cv::Scalar alpha(0.0, 0.1, 0.01);
//
//	std::string name = "MIXTURE_OF_GAUSSIAN_V1BGS";
//	std::cout << "START EVALUATION OF " << name << std::endl;
//	cv::Scalar bestSets(0, 0, 0); // score, threshold, alpha
//
//	uint count = 1;
//	uint bestCount = 0;
//	for (uint i = threshold[0]; i < threshold[1]; i = i + threshold[2]) {
//		for (double j = alpha[0]; j < alpha[1]; j = j + alpha[2]) {
//			std::vector<double> parans(2);
//			parans[0] = i;
//			parans[1] = j;
//
//			BackGroundSubtraction bkSubtraction(
//			METHOD_MIXTURE_OF_GAUSSIAN_V1BGS,
//					cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), parans);
//
//			cv::Scalar scoreActual = evalutationROCArea(&bkSubtraction);
//			std::cout << " index " << count << "[score,th,alpha,fps] "
//					<< cv::Scalar(scoreActual[0], i, j, scoreActual[1])
//					<< std::endl;
//			if (bestSets[0] < scoreActual[0]) {
//				bestSets = cv::Scalar(scoreActual[0], i, j, scoreActual[1]);
//				bestCount = count;
//			}
//			std::cout << "Bests Results of " << name << " index " << bestCount
//					<< " [score,th,alpha,fps] = " << bestSets << std::endl;
//			count++;
//		}
//	}
//}

// best result [0.186648, 14, 0.04, 63.6608]
//BOOST_AUTO_TEST_CASE(METHOD_ADAPTIVE_BACKGROUND_LEARNING_Evaluation) {
//
//	cv::Scalar threshold(14, 15, 1);
//	cv::Scalar alpha(0.01, 0.2, 0.01);
//
//	std::string name = "METHOD_ADAPTIVE_BACKGROUND_LEARNING";
//	std::cout << "START EVALUATION OF " << name << std::endl;
//	cv::Scalar bestSets(0, 0, 0); // score, threshold, alpha
//
//	uint count = 1;
//	uint bestCount = 0;
//	for (uint i = threshold[0]; i < threshold[1]; i = i + threshold[2]) {
//		for (double j = alpha[0]; j < alpha[1]; j = j + alpha[2]) {
//			std::vector<double> parans(2);
//			parans[0] = i;
//			parans[1] = j;
//
//			BackGroundSubtraction bkSubtraction(
//			METHOD_ADAPTIVE_BACKGROUND_LEARNING,
//					cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), parans);
//
//			cv::Scalar scoreActual = evalutationROCArea(&bkSubtraction);
//
//			std::cout << " index " << count << " [score,th,alpha,fps] "
//					<< cv::Scalar(scoreActual[0], i, j, scoreActual[1])
//					<< std::endl;
//
//			if (bestSets[0] < scoreActual[0]) {
//				bestSets = cv::Scalar(scoreActual[0], i, j, scoreActual[1]);
//				bestCount = count;
//			}
//			std::cout << "Bests Results of " << name << " index " << bestCount
//					<< " [score,th,alpha,fps] = " << bestSets << std::endl;
//			count++;
//		}
//	}
//}

//
//[0.320123, 39, 0.99, 61.9227]
//BOOST_AUTO_TEST_CASE(METHOD_MEDIAN_FILTER_Evaluation) {
//
//	cv::Scalar threshold(30, 70, 1);
//	cv::Scalar alpha(0.01, 1, 0.01);
//
//	std::string name = "METHOD_MEDIAN_FILTER";
//	std::cout << "START EVALUATION OF " << name << std::endl;
//	cv::Scalar bestSets(0, 0, 0, 0); // score, threshold, alpha
//
//	uint count = 1;
//	uint bestCount = 0;
//	for (uint i = threshold[0]; i < threshold[1]; i = i + threshold[2]) {
//		for (double j = alpha[0]; j < alpha[1]; j = j + alpha[2]) {
//			std::vector<double> parans(2);
//			parans[0] = i;
//			parans[1] = j;
//
//			BackGroundSubtraction bkSubtraction(
//			METHOD_MEDIAN_FILTER, cv::Mat::zeros(cv::Size(100, 100), CV_8UC3),
//					parans);
//
//			cv::Scalar scoreActual = evalutationROCArea(&bkSubtraction);
//			std::cout << " index " << count << "[score,th,alpha,fps] "
//					<< cv::Scalar(scoreActual[0], i, j, scoreActual[1])
//					<< std::endl;
//
//			if (bestSets[0] < scoreActual[0]) {
//				bestSets = cv::Scalar(scoreActual[0], i, j, scoreActual[1]);
//			}
//			std::cout << "Bests Results of " << name << " index " << bestCount
//					<< " [score,th,alpha,fps] = " << bestSets << std::endl;
//			count++;
//		}
//	}
//}


//[score,fps] 0.332064 39.0248  - [th,alpha,dilate,erode] [48, 0.99, 2, 2]
//[score,fps] 0.336554 14.191 [th,alpha,dilate,erode] [53, 1, 9, 9]
//[score,fps] 0.336032 16.62371: [th,alpha,dilate,erode] [51, 1, 5, 5]
//[score,fps] 0.334738 16.86391: [th,alpha,dilate,erode] [49, 1, 5, 5]

BOOST_AUTO_TEST_CASE(METHOD_MEDIAN_FILTER_WITH_MORPH_Evaluation) {

	cv::Scalar threshold(45, 50, 1);
	cv::Scalar alpha(0, 1, 0.1);
	cv::Scalar dilate(0, 10, 1);
	cv::Scalar erode(0, 10, 1);

	std::string name = "METHOD_MEDIAN_FILTER+MORPH";
	std::cout << "START EVALUATION OF " << name << std::endl;
	cv::Scalar bestSets(0, 0, 0, 0); // score, threshold, alpha
	cv::Scalar bestSetsConfig(0, 0, 0, 0);
	uint count = 1;
	uint bestCount = 0;
	for (uint i = threshold[0]; i < threshold[1]; i = i + threshold[2])
		for (double j = alpha[0]; j < alpha[1]; j = j + alpha[2])
			for (double k = dilate[0]; k < dilate[1]; k = k + dilate[2]) {
				for (double l = erode[0]; l < erode[1]; l = l + erode[2]) {

					std::vector<double> parans(2);
					parans[0] = i;
					parans[1] = j;

					std::vector<double> morph(2);
					morph[0] = k;
					morph[1] = l;

					BackGroundSubtraction bkSubtraction(
					METHOD_MEDIAN_FILTER,
							cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), parans,
							morph);

					cv::Scalar scoreActual = evalutationROCArea(&bkSubtraction);
					std::cout << " index " << count << "[score,fps] "
							<< scoreActual[0] << " " << scoreActual[1]
							<< "[th,alpha,dilate,erode] "
							<< cv::Scalar(i, j, k, l) << std::endl;

					if (bestSets[0] < scoreActual[0]) {
						bestSets = cv::Scalar(scoreActual[0], scoreActual[1]);
						bestCount = count;
						bestSetsConfig = cv::Scalar(i, j, k, l);
					}
					std::cout << "Bests Results of " << name << " index "
							<< bestCount << "[score,fps] " << bestSets[0] << " "
							<< bestSets[1] << "\n" << "[th,alpha,dilate,erode] "
							<< bestSetsConfig << std::endl;
					count++;
				}
			}
}

//BOOST_AUTO_TEST_CASE(MANUAL_Evaluation) {
//
//	std::string name = "MANUAL EVALUATION";
//	std::cout << "START EVALUATION OF " << name << std::endl;
//
//	std::vector<double> parans(2);
//	parans[0] = 48;
//	parans[1] = 0.99;
//
//	std::vector<double> morph(2);
//	morph[0] = 2;
//	morph[1] = 2;
//
//	BackGroundSubtraction bkSubtraction(
//	METHOD_MEDIAN_FILTER, cv::Mat::zeros(cv::Size(100, 100), CV_8UC3), parans,
//			morph);
//
//	cv::Scalar scoreActual = evalutationROCArea(&bkSubtraction);
//	std::cout << "[score,fps] " << scoreActual[0] << " " << scoreActual[1]
//			<< "[th,alpha,dilate,erode] "
//			<< cv::Scalar(parans[0], parans[1], morph[0], morph[1])
//			<< std::endl;
//
//}
