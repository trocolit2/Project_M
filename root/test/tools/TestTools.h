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

#define STIXEL_RESOURCE_PATH "resource/stixelTests/"

#define BW_FOREGROUND_IMAGE_01 "bwForegroundImage01.jpeg"
#define BW_FOREGROUND_IMAGE_02 "bwForegroundImage02.jpeg"
#define BW_FOREGROUND_IMAGE_03 "bwForegroundImage03.jpeg"
#define BW_FOREGROUND_IMAGE_04 "bwForegroundImage04.jpeg"

#define BACKGROUND_IMAGE_01 "backgroundStixel01.jpg"
#define BACKGROUND_IMAGE_02 "backgroundStixel02.jpg"
#define BACKGROUND_IMAGE_03 "backgroundStixel03.jpg"
#define BACKGROUND_IMAGE_04 "backgroundStixel04.jpg"

#define BACKGROUND_IMAGE_LINES_03 "backgroundStixel03_lines.jpg"
#define BACKGROUND_IMAGE_LINES_04 "backgroundStixel04_lines.jpg"

class TestTools {
public:

    static std::vector<uint8_t> convertmat2vector(cv::Mat m);
    static void writeImageJpeg(std::string writePath, cv::Mat image);
    static double setDigits(double number, int digits);
};

#endif /* TEST_TESTTOOLS_H_ */
