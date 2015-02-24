/*
 * VideoTools_test.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: tiagotrocoli
 */
#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "VideoTools_test"
//VERY IMPORTANT - include this last

#include <cmath>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <library/VideoTools.h>
#include <library/RegexStringTools.h>

#include "tools/TestTools.h"

//================================
// VIDEO TEST FILES INFO
//================================

std::vector<std::string> videoPathCompleteWithInitFrameGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = "/path/to/video/file";
	vectorFileInfo[2] = "name.mp4";
	vectorFileInfo[3] = "15";
	vectorFileInfo[4] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	(*input).push_back(vectorFileInfo[3]);
	return vectorFileInfo;
}

std::vector<std::string> videoPathCompleteWithInitFrameAndLengthGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = "/path/to/video/file";
	vectorFileInfo[2] = "name.mp4";
	vectorFileInfo[3] = "15";
	vectorFileInfo[4] = "100";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	(*input).push_back(vectorFileInfo[3]);
	(*input).push_back(
			std::to_string(
					atoi(vectorFileInfo[4].c_str())
							- atoi(vectorFileInfo[3].c_str())));
	return vectorFileInfo;
}

std::vector<std::string> videoPathCompleteGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = "/path/to/video/file";
	vectorFileInfo[2] = "name.mp4";
	vectorFileInfo[3] = "0";
	vectorFileInfo[4] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	return vectorFileInfo;
}

std::vector<std::string> videoWithoutPathGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = "";
	vectorFileInfo[2] = "name.mp4";
	vectorFileInfo[3] = "13";
	vectorFileInfo[4] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[2]);
	(*input).push_back(vectorFileInfo[3]);
	return vectorFileInfo;
}

BOOST_AUTO_TEST_CASE(videoPathCompleteTestCase) {
	std::vector<std::string> input, groundTruth = videoPathCompleteGroundTruth(
			&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());

}

BOOST_AUTO_TEST_CASE(videoWithoutPathTestCase) {
	std::vector<std::string> input, groundTruth = videoWithoutPathGroundTruth(
			&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());

}

BOOST_AUTO_TEST_CASE(videoPathCompleteWithInitFrameTestCase) {
	std::vector<std::string> input, groundTruth =
			videoPathCompleteWithInitFrameGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());

}

BOOST_AUTO_TEST_CASE(videoPathCompleteWithInitFrameAndLengthTestCase) {
	std::vector<std::string> input, groundTruth =
			videoPathCompleteWithInitFrameAndLengthGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());

}

//================================
// IMAGE SEQUENCE TEST FILES INFO
//================================

std::vector<std::string> imageSequencePathCompleteWithInitFrameAndLengthGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "/path/to/images/sequence";
	vectorFileInfo[2] = "PREFIX";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3"; //size ou digit
	vectorFileInfo[5] = "4";
	vectorFileInfo[6] = "20";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(
			vectorFileInfo[1] + "/" + vectorFileInfo[2] + "|"
					+ vectorFileInfo[4] + "|" + vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[5]);
	(*input).push_back(
			std::to_string(
					atoi(vectorFileInfo[6].c_str())
							- atoi(vectorFileInfo[5].c_str())));
	return vectorFileInfo;
}

std::vector<std::string> imageSequencePathCompleteNoInitFrameGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "/path/to/images/sequence";
	vectorFileInfo[2] = "PREFIX";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3";
	vectorFileInfo[5] = "0";
	vectorFileInfo[6] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(
			vectorFileInfo[1] + "/" + vectorFileInfo[2] + "|"
					+ vectorFileInfo[4] + "|" + vectorFileInfo[3]);
	return vectorFileInfo;
}

std::vector<std::string> imageSequencePathCompleteGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "/path/to/images/sequence";
	vectorFileInfo[2] = "PREFIX";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3";
	vectorFileInfo[5] = "10";
	vectorFileInfo[6] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(
			vectorFileInfo[1] + "/" + vectorFileInfo[2] + "|"
					+ vectorFileInfo[4] + "|" + vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[5]);
	return vectorFileInfo;
}

