/*
 * VanishingPointDetection.cpp
 *
 *  Created on: Mar 14, 2016
 *      Author: tiagotrocoli
 */

#include <VanishingPointDetection.h>

std::vector<cv::Point2f> VanishingPointDetection::detectVanishingPoints(
    cv::Mat image, bool manhattan_world) {

  return applyDetectVP(image,manhattan_world);
}
