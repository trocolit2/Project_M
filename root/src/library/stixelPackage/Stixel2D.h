/*
 * Stixel2D.h
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_STIXEL2D_H_
#define SRC_LIBRARY_STIXEL2D_H_

#include <opencv2/core/core.hpp>
#include <iostream>

class Stixel2D {
public:
	Stixel2D();
	Stixel2D(cv::Point2d point1, cv::Point2d point2);
	virtual ~Stixel2D();

	void refreshTopAndBottonPoints(cv::Point2d point1, cv::Point2d point2);

	double getAngle();
	double getSize();
	cv::Point2d getCenter();
	cv::Point2d getTopPoint();
	cv::Point2d getBottonPoint();
	cv::Scalar getLineEquation();

private:

	double angle;
	double size;
	cv::Point2d center;
	cv::Point2d topPoint;
	cv::Point2d bottonPoint;
	cv::Scalar lineEquation;

	void sortTopAndBottonPoints(cv::Point2d *topPoint,
			cv::Point2d *bottonPoint);
	void initStixel(cv::Point2f point1, cv::Point2f point2);

// operators
public:

	bool operator!=(const Stixel2D &other);

	friend std::ostream &operator<<(std::ostream &out,
			const Stixel2D &stixel2D) {
		out << "[" << stixel2D.bottonPoint.x << ", " << stixel2D.bottonPoint.y
				<< "; " << stixel2D.topPoint.x<<", " << stixel2D.topPoint.y << "]";
		return out;
	}

};

#endif /* SRC_LIBRARY_STIXEL2D_H_ */
