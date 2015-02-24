/*
 * EvaluationsTools.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: tiagotrocoli
 */

#include "EvaluationsTools.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>

#define EVALUATION_MAP_TP 255
#define EVALUATION_MAP_TN 0
#define EVALUATION_MAP_FP 64
#define EVALUATION_MAP_FN 191

cv::Scalar EvaluationsTools::evaluationMaps(cv::Mat groundThruth, cv::Mat input,
		cv::Mat *imageCheck) {

	cv::Scalar tempCount(0, 0, 0, 0);
	std::vector<cv::Mat> mats;
	cv::Mat sumMat = (3 * groundThruth + input) / 4.0;

	mats.push_back(sumMat == EVALUATION_MAP_FP);
	mats.push_back(sumMat == EVALUATION_MAP_TP);
	mats.push_back(sumMat == EVALUATION_MAP_FN);

	tempCount[0] = cv::sum(mats[1])[0] / 255; //TP
	tempCount[2] = cv::sum(mats[0])[0] / 255; //FP
	tempCount[3] = cv::sum(mats[2])[0] / 255; //FN
	tempCount[1] = groundThruth.size().height * groundThruth.size().width
			- (tempCount[0] + tempCount[2] + tempCount[3]); //TN

	if (imageCheck != 0) {
		mats[1] = mats[1] + mats[0];
		mats[2] = mats[2] + mats[0];
		mats[0] = cv::Mat::zeros(mats[0].size(), CV_8UC1);
		cv::merge(mats, (*imageCheck));
	}

	return tempCount;
}

cv::Scalar EvaluationsTools::calcTPR_FPR_PRECISION_ACCURACY(cv::Scalar table) {

	double tp = table[0];
	double tn = table[1];
	double fp = table[2];
	double fn = table[3];

	double tpr = tp / (tp + fn + fp);
	if ((tp + fn + fp) == 0) {
		tpr = 0;
	}
	double fpr = fp / (fp + tn);
	double precision = tp / (tp + fp);
	if ((tp + fp) == 0) {
		precision = 1;
	}
	double accuracy = (tn + tp) / (tp + fp + tn + fn);
	return cv::Scalar(tpr, fpr, precision, accuracy);
}

std::vector<cv::Point2f> EvaluationsTools::curveROC(std::vector<double> data,
		double *area) {

	std::sort(data.begin(), data.end());
	std::vector<cv::Point2f> points;
	double total = data.size();
	for (uint i = 0; i < total; ++i) {
		uint count = 0;
		for (uint y = 0; y < total; ++y) {
			if (data[y] < data[i]) {
				count++;
			}
		}
		points.push_back(cv::Point2f(data[i], count * 1.0 / total));
	}
	points.push_back(cv::Point2f(1, 1));
	points.push_back(cv::Point2f(1, 0));
	points.push_back(cv::Point2f(0, 0));

	if (area != 0)
		(*area) = cv::contourArea(points);

	return points;
}
