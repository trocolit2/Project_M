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
    static std::vector<cv::Point2f> convergeStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints, uint seed = 0);

    static cv::Point2f convergeStixeisToPointByRANSAC(std::vector<Stixel2D> stixeis, uint sample, uint iteration, float erro, uint seed = 0);
    static cv::Point2f convergeStixeisToPointBySVD(std::vector<Stixel2D> stixeis);

private:

    static cv::Point2f computeStixeisToPointBySVD(std::vector<Stixel2D> stixeis);
};

#endif /* SRC_LIBRARY_VANISHPOINTDETECTION_VPTOOLS_H_ */
