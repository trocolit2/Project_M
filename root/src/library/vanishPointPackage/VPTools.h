/*
 * VPTools.h
 *
 *  Created on: Mar 16, 2015
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_VANISHPOINTDETECTION_VPTOOLS_H_
#define SRC_LIBRARY_VANISHPOINTDETECTION_VPTOOLS_H_

#include <library/stixelPackage/Stixel2D.h>

#include <opencv2/core/core.hpp>
#include <vector>

class VPTools {
public:
    static std::vector<cv::Point2f> convertStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints, uint seed = 0);
};

#endif /* SRC_LIBRARY_VANISHPOINTDETECTION_VPTOOLS_H_ */
