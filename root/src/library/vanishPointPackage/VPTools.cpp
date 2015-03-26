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

template<typename tPair>
struct second_t {
    typename tPair::second_type operator()(const tPair& p) const {
        return p.second;
    }
};

template<typename tMap>
second_t<typename tMap::value_type> second(const tMap& m) {
    return second_t<typename tMap::value_type>();
}

std::vector<cv::Point2f> VPTools::convergeStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints, uint seed) {

    std::vector<cv::Point2f> points;
    srand(seed);
    for (uint i = 0; i < numberOfPoints; ++i) {
        std::map<uint, Stixel2D> mapCandidatesStixeis;

        while (mapCandidatesStixeis.size() < numberOfCandidateStixeis) {
            uint k = rand() % stixeis.size();
            mapCandidatesStixeis.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
        }
        std::vector<Stixel2D> localVector;

        std::transform(mapCandidatesStixeis.begin(), mapCandidatesStixeis.end(), std::back_inserter(localVector), second(mapCandidatesStixeis));
        points.push_back(computeStixeisToPointBySVD(localVector));
    }
    return points;
}

cv::Point2f VPTools::convergeStixeisToPointBySVD(std::vector<Stixel2D> stixeis) {
    return computeStixeisToPointBySVD(stixeis);
}

cv::Point2f VPTools::convergeStixeisToPointByRANSAC(std::vector<Stixel2D> stixeis, uint sample, uint iteration, float erro, uint seed) {

    srand(seed);
    std::vector<Stixel2D> consensu;

    for (int var = 0; var < iteration; ++var) {
        std::map<uint, Stixel2D> map;

        while (map.size() < sample) {
            uint k = rand() % stixeis.size();
            map.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
        }
        std::vector<Stixel2D> localVector;

        std::transform(map.begin(), map.end(), std::back_inserter(localVector), second(map));

        computeStixeisToPointBySVD(localVector);
    }

}

cv::Point2f VPTools::computeStixeisToPointBySVD(std::vector<Stixel2D> stixeis) {
    cv::Mat MatX;
    cv::Mat MatA = cv::Mat::zeros(stixeis.size(), 3, CV_32FC1);
    for (int i = 0; i < stixeis.size(); ++i) {
        MatA.at<float>(i, 0) = stixeis[i].getLineEquation()[0];
        MatA.at<float>(i, 1) = stixeis[i].getLineEquation()[1];
        MatA.at<float>(i, 2) = stixeis[i].getLineEquation()[2];
    }
    cv::SVD::solveZ(MatA, MatX);
    cv::Point2f point(MatX.at<float>(0, 0) / MatX.at<float>(0, 2), MatX.at<float>(0, 1) / MatX.at<float>(0, 2));
    return point;
}
