/*
 * Line2DMathTools.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#include "Line2DMathTools.h"
#include <cmath>
#include <iostream>

cv::Scalar Line2DMathTools::calcLineEquation2D(cv::Point2d point1,
                                               cv::Point2d point2) {

  double a, b, c;
  a = point2.x - point1.x;
  if (a != 0) {
    a = (point2.y - point1.y) / a;
    b = -1;
    c = point2.y - a * point2.x;
  } else {
    a = -1;
    c = point2.x;
    b = 0;
  }
  cv::Scalar temp(a, b, c);
  return temp;
}

double Line2DMathTools::calcLenghtFrom2Points(cv::Point2f point1,
                                              cv::Point2f point2) {
  double size = (point1.x - point2.x) * (point1.x - point2.x);
  size += (point1.y - point2.y) * (point1.y - point2.y);
  size = sqrt(size);
  return size;
}

cv::Point2d Line2DMathTools::calcCenterFrom2Points(cv::Point2d point1,
                                                   cv::Point2d point2) {
  cv::Point2f center;
  center.x = (point1.x - point2.x) / 2 + point2.x;
  center.y = (point1.y - point2.y) / 2 + point2.y;
  return center;
}

double Line2DMathTools::calcAngle(cv::Scalar lineEuclidian) {
  double out = -1;
  if (lineEuclidian[1] == 0) {
    out = 90;
  } else {
    out = atan(lineEuclidian[0]);
    out = out * 180.0 / M_PI;
    if (out < 0) {
      out = 180 + out;
    }
  }
  return out;
}

cv::Scalar Line2DMathTools::calcNormlizeLineEquation(cv::Scalar lineEquation) {
  double norm = sqrt(
      lineEquation[0] * lineEquation[0] + lineEquation[1] * lineEquation[1]);
  cv::Scalar temp(lineEquation[0] / norm, lineEquation[1] / norm,
                  lineEquation[2] / norm);
  return temp;
}

double Line2DMathTools::calcDistanceLine2Point(cv::Scalar line,
                                               cv::Point2f point,
                                               cv::Point2f* closePoint) {

  double distance;
  if (closePoint != 0) {
    closePoint->x = line[1] * (line[1] * point.x - line[0] * point.y)
        - line[0] * line[2];
    closePoint->x = closePoint->x / (line[1] * line[1] + line[0] * line[0]);

    closePoint->y = line[0] * (-line[1] * point.x + line[0] * point.y)
        - line[1] * line[2];
    closePoint->y = closePoint->y / (line[1] * line[1] + line[0] * line[0]);

    distance = calcLenghtFrom2Points(point, (*closePoint));
  } else {
    distance = abs(line[0] * point.x + line[1] * point.y + line[2]);
    distance = distance / sqrt(line[0] * line[0] + line[1] * line[1]);
  }
  return distance;
}

