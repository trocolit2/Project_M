/*
 * TestTools.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: tiagotrocoli
 */

#include "TestTools.h"

#include <exception>
#include <iostream>
#include <algorithm>

std::vector<uint8_t> TestTools::convertmat2vector(cv::Mat m) {
    uint8_t* data = reinterpret_cast<uint8_t*>(m.data);
    int len = m.rows * m.cols * m.channels();
    std::vector<uint8_t> vec(len);
    std::copy(data + 0, data + len, vec.begin());
    return vec;
}

void TestTools::writeImageJpeg(std::string writePath, cv::Mat image) {
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);

    try {
        cv::imwrite(writePath, image, compression_params);
    } catch (std::exception& ex) {
        std::cout << stderr << "Exception write image to JPEG format:" << ex.what() << std::endl;
        exit (EXIT_FAILURE);
    }
}

double TestTools::setDigits(double _number, int _digits) {
    double tenth = pow(10, _digits);
    int result = (_number * tenth);
    return result * 1.0 / tenth;
}

