/*
 * VideoTools.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: tiagotrocoli
 */

#include "VideoTools.h"

#include <iostream>
#include <string>
#include <RegexStringTools.h>

using namespace std;

bool VideoTools::isNextImageSequenceFrame() {

	bool control = false;
	std::string sequenceNumber = RegexStringTools::fillSizeDigit(
			this->frameNext, this->sequenceDigitSize);

	std::string imagePath = "";
	if (this->path.size() != 0)
		imagePath = this->path + "/";

	imagePath = imagePath + this->prefixName;
	imagePath = imagePath + sequenceNumber + this->sufixName;
	cv::Mat tempImage = cv::imread(imagePath);
	if (this->frameMax == 0 || this->frameNext < this->frameMax)
		if (tempImage.size().height > 0 || tempImage.size().width > 0) {
			tempImage.copyTo(this->frame);
			control = true;
			++this->frameNext;
			this->frameCurrent = this->frameNext - 1;
		}

	return control;
}

bool VideoTools::isNextVideoFrame() {
	bool control = false;
	std::string imagePath = "";

	if (this->path.size() != 0)
		imagePath = this->path + "/";
	imagePath = imagePath + this->videoName;
	cv::Mat tempImage;

	if (!videoCapture.isOpened()) {
		videoCapture = cv::VideoCapture(imagePath);
		videoCapture.set(CV_CAP_PROP_POS_FRAMES, this->frameCurrent);
	}

	videoCapture >> tempImage;

	if (this->frameMax == 0 || this->frameCurrent < this->frameMax)
		if (tempImage.size().height > 0 || tempImage.size().width > 0) {
			tempImage.copyTo(this->frame);
			control = true;
			this->frameCurrent++;
		}

	return control;
}

void VideoTools::inputFrameControl(std::vector<std::string> fileInfo) {
	this->frameCurrent = 0;
	if (fileInfo.size() > 1)
		this->frameCurrent = atoi(fileInfo[1].c_str());
	this->frameNext = this->frameCurrent;
	this->frameMax = 0;
	if (fileInfo.size() > 2)
		this->frameMax = this->frameCurrent + atoi(fileInfo[2].c_str());
}

VideoTools::VideoTools(std::vector<std::string> fileInfo) {
	initVideoTools(fileInfo);
}

void VideoTools::initVideoTools(std::vector<std::string> fileInfo) {

	char tempChar = ((char) fileInfo[0].c_str()[1]);
	std::vector<std::string> temp;
	this->flag = tempChar;
	if (tempChar == INPUT_READ_IMAGE_SEQUENCE) {

		temp.push_back(fileInfo[1]);
		if (fileInfo.size() > 2)
			temp.push_back(fileInfo[2]);
		if (fileInfo.size() > 3)
			temp.push_back(fileInfo[3]);
		readSequenceFrames(temp);
	} else if (tempChar == INPUT_READ_VIDEO) {

		temp.push_back(fileInfo[1]);
		if (fileInfo.size() > 2)
			temp.push_back(fileInfo[2]);
		if (fileInfo.size() > 3)
			temp.push_back(fileInfo[3]);
		readVideo(temp);

	} else if (tempChar == INPUT_READ_CAMERA) {

		temp.push_back(fileInfo[1]);
		if (fileInfo.size() > 2)
			temp.push_back(fileInfo[2]);
		readDeviceCamera(temp);

	} else {
		exit(EXIT_FAILURE);
	}
}

std::vector<std::string> VideoTools::getFileInfo() {

	std::vector<std::string> temp;
	std::string tempStr = { this->flag };
	temp.push_back(tempStr); //FLAG -> position 0

	if (this->flag == INPUT_READ_IMAGE_SEQUENCE) {
		temp.push_back(this->path); // PATH FOLDER -> position 1
		temp.push_back(this->prefixName); //PREFIX NAME -> position 2
		temp.push_back(this->sufixName); // SUFIX NAME -> position 3
		temp.push_back(std::to_string(sequenceDigitSize)); // Digit SIZE -> position 4
	} else if (this->flag == INPUT_READ_VIDEO) {
		temp.push_back(this->path); // PATH FOLDER -> position 1
		temp.push_back(this->videoName); ////PREFIX NAME -> position 2
	} else {

	}

	if (this->flag != INPUT_READ_CAMERA) {
		temp.push_back(std::to_string(frameCurrent)); // POSITION 5 IN SEQUENCE, POSITION 3 IN VIDEO
		temp.push_back(std::to_string(frameMax)); // POSITION 6 IN SEQUENCE, POSITION 4 IN VIDEO
	}

	return temp;

}

cv::Mat VideoTools::getFrame() {
	return this->frame;
}

bool VideoTools::isNextFrame() {
	bool control = false;
	if (this->flag == INPUT_READ_IMAGE_SEQUENCE) {
		control = isNextImageSequenceFrame();
	} else if (this->flag == INPUT_READ_VIDEO) {
		control = isNextVideoFrame();
	} else {

	}
	return control;
}

void VideoTools::readVideo(std::vector<std::string> fileInfo) {
	std::vector<std::string> vectorPath;
	unsigned int flagPath = 0;
	vectorPath = RegexStringTools::regexGet(fileInfo[0], regexAssemble(),
			&flagPath);

	inputFrameControl(fileInfo);
	if (REGEX_PATH_FILE_FLAG == flagPath) {
		this->path = vectorPath[0];
		this->videoName = vectorPath[1];
	} else if (REGEX_ONLY_FILE_FLAG == flagPath) {
		this->path = "";
		this->videoName = vectorPath[0];
	}
}

void VideoTools::readDeviceCamera(std::vector<std::string> fileInfo) {
}

void VideoTools::readSequenceFrames(std::vector<std::string> fileInfo) {

	std::vector<std::string> vectorPath;
	unsigned int flagPath = 0;
	vectorPath = RegexStringTools::regexGet(fileInfo[0], regexAssemble(),
			&flagPath);

	inputFrameControl(fileInfo);

	if (REGEX_PATH_COMPLETE_FLAG == flagPath) {
		this->path = vectorPath[0];
		this->prefixName = vectorPath[1];
		this->sequenceDigitSize = std::stoi(vectorPath[2]);
		this->sufixName = vectorPath[3];

	} else if (REGEX_WITHOUT_PATH_FLAG == flagPath) {
		this->path = "";
		this->prefixName = vectorPath[0];
		this->sequenceDigitSize = std::stoi(vectorPath[1]);
		this->sufixName = vectorPath[2];

	} else if (REGEX_WITHOUT_PREFIX_FLAG == flagPath) {
		this->path = vectorPath[0];
		this->prefixName = "";
		this->sequenceDigitSize = std::stoi(vectorPath[1]);
		this->sufixName = vectorPath[2];

	} else if (REGEX_WITHOUT_PREFIX_AND_PATH_FLAG == flagPath) {
		this->path = "";
		this->prefixName = "";
		this->sequenceDigitSize = std::stoi(vectorPath[0]);
		this->sufixName = vectorPath[1];
	}

}

std::string VideoTools::regexAssemble() {
	std::string allregex = std::string(REGEX_WITHOUT_PREFIX_AND_PATH) + "|"
			+ std::string(REGEX_WITHOUT_PREFIX) + "|"
			+ std::string(REGEX_PATH_COMPLETE) + "|"
			+ std::string(REGEX_WITHOUT_PATH) + "|"
			+ std::string(REGEX_PATH_FILE) + "|" + std::string(REGEX_ONLY_FILE);
	return allregex;
}

VideoTools::~VideoTools() {
}
