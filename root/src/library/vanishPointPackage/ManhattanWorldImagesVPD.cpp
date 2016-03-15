/*
 * ManhattanWorldImagesVPD.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: tiagotrocoli
 */

#include "ManhattanWorldImagesVPD.h"

ManhattanWorldImagesVPD::~ManhattanWorldImagesVPD() {
  // TODO Auto-generated destructor stub
}

ManhattanWorldImagesVPD::ManhattanWorldImagesVPD() {
  // TODO Auto-generated constructor stub

}

ManhattanWorldImagesVPDRANSAC::~ManhattanWorldImagesVPDRANSAC() {
}

ManhattanWorldImagesVPDRANSAC::ManhattanWorldImagesVPDRANSAC() {
}

std::vector<cv::Point3f> ManhattanWorldImagesVPDRANSAC::applyMethodModel(
    std::vector<cv::Point2f> data) {
}

double ManhattanWorldImagesVPDRANSAC::calcError(std::vector<cv::Point3f> model,
                                                cv::Point2f sample) {
}

unsigned int ManhattanWorldImagesVPDRANSAC::numberOfSamples() {
}
