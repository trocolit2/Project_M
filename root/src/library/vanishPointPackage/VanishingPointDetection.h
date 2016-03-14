/*
 * VanishingPointDetection.h
 *
 *  Created on: Mar 14, 2016
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_VANISHPOINTPACKAGE_VANISHINGPOINTDETECTION_H_
#define SRC_LIBRARY_VANISHPOINTPACKAGE_VANISHINGPOINTDETECTION_H_

#include <vector>
#include <string>

#include <opencv2/core/core.hpp>

class VanishingPointDetection {

 public:
  virtual ~VanishingPointDetection()=0;

  std::vector<cv::Point2f> detectVanishingPoints(
      cv::Mat image, bool manhattan_world = true);
  virtual std::string methodName();

 private:
  virtual std::vector<cv::Point2f> applyDetectVP(cv::Mat image,
                                                 bool manhattan_world)=0;

};

#endif /* SRC_LIBRARY_VANISHPOINTPACKAGE_VANISHINGPOINTDETECTION_H_ */
