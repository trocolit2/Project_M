/*
 * VPTools.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: tiagotrocoli
 */

#include <vanishPointPackage/VPTools.h>

#include <opencv2/core/core.hpp>
#include <map>
#include <vector>

std::vector<cv::Point2f> VPTools::convertStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints, uint seed) {

    std::vector<cv::Point2f> points;

    srand(seed);
    for (uint i = 0; i < numberOfPoints; ++i) {
        std::map<uint, Stixel2D> mapCandidatesStixeis;

        while (mapCandidatesStixeis.size() < numberOfCandidateStixeis) {
            uint k = rand() % stixeis.size();
            mapCandidatesStixeis.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
        }

        //std::cout << "\nITERATION " << i << std::endl;
        cv::Mat MatA = cv::Mat::zeros(numberOfCandidateStixeis, 3, CV_32FC1);
        cv::Mat MatX;
        std::map<uint, Stixel2D>::iterator p;

        uint j = 0;
        for (p = mapCandidatesStixeis.begin(); p != mapCandidatesStixeis.end(); ++p) {
            //  std::cout << "KEY " << p->first << " VALUE " << p->second << std::endl;
            MatA.at<float>(j, 0) = p->second.getLineEquation()[0];
            MatA.at<float>(j, 1) = p->second.getLineEquation()[1];
            MatA.at<float>(j, 2) = p->second.getLineEquation()[2];
            ++j;
        }
        //std::cout << "\nMat A -->" << MatA << std::endl;
        cv::SVD::solveZ(MatA, MatX);
        //cv::solve(MatA, MatB, MatX, cv::DECOMP_NORMAL);
        //std::cout << "\nMat X -->" << MatX << std::endl;
        cv::Point2f point(MatX.at<float>(0, 0) / MatX.at<float>(0, 2), MatX.at<float>(0, 1) / MatX.at<float>(0, 2));
        //std::cout << "cv::Point = " << point << std::endl;
        points.push_back(point);
    }

    return points;
}