std::vector<std::string> imageSequenceWithoutPathGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "";
	vectorFileInfo[2] = "PREFIX";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3";
	vectorFileInfo[5] = "10";
	vectorFileInfo[6] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(
			vectorFileInfo[2] + "|" + vectorFileInfo[4] + "|"
					+ vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[5]);
	return vectorFileInfo;
}

std::vector<std::string> imageSequenceWithoutPrefixGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "/path/to/images/sequence";
	vectorFileInfo[2] = "";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3";
	vectorFileInfo[5] = "10";
	vectorFileInfo[6] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(
			vectorFileInfo[1] + "/" + vectorFileInfo[2] + "|"
					+ vectorFileInfo[4] + "|" + vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[5]);
	return vectorFileInfo;
}

std::vector<std::string> imageSequenceWithoutPrefixAndPathGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(7);
	vectorFileInfo[0] = "S";
	vectorFileInfo[1] = "";
	vectorFileInfo[2] = "";
	vectorFileInfo[3] = "sufix.jpg";
	vectorFileInfo[4] = "3";
	vectorFileInfo[5] = "10";
	vectorFileInfo[6] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back("|" + vectorFileInfo[4] + "|" + vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[5]);
	return vectorFileInfo;
}

BOOST_AUTO_TEST_CASE(imageSequencePathCompleteTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequencePathCompleteGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

BOOST_AUTO_TEST_CASE(imageSequenceWithoutPathTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequenceWithoutPathGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

BOOST_AUTO_TEST_CASE(imageSequenceWithoutPrefixTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequenceWithoutPrefixGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

BOOST_AUTO_TEST_CASE(imageSequenceWithoutPrefixAndPathTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequenceWithoutPrefixAndPathGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

BOOST_AUTO_TEST_CASE(imageSequencePathCompleteNoInitFrameTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequencePathCompleteNoInitFrameGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

BOOST_AUTO_TEST_CASE(imageSequencePathCompleteWithInitFrameAndLengthTestCase) {

	std::vector<std::string> input, groundTruth =
			imageSequencePathCompleteWithInitFrameAndLengthGroundTruth(&input);
	VideoTools bla(input);
	std::vector<std::string> output = bla.getFileInfo();
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruth.begin(), groundTruth.end(),
			output.begin(), output.end());
}

//=========================================
// GET FRAME TEST CASES FOR IMAGE SEQUENCE
//=========================================

std::vector<std::string> getFrameImageSequenceSimplesGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(7);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "S6-T3-H.";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "5";
	inputTemp[5] = "0";
	inputTemp[6] = "1";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);
	(*input).push_back(inputTemp[6]);

	std::vector<std::string> groundTruthVector;
	std::string inputStr = inputTemp[1] + "/" + inputTemp[2];
	inputStr = inputStr
			+ RegexStringTools::fillSizeDigit(std::stoi(inputTemp[5]),
					std::stoi(inputTemp[4]));
	inputStr = inputStr + inputTemp[3];

	groundTruthVector.push_back(inputStr);

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceSimplesTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceSimplesGroundThruth(&input);
	VideoTools videoTools(input);
	bool outControlFrame = videoTools.isNextFrame();

	cv::Mat imageGroundTruth = cv::imread(groundTruth[0]);
	cv::Mat imageGetFrame = videoTools.getFrame();

	std::vector<uint8_t> outVector = TestTools::convertmat2vector(
			imageGetFrame);
	std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
			imageGroundTruth);

//	cv::imshow("OUT IMAGE", imageGetFrame);
//	cv::imshow("GT IMAGE", imageGroundTruth);
//	cv::waitKey();

	BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
			gtVector.begin(), gtVector.end());
	BOOST_CHECK_EQUAL(outControlFrame, true);
}

