/*
 * EvaluationsTools.h
 *
 *  Created on: Jan 12, 2015
 *      Author: tiagotrocoli
 */

#ifndef TEST_TOOLS_EVALUATIONSTOOLS_H_
#define TEST_TOOLS_EVALUATIONSTOOLS_H_

#include <opencv2/core/core.hpp>
#include <vector>

class EvaluationsTools {
public:

	static cv::Scalar evaluationMaps(cv::Mat groundThruth, cv::Mat input,
			cv::Mat *imageCheck = 0);
	static cv::Scalar calcTPR_FPR_PRECISION_ACCURACY(cv::Scalar table);
	static std::vector<cv::Point2f> curveROC(std::vector<double> data,
			double *area = 0);
};

#endif /* TEST_TOOLS_EVALUATIONSTOOLS_H_ */
