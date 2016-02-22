/*
 * Line2D.h
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_STIXEL2D_H_
#define SRC_LIBRARY_STIXEL2D_H_

#include <opencv2/core/core.hpp>
#include <iostream>

class Line2D {
 public:
  Line2D();
  Line2D(cv::Point2d point1, cv::Point2d point2);
  virtual ~Line2D();

  void refreshTopAndBottonPoints(cv::Point2d point1, cv::Point2d point2);

  double angle();
  double size();
  cv::Point2d center();
  cv::Point2d topPoint();
  cv::Point2d bottonPoint();
  cv::Scalar lineEquation();

 private:

  double angle_;
  double size_;
  cv::Point2d center_;
  cv::Point2d top_point_;
  cv::Point2d botton_point_;
  cv::Scalar line_equation_;

  void sortTopAndBottonPoints(cv::Point2d *topPoint, cv::Point2d *bottonPoint);
  void initLine2D(cv::Point2f point1, cv::Point2f point2);

// operators
 public:

  bool operator!=(const Line2D &other);
  bool operator<(const Line2D &other);

  friend std::ostream &operator<<(std::ostream &out, const Line2D &line2D) {
    out << "[" << line2D.botton_point_.x << ", " << line2D.botton_point_.y << "; "
        << line2D.top_point_.x << ", " << line2D.top_point_.y << "]";
    return out;
  }

};

#endif /* SRC_LIBRARY_STIXEL2D_H_ */
