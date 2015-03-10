/*
 * Stixel2D.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: tiagotrocoli
 */

#include <LineTools.h>
#include <Stixel2D.h>

Stixel2D::Stixel2D() {
    initStixel(cv::Point2d(0, 0), cv::Point2d(0, 0));
}

Stixel2D::Stixel2D(cv::Point2d point1, cv::Point2d point2) {
    initStixel(point1, point2);
}

Stixel2D::~Stixel2D() {
    // TODO Auto-generated destructor stub
}

void Stixel2D::refreshTopAndBottonPoints(cv::Point2d point1, cv::Point2d point2) {
    initStixel(point1, point2);
}

double Stixel2D::getAngle() {
    return this->angle;
}

double Stixel2D::getSize() {
    return this->size;
}

cv::Point2d Stixel2D::getCenter() {
    return this->center;
}

cv::Point2d Stixel2D::getTopPoint() {
    return this->topPoint;
}

cv::Point2d Stixel2D::getBottonPoint() {
    return this->bottonPoint;
}

cv::Scalar Stixel2D::getLineEquation() {
    return this->lineEquation;
}

void Stixel2D::sortTopAndBottonPoints(cv::Point2d* topPoint, cv::Point2d* bottonPoint) {
    if ((*topPoint).y > (*bottonPoint).y) {
        cv::Point2d temp = (*topPoint);
        (*topPoint) = (*bottonPoint);
        (*bottonPoint) = temp;
    }

}

bool Stixel2D::operator !=(const Stixel2D &other) {

    bool result = false;
    if (this->bottonPoint.x != other.bottonPoint.x)
        result = true;
    else if (this->bottonPoint.y != other.bottonPoint.y)
        result = true;
    else if (this->topPoint.x != other.topPoint.x)
        result = true;
    else if ((this->topPoint.y != other.topPoint.y))
        result = true;
    return result;
}

bool Stixel2D::operator <(const Stixel2D &other) {

    bool result = false;
    if (this->lineEquation[0] < other.lineEquation[0])
        result = true;
    else if (this->lineEquation[2] < other.lineEquation[2])
        result = true;
    else if (this->lineEquation[1] < other.lineEquation[1])
        result = true;
    return result;
}

void Stixel2D::initStixel(cv::Point2f point1, cv::Point2f point2) {
    this->topPoint = point1;
    this->bottonPoint = point2;
    sortTopAndBottonPoints(&this->topPoint, &this->bottonPoint);

    this->size = LineTools::calcLenghtFrom2Points(this->topPoint, this->bottonPoint);
    this->center = LineTools::calcCenterFrom2Points(this->topPoint, this->bottonPoint);
    this->lineEquation = LineTools::calcLineEquation2D(this->topPoint, this->bottonPoint);
    this->angle = LineTools::calcAngle(this->lineEquation);

}