std::vector<std::string> getFrameImageSequenceWithSizeSequence7sGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(7);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "S6-T3-H.";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "5";
	inputTemp[5] = "0";
	inputTemp[6] = "7";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);
	(*input).push_back(inputTemp[6]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	for (int i = 0; i < std::stoi(inputTemp[6]); ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceWithSizeSequence7sTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceWithSizeSequence7sGroundThruth(&input);
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	while (videoTools.isNextFrame()) {
		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
		//std::cout << "\nGT PATH IMAGE SEQUENCE: " << groundTruth[testCount]
		//			<< std::endl;
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

//		cv::imshow("OUT IMAGE", imageGetFrame);
//		cv::imshow("GT IMAGE", imageGroundTruth);
//		cv::waitKey();

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		testCount++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);

}

std::vector<std::string> getFrameImageSequenceWithInfiniteSizeSequenceGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(7);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "S6-T3-H.";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "5";
	inputTemp[5] = "0";
	inputTemp[6] = "0";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);
	(*input).push_back(inputTemp[6]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	uint8_t sequenceSizeGroundTruth = 10;
	for (int i = 0; i < sequenceSizeGroundTruth; ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceWithInfiniteSizeSequenceTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceWithInfiniteSizeSequenceGroundThruth(&input);
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	while (videoTools.isNextFrame()) {
		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
//		std::cout << "\nGT PATH IMAGE SEQUENCE: " << groundTruth[testCount]
//				<< std::endl;
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

		//		cv::imshow("OUT IMAGE", imageGetFrame);
		//		cv::imshow("GT IMAGE", imageGroundTruth);
		//		cv::waitKey();

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		testCount++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);
}

std::vector<std::string> getFrameImageSequenceWithoutInitControlGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(5);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "S6-T3-H.";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "5";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	uint8_t sequenceSizeGroundTruth = 10;
	for (int i = 0; i < sequenceSizeGroundTruth; ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceWithoutInitControl) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceWithoutInitControlGroundThruth(&input);
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	while (videoTools.isNextFrame()) {
		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
//		std::cout << "\nGT PATH IMAGE SEQUENCE: " << groundTruth[testCount]
//				<< std::endl;
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

		//		cv::imshow("OUT IMAGE", imageGetFrame);
		//		cv::imshow("GT IMAGE", imageGroundTruth);
		//		cv::waitKey();

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		testCount++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);
}

std::vector<std::string> getFrameImageSequenceInit2SizeDigit2InfinitGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(6);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "SizeDigit";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "2";
	inputTemp[5] = "2";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	uint8_t sequenceSizeGroundTruth = 4;
	for (int i = std::stoi(inputTemp[5]);
			i < std::stoi(inputTemp[5]) + sequenceSizeGroundTruth; ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceInit2SizeDigit2InfinitTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceInit2SizeDigit2InfinitGroundThruth(&input);
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	while (videoTools.isNextFrame()) {
		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
//		std::cout << "\nGT PATH IMAGE SEQUENCE: " << groundTruth[testCount]
//				<< std::endl;
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

		//		cv::imshow("OUT IMAGE", imageGetFrame);
		//		cv::imshow("GT IMAGE", imageGroundTruth);
		//		cv::waitKey();

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		testCount++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);
}

