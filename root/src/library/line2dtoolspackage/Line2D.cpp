/*
 * Line2D.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#include <line2dtoolspackage/Line2D.h>
#include <Line2DMathTools.h>

Line2D::Line2D() {
  initLine2D(cv::Point2d(0, 0), cv::Point2d(0, 0));
}

Line2D::Line2D(cv::Point2d point1, cv::Point2d point2) {
  initLine2D(point1, point2);
}

Line2D::~Line2D() {
  // TODO Auto-generated destructor stub
}

void Line2D::refreshTopAndBottonPoints(cv::Point2d point1, cv::Point2d point2) {
  initLine2D(point1, point2);
}

double Line2D::angle() {
  return angle_;
}

double Line2D::size() {
  return size_;
}

cv::Point2d Line2D::center() {
  return center_;
}

cv::Point2d Line2D::topPoint() {
  return top_point_;
}

cv::Point2d Line2D::bottonPoint() {
  return botton_point_;
}

cv::Scalar Line2D::lineEquation() {
  return line_equation_;
}

void Line2D::sortTopAndBottonPoints(cv::Point2d* top_point,
                                    cv::Point2d* botton_point) {
  if ((*top_point).y > (*botton_point).y) {
    cv::Point2d temp = (*top_point);
    (*top_point) = (*botton_point);
    (*botton_point) = temp;
  }

}

bool Line2D::operator !=(const Line2D &other) {

  bool result = false;
  if (botton_point_.x != other.botton_point_.x)
    result = true;
  else if (botton_point_.y != other.botton_point_.y)
    result = true;
  else if (top_point_.x != other.top_point_.x)
    result = true;
  else if ((top_point_.y != other.top_point_.y))
    result = true;
  return result;
}

bool Line2D::operator <(const Line2D &other) {

  bool result = false;
  if (line_equation_[0] < other.line_equation_[0])
    result = true;
  else if (line_equation_[2] < other.line_equation_[2])
    result = true;
  else if (line_equation_[1] < other.line_equation_[1])
    result = true;
  return result;
}

void Line2D::initLine2D(cv::Point2f point1, cv::Point2f point2) {
  top_point_ = point1;
  botton_point_ = point2;
  sortTopAndBottonPoints(&top_point_, &botton_point_);

  size_ = Line2DMathTools::calcLenghtFrom2Points(top_point_, botton_point_);
  center_ = Line2DMathTools::calcCenterFrom2Points(top_point_, botton_point_);
  line_equation_ = Line2DMathTools::calcLineEquation2D(top_point_, botton_point_);
  angle_ = Line2DMathTools::calcAngle(line_equation_);

}
