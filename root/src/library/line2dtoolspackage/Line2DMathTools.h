/*
 * Line2DMathTools.h
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_LINETOOLS_H_
#define SRC_LIBRARY_LINETOOLS_H_

#include <opencv2/core/core.hpp>

class Line2DMathTools {
 public:

  static cv::Scalar calcLineEquation2D(cv::Point2d point1, cv::Point2d point2);
  static cv::Scalar calcNormlizeLineEquation(cv::Scalar lineEquation);
  static double calcLenghtFrom2Points(cv::Point2f point1, cv::Point2f point2);
  static cv::Point2d calcCenterFrom2Points(cv::Point2d point1,
                                           cv::Point2d point2);

  static double calcAngle(cv::Scalar lineEuclidian);
  static double calcDistanceLine2Point(cv::Scalar lineEuclidian,
                                       cv::Point2f point,
                                       cv::Point2f* closePoint = 0);

};

#endif /* SRC_LIBRARY_LINETOOLS_H_ */
