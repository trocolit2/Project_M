/*
 * VPTools.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: tiagotrocoli
 */

//#include <LineMathTools.h>
#include "VPTools.h"
#include <opencv2/core/core.hpp>
#include <map>
#include <vector>
#include <cfloat>

#define MAX_FLOAT_VALUE DBL_MAX

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

//std::vector<cv::Point2f> VPTools::convergeStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints, uint seed) {
//
//    std::vector<cv::Point2f> points;
//    srand(seed);
//    for (uint i = 0; i < numberOfPoints; ++i) {
//        std::map<uint, Stixel2D> mapCandidatesStixeis;
//
//        while (mapCandidatesStixeis.size() < numberOfCandidateStixeis) {
//            uint k = rand() % stixeis.size();
//            mapCandidatesStixeis.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
//        }
//        std::vector<Stixel2D> localVector;
//
//        std::transform(mapCandidatesStixeis.begin(), mapCandidatesStixeis.end(), std::back_inserter(localVector), second(mapCandidatesStixeis));
//        points.push_back(computeStixeisToPointBySVD(localVector));
//    }
//    return points;
//}
//
//cv::Point2f VPTools::convergeStixeisToPointBySVD(std::vector<Stixel2D> stixeis) {
//    return computeStixeisToPointBySVD(stixeis);
//}
//
//cv::Point2f VPTools::convergeStixeisToPointByRANSAC(std::vector<Stixel2D> stixeis, uint sample, uint iteration, double error, uint seed, std::vector<Stixel2D> * set) {
//
//    srand(seed);
//    std::vector<Stixel2D> consensu, tempVector;
////    double consensuSTD = 1, consensuError = 0; // eh o valor do std;
//    double consensuSTD, consensuError = MAX_FLOAT_VALUE; // eh o valor do std;
//    std::vector<double> distanceLine2Point;
//    cv::Scalar sum = 0;
//    std::map<uint, Stixel2D> map;
//    uint i_select = 0;
//
//    for (int i = 0; i < iteration; ++i) {
//        std::cout << "\n\nIT " << i << std::endl;
//        map.clear();
//        while (map.size() < sample) {
//            uint k = rand() % stixeis.size();
//            map.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
//        }
//        tempVector.clear();
//        std::transform(map.begin(), map.end(), std::back_inserter(tempVector), second(map));
//        cv::Point2f convergePoint = computeStixeisToPointBySVD(tempVector);
//
//        tempVector.clear();
//        distanceLine2Point.clear();
//
//        for (uint j = 0; j < stixeis.size(); ++j) {
////            double distance = VPTools::liowtizDistance(convergePoint, stixeis[j]);
//            double distance = LineTools::calcDistanceLine2Point(stixeis[j].getLineEquation(), convergePoint);
//            std::cout << "OUT ERROR: " << distance << std::endl;
//            if (distance < error) {
//                distanceLine2Point.push_back(distance);
//                tempVector.push_back(stixeis[j]);
//            }
//        }
//
//        std::cout << "MAT DIST: " << cv::Mat(distanceLine2Point) << std::endl;
//        sum = cv::sum(cv::Mat(distanceLine2Point));
//
////        std::cout << "STD: " << std[0] << std::endl;
//        if (tempVector.size() > 2) {
//            double tempError = sum[0] - tempVector.size() * 1.0 / sample;
//            std::cout << "tempERROR: " << tempError << std::endl;
//            std::cout << "SUM: " << sum[0] << " tempVector.size() * 1.0 / sample = " << -(tempVector.size() * 1.0 / sample) << std::endl;
//            if (tempError < consensuError) {
//                i_select = i;
//                consensuError = tempError;
//                consensuSTD = sum[0];
//                consensu.clear();
//                consensu = std::vector<Stixel2D>(tempVector);
//            }
//        }
//    }
//
//    if (set != 0)
//        (*set) = consensu;
//
//    std::cout << "\nITERACTION  " << i_select << std::endl;
//    std::cout << "consensuError " << consensuError << std::endl;
//    std::cout << "consensuSTD " << consensuSTD << std::endl;
//    for (int l = 0; l < consensu.size(); ++l) {
//        std::cout << "POINTS " << consensu[l] << std::endl;
//    }
//    return computeStixeisToPointBySVD(consensu);
//}
//
//double VPTools::liowtizDistance(cv::Point2f point1, Stixel2D line) {
//
//    Stixel2D mainLine(point1, line.getCenter());
//    double distance = LineTools::calcDistanceLine2Point(mainLine.getLineEquation(), line.getTopPoint());
//    std::cout << "DIST " << distance << " ";
//    std::cout << "lineSeg " << line.getSize() << std::endl;
//    distance = distance / (line.getSize() * 1.0 / 2);
//    return distance;
//
//}
//
//cv::Point2f VPTools::computeStixeisToPointBySVD(std::vector<Stixel2D> stixeis) {
//    cv::Mat MatX;
//    cv::Mat MatA = cv::Mat::zeros(stixeis.size(), 3, CV_32FC1);
//    for (int i = 0; i < stixeis.size(); ++i) {
//        MatA.at<float>(i, 0) = stixeis[i].getLineEquation()[0];
//        MatA.at<float>(i, 1) = stixeis[i].getLineEquation()[1];
//        MatA.at<float>(i, 2) = stixeis[i].getLineEquation()[2];
//    }
//    cv::SVD::solveZ(MatA, MatX);
//    cv::Point2f point(MatX.at<float>(0, 0) / MatX.at<float>(0, 2), MatX.at<float>(0, 1) / MatX.at<float>(0, 2));
//    return point;
//}