std::vector<std::string> getFrameImageSequenceInit1SizeDigit1Length4GroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(7);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "1";
	inputTemp[5] = "1";
	inputTemp[6] = "4";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);
	(*input).push_back(inputTemp[6]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	uint8_t sequenceSizeGroundTruth = std::stoi(inputTemp[6]);
	for (int i = std::stoi(inputTemp[5]);
			i < std::stoi(inputTemp[5]) + sequenceSizeGroundTruth; ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceInit1SizeDigit1Length4TestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceInit1SizeDigit1Length4GroundThruth(&input);
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	while (videoTools.isNextFrame()) {
		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
//		std::cout << "\nGT PATH IMAGE SEQUENCE: " << groundTruth[testCount]
//				<< std::endl;
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

		//		cv::imshow("OUT IMAGE", imageGetFrame);
		//		cv::imshow("GT IMAGE", imageGroundTruth);
		//		cv::waitKey();

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		testCount++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);
}

std::vector<std::string> getFrameImageSequenceAndCheckFileInfoGroundThruth(
		std::vector<std::string> *input) {

	std::vector<std::string> inputTemp(7);
	inputTemp[0] = "S"; //flag
	inputTemp[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/imageSequence"; //path
	inputTemp[2] = "";
	inputTemp[3] = ".jpeg";
	inputTemp[4] = "1";
	inputTemp[5] = "1";
	inputTemp[6] = "4";
	(*input).push_back("-" + inputTemp[0]);
	(*input).push_back(
			inputTemp[1] + "/" + inputTemp[2] + "|" + inputTemp[4] + "|"
					+ inputTemp[3]);
	(*input).push_back(inputTemp[5]);
	(*input).push_back(inputTemp[6]);

	std::vector<std::string> groundTruthVector;
	std::string pathPrefix = inputTemp[1] + "/" + inputTemp[2];

	uint8_t sequenceSizeGroundTruth = std::stoi(inputTemp[6]);
	for (int i = std::stoi(inputTemp[5]);
			i < std::stoi(inputTemp[5]) + sequenceSizeGroundTruth; ++i) {
		std::string inputStr = RegexStringTools::fillSizeDigit(i,
				std::stoi(inputTemp[4]));
		groundTruthVector.push_back(pathPrefix + inputStr + inputTemp[3]);
	}

	return groundTruthVector;
}

BOOST_AUTO_TEST_CASE(getFrameImageSequenceAndCheckFileInfoTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameImageSequenceAndCheckFileInfoGroundThruth(&input);
	std::vector<std::string> outFileInfo;
	VideoTools videoTools(input);

	unsigned int testCount = 0;
	int testCurrent = std::stoi(input[2]);
	while (videoTools.isNextFrame()) {
		outFileInfo = videoTools.getFileInfo();

		cv::Mat imageGroundTruth = cv::imread(groundTruth[testCount]);
		cv::Mat imageGetFrame = videoTools.getFrame();

		std::vector<uint8_t> outVector = TestTools::convertmat2vector(
				imageGetFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				imageGroundTruth);

		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		BOOST_CHECK_EQUAL(testCurrent, std::stoi(outFileInfo[5]));
		testCount++;
		testCurrent++;
	}
	BOOST_CHECK_EQUAL(groundTruth.size(), testCount);
}


//=========================================
// GET FRAME TEST CASES FOR VIDEO SEQUENCE
//=========================================


std::vector<std::string> getFrameVideoPathCompleteInitInfinitGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/videoInputTest";
	vectorFileInfo[2] = "video31s.mp4";
	vectorFileInfo[3] = "0";

	vectorFileInfo[4] = "0";
	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);

	std::vector<std::string> groundTruth;
	groundTruth.push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	groundTruth.push_back(vectorFileInfo[3]); //init frame
	groundTruth.push_back(vectorFileInfo[4]); //size
	return groundTruth;
}

BOOST_AUTO_TEST_CASE(getFrameVideoPathCompleteInitInfinitTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameVideoPathCompleteInitInfinitGroundTruth(&input);
	std::vector<std::string> outFileInfo;
	VideoTools videoTools(input);
	cv::VideoCapture cap(groundTruth[0]); // open the default camera

	//std::cout << " Video PATH " << groundTruth[0] << std::endl;
	if (!cap.isOpened())  // check if we succeeded
		EXIT_FAILURE;

	cv::Mat outFrame;
	while (videoTools.isNextFrame()) {
		cap >> outFrame; // get a new frame from camera
		std::vector<uint8_t> outVector = TestTools::convertmat2vector(outFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				videoTools.getFrame());
		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
	}
	cap.release();

}

