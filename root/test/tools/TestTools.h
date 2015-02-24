/*
 * TestTools.h
 *
 *  Created on: Dec 15, 2014
 *      Author: tiagotrocoli
 */

#ifndef TEST_TESTTOOLS_H_
#define TEST_TESTTOOLS_H_

#include <string>
#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>

//constants
#define PATH_RELATIVE_ROOT_TESTBIN "../../../root/"

//path to dataset test
#define PATH_PETS_2006_S1 "/home/tiagotrocoli/Documents/Mestrado/datasets-tracking/pets_2006/S6/1/picture/"
#define PATH_PETS_2006_S2 "/home/tiagotrocoli/Documents/Mestrado/datasets-tracking/pets_2006/S6/2/picture/"
#define PATH_PETS_2006_S3 "/home/tiagotrocoli/Documents/Mestrado/datasets-tracking/pets_2006/S6/3/picture/"
#define PATH_PETS_2006_S4 "/home/tiagotrocoli/Documents/Mestrado/datasets-tracking/pets_2006/S6/4/picture/"

class TestTools {
public:

	static std::vector<uint8_t> convertmat2vector(cv::Mat m);
	static void writeImageJpeg(std::string writePath, cv::Mat image);
	static double setDigits(double number, int digits);
};

#endif /* TEST_TESTTOOLS_H_ */
