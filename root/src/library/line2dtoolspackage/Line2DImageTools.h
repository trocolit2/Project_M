/*
 * Line2DImageTools.h
 *
 *  Created on: Jan 20, 2015
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_LINE2DTOOLSPACKAGE_LINE2DIMAGETOOLS_H_
#define SRC_LIBRARY_LINE2DTOOLSPACKAGE_LINE2DIMAGETOOLS_H_

#include <vector>

#include <opencv2/core/core.hpp>

#include "Line2D.h"

class Line2DImageTools {
 public:
  static cv::Mat extractLine2DFromForeground(
      cv::Mat foreground, std::vector<Line2D> *stixeis, uint64 minPoints = 4,
      cv::Mat showImage = cv::Mat::zeros(0, 0, CV_8UC3));

  static cv::Mat extractLine2DFromBackground(
      cv::Mat background, std::vector<Line2D> *stixeis, cv::Mat showImage =
          cv::Mat::zeros(0, 0, CV_8UC3));

  static std::vector<uint> histogramAngleLine2D(std::vector<Line2D> stixeis,
                                                uint beans, cv::Mat *image = 0);

  static std::vector<Line2D> gethistogramAngleInterval(
      std::vector<Line2D> mainVector, std::vector<uint> histogram,
      uint midleBean, uint intevalSides,
      std::vector<Line2D>* residualVector = 0);

  static std::vector<Line2D> getMaxBeanAngleInteval(
      std::vector<Line2D> mainVector, std::vector<uint> histogram,
      uint intevalSides, std::vector<Line2D>* residualVector = 0);

  static std::vector<Line2D> getMaxBeanAngleIntevalsAdaptative(
      std::vector<Line2D> mainVector, std::vector<uint> histogram,
      std::vector<Line2D>* residualVector = 0);

  static cv::Mat drawStixeis(std::vector<Line2D> stixeis, cv::Mat image =
                                 cv::Mat::zeros(0, 0, CV_8UC3));

  static cv::Scalar colorAngle(double angle);

 private:
  static std::vector<std::vector<cv::Point> > filterByNumberPoints(
      std::vector<std::vector<cv::Point> > contours, uint64 numberPoints);

  static std::vector<Line2D> getLine2DFromLSD(cv::Mat background);

  static cv::Mat drawHistogramAngleLine2D(std::vector<uint> histgram,
                                          cv::Size size = cv::Size(640, 480));
};

#endif /* SRC_LIBRARY_LINE2DTOOLSPACKAGE_LINE2DIMAGETOOLS_H_ */