std::vector<std::string> getFrameVideoPathCompleteInit400AndInfinitGroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/videoInputTest";
	vectorFileInfo[2] = "video31s.mp4";
	vectorFileInfo[3] = "400";
	vectorFileInfo[4] = "0";

	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	(*input).push_back(vectorFileInfo[3]);

	std::vector<std::string> groundTruth;
	groundTruth.push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	groundTruth.push_back(vectorFileInfo[3]); //init frame
	groundTruth.push_back(vectorFileInfo[4]); //size
	return groundTruth;
}

BOOST_AUTO_TEST_CASE(getFrameVideoPathCompleteInit400AndInfinitTestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameVideoPathCompleteInit400AndInfinitGroundTruth(&input);
	std::vector<std::string> outFileInfo;
	VideoTools videoTools(input);
	cv::VideoCapture cap(groundTruth[0]); // open the default camera

	//std::cout << " Video PATH " << groundTruth[0] << std::endl;
	if (!cap.isOpened())  // check if we succeeded
		EXIT_FAILURE;
	cap.set(CV_CAP_PROP_POS_FRAMES, std::stoi(groundTruth[1]));

	cv::Mat outFrame;

	while (videoTools.isNextFrame()) {
		cap >> outFrame; // get a new frame from camera
		std::vector<uint8_t> outVector = TestTools::convertmat2vector(outFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				videoTools.getFrame());
		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
	}
	cap.release();
}

std::vector<std::string> getFrameVideoPathCompleteInit100AndSize100GroundTruth(
		std::vector<std::string> *input) {

	std::vector<std::string> vectorFileInfo(5);
	vectorFileInfo[0] = "V";
	vectorFileInfo[1] = std::string(PATH_RELATIVE_ROOT_TESTBIN)
			+ "resource/videoInputTest";
	vectorFileInfo[2] = "video31s.mp4";
	vectorFileInfo[3] = "100";
	vectorFileInfo[4] = "100";

	(*input).push_back("-" + vectorFileInfo[0]);
	(*input).push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	(*input).push_back(vectorFileInfo[3]);
	(*input).push_back(vectorFileInfo[4]);

	std::vector<std::string> groundTruth;
	groundTruth.push_back(vectorFileInfo[1] + "/" + vectorFileInfo[2]);
	groundTruth.push_back(vectorFileInfo[3]); //init frame
	groundTruth.push_back(vectorFileInfo[4]); //size
	return groundTruth;
}

BOOST_AUTO_TEST_CASE(getFrameVideoPathCompleteInit100AndSize100TestCase) {

	std::vector<std::string> input, groundTruth =
			getFrameVideoPathCompleteInit100AndSize100GroundTruth(&input);
	std::vector<std::string> outFileInfo;
	VideoTools videoTools(input);
	cv::VideoCapture cap(groundTruth[0]); // open the default camera

	//std::cout << " Video PATH " << groundTruth[0] << std::endl;
	if (!cap.isOpened())  // check if we succeeded
		EXIT_FAILURE;
	cap.set(CV_CAP_PROP_POS_FRAMES, std::stoi(groundTruth[1]));

	int sizeOfFramesGT = std::stoi(groundTruth[2]);
	int sizeOfFramesCount = 0;

	cv::Mat outFrame;

	while (videoTools.isNextFrame()) {
		cap >> outFrame; // get a new frame from camera
		std::vector<uint8_t> outVector = TestTools::convertmat2vector(outFrame);
		std::vector<uint8_t> gtVector = TestTools::convertmat2vector(
				videoTools.getFrame());
		BOOST_CHECK_EQUAL_COLLECTIONS(outVector.begin(), outVector.end(),
				gtVector.begin(), gtVector.end());
		sizeOfFramesCount++;
	}
	BOOST_CHECK_EQUAL(sizeOfFramesGT, sizeOfFramesCount);
	cap.release();
}
