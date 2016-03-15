/*
 * ManhattanWorldImagesVPD.h
 *
 *  Created on: Mar 15, 2016
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_VANISHPOINTPACKAGE_MANHATTANWORLDIMAGESVPD_H_
#define SRC_LIBRARY_VANISHPOINTPACKAGE_MANHATTANWORLDIMAGESVPD_H_

#include <opencv2/core/core.hpp>
#include <GenericRansac.hpp>

class ManhattanWorldImagesVPDRANSAC : public generic_ransac::GenericRansac<
    cv::Point3f, cv::Point2f> {
 public:
  ~ManhattanWorldImagesVPDRANSAC();
  ManhattanWorldImagesVPDRANSAC();

  std::vector<cv::Point3f> applyMethodModel(std::vector<cv::Point2f> data);
  double calcError(std::vector<cv::Point3f> model, cv::Point2f sample);

  std::string methodName() {return "ManhattanWorldImagesVPDRANSAC";};
  unsigned int numberOfSamples();

};

class ManhattanWorldImagesVPD {
 public:
  ~ManhattanWorldImagesVPD();
  ManhattanWorldImagesVPD();
};

#endif /* SRC_LIBRARY_VANISHPOINTPACKAGE_MANHATTANWORLDIMAGESVPD_H_ */
