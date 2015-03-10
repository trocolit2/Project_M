/*
 * StixelTools.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: tiagotrocoli
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <LineTools.h>
#include "StixelTools.h"
#include "lsd.h"

#define minNumber

cv::Mat StixelTools::extractStixelFromForeground(cv::Mat foreground, std::vector<Stixel2D>* stixeis, uint64 minPoints, cv::Mat showImage) {

    std::vector<Stixel2D> tempStixeis;
    std::vector<std::vector<cv::Point> > contours;
    bool draw = showImage.cols > 4 && showImage.rows > 4 && showImage.channels() == 3;

    cv::Mat tempImage = showImage.clone();

    cv::findContours(foreground.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    if (minPoints > 0)
        contours = filterByNumberPoints(contours, minPoints);

    for (uint64 k = 0; k < contours.size(); ++k) {
        cv::Point2f min, max;
        cv::RotatedRect roteRect = cv::fitEllipse(contours[k]);
        cv::Point2f points[4];
        roteRect.points(points);
        max.x = roteRect.center.x + (points[0].x - points[1].x) / 2;
        max.y = roteRect.center.y + (points[0].y - points[1].y) / 2;
        min.x = roteRect.center.x + (points[2].x - points[3].x) / 2;
        min.y = roteRect.center.y + (points[2].y - points[3].y) / 2;

        Stixel2D stixel(min, max);
        stixeis->push_back(stixel);

        if (draw) {
            cv::line(tempImage, min, max, LineTools::colorAngle(stixel.getAngle()));
            cv::circle(tempImage, roteRect.center, stixel.getSize() * 0.03, cv::Scalar(255, 255, 0), -1);
        }
    }

    if (draw) {
        cv::drawContours(tempImage, contours, -1, cv::Scalar(0, 255, 0));
    }

    return tempImage;
}

cv::Mat StixelTools::extractStixelFromBackground(cv::Mat background, std::vector<Stixel2D>* stixeis, cv::Mat showImage) {

    cv::Mat tempImage = background.clone();
    std::vector<Stixel2D> tempStixeis = getStixelFromLSD(background.clone());

    bool draw = showImage.cols > 4 && showImage.rows > 4 && showImage.channels() == 3;

    if (draw) {
        std::cout << "SIZE STIXEIS " << tempStixeis.size() << std::endl;
        for (uint64 i = 0; i < tempStixeis.size(); ++i)
            cv::line(showImage, tempStixeis[i].getBottonPoint(), tempStixeis[i].getTopPoint(), LineTools::colorAngle(tempStixeis[i].getAngle()));
    }

    stixeis->insert(stixeis->begin(), tempStixeis.begin(), tempStixeis.end());
    return showImage;
}

std::vector<std::vector<cv::Point> > StixelTools::filterByNumberPoints(std::vector<std::vector<cv::Point> > contours, uint64 numberPoints) {

    std::vector<std::vector<cv::Point> > temp;
    for (uint64 k = 0; k < contours.size(); ++k)
        if (contours[k].size() > numberPoints)
            temp.push_back(contours[k]);
    return temp;
}

std::vector<Stixel2D> StixelTools::getStixelFromLSD(cv::Mat background) {

    std::vector<Stixel2D> stixeis;
    double * image;
    double * out;
    int x, y, i, n;
    int X = background.cols; /* x image size */
    int Y = background.rows; /* y image size */

    cv::Mat temp;
    cv::cvtColor(background, temp, CV_BGR2GRAY);

    /* create a simple image: left half black, right half gray */
    image = (double *) malloc(X * Y * sizeof(double));
    if (image == NULL) {
        fprintf(stderr, "error: not enough memory\n");
        exit(EXIT_FAILURE);
    }
    for (x = 0; x < X; x++)
        for (y = 0; y < Y; y++)
            image[x + y * X] = temp.at<uint8_t>(y, x); /* image(x,y) */

    /* LSD call */
    out = lsd(&n, image, X, Y);

    /* print output */
    //printf("%d line segments found:\n", n);
    for (i = 0; i < n; i++) {
        cv::Point2f point1(out[7 * i + 0], out[7 * i + 1]), point2(out[7 * i + 2], out[7 * i + 3]);

        Stixel2D stixel(point1, point2);
        stixeis.push_back(stixel);
    }

    /* free memory */
    free((void *) image);
    free((void *) out);
    return stixeis;

}

std::vector<uint> StixelTools::histogramAngleStixel2D(std::vector<Stixel2D> stixeis, uint beans, cv::Mat* image) {

    std::vector<uint> histVector(beans, 0);
    double slope = beans * 1.0 / 180.0;

    for (uint i = 0; i < stixeis.size(); ++i) {
        ++histVector[(uint) stixeis[i].getAngle() * slope];
//		std::cout << " ANGLE " << stixeis[i].getAngle() << " POSITION "
//				<< ((int) (stixeis[i].getAngle() * slope)) << std::endl;
    }

    if (image != 0) {
        if (image->size().height > 0 && image->size().width > 0)
            (*image) = drawHistogramAngleStixel2D(histVector, image->size());
        else
            (*image) = drawHistogramAngleStixel2D(histVector);

        std::cout << "{" << histVector[0];
        for (uint i = 1; i < histVector.size(); ++i)
            std::cout << ", " << histVector[i];
        std::cout << "}" << std::endl;
    }

    return histVector;
}

cv::Mat StixelTools::drawHistogramAngleStixel2D(std::vector<uint> histogram, cv::Size size) {

    cv::Mat histImage = cv::Mat::zeros(size, CV_8UC3) + cv::Scalar(255, 255, 255);

    cv::Mat histMat(1, histogram.size(), CV_32SC1);
    for (uint i = 0; i < histogram.size(); ++i) {
        histMat.at<uint>(0, i) = histogram[i];
    }

    double maxBeanValue;
    cv::minMaxIdx(histMat, 0, &maxBeanValue);

    double highNorm = (size.height - size.height * 0.02) * 1.0 / maxBeanValue;
    double beanSize = size.width * 1.0 / histogram.size();
    double angleSlice = 180 * 1.0 / histogram.size();

    for (uint i = 0; i < histogram.size(); ++i) {
        cv::Scalar color = LineTools::colorAngle(i * angleSlice);
        cv::Point pt1 = cv::Point(i * beanSize, size.height - 1);
        cv::Point pt2 = cv::Point(i * beanSize + beanSize, size.height - histogram[i] * highNorm);
        cv::rectangle(histImage, pt1, pt2, color, -1);
    }
    return histImage;
}

std::vector<Stixel2D> StixelTools::gethistogramAngleInterval(std::vector<Stixel2D> mainVector, std::vector<uint> histogram, uint midleBean, uint intevalSides, std::vector<Stixel2D>* residualVector) {

    std::vector<Stixel2D> result;
    double beanSize = 180.0 / histogram.size();
    int minBean = (midleBean - intevalSides);
    if (minBean < 0)
        minBean = histogram.size() + minBean;
    int maxBean = (midleBean + intevalSides + 1) % histogram.size();
    bool normalWay = minBean < maxBean;

    minBean *= beanSize;
    maxBean *= beanSize;
    if (normalWay) {
        for (uint i = 0; i < mainVector.size(); ++i)
            if (mainVector[i].getAngle() < maxBean && mainVector[i].getAngle() >= minBean)
                result.push_back(mainVector[i]);
            else if (residualVector != 0)
                (*residualVector).push_back(mainVector[i]);
    } else {
        for (uint i = 0; i < mainVector.size(); ++i)
            if (mainVector[i].getAngle() < maxBean || mainVector[i].getAngle() >= minBean)
                result.push_back(mainVector[i]);
            else if (residualVector != 0)
                (*residualVector).push_back(mainVector[i]);
    }

    return result;
}

std::vector<Stixel2D> StixelTools::getMaxBeanAngleInteval(std::vector<Stixel2D> mainVector, std::vector<uint> histogram, uint intervalSides, std::vector<Stixel2D>* residualVector) {

    cv::Mat histMat(1, histogram.size(), CV_32SC1);
    for (uint i = 0; i < histogram.size(); ++i) {
        histMat.at<uint>(0, i) = histogram[i];
    }

    cv::Point maxPosition;
    double maxValue;
    cv::minMaxLoc(histMat, 0, &maxValue, 0, &maxPosition);

    return gethistogramAngleInterval(mainVector, histogram, maxPosition.x, intervalSides, residualVector);
}

std::vector<Stixel2D> StixelTools::getMaxBeanAngleIntevalsAdaptative(std::vector<Stixel2D> mainVector, std::vector<uint> histogram, std::vector<Stixel2D>* residualVector) {

    cv::Mat histMat(1, histogram.size(), CV_32SC1);
    for (uint i = 0; i < histogram.size(); ++i)
        histMat.at<uint>(0, i) = histogram[i];

    cv::Point maxPosition;
    double maxValue;
    cv::minMaxLoc(histMat, 0, &maxValue, 0, &maxPosition);

    int leftValue = maxPosition.x - 1;
    leftValue < 0 ? leftValue = histogram[histogram.size() - 1] : leftValue = histogram[leftValue];

    int rightValue = histogram[(maxPosition.x + 1) % histogram.size()];
    uint intervalSize = 1;

    int leftIncrement = maxPosition.x - 1;
    int rightIncrement = maxPosition.x + 1;

    for (uint i = 0; i < histogram.size(); ++i) {
        rightIncrement += 1;
        rightIncrement = rightIncrement % histogram.size();
        leftIncrement -= 1;
        leftIncrement < 0 ? leftIncrement = histogram.size() - 1 : 0;

        //std::cout << "Actual left " << histogram[leftIncrement] << " hist Left " << leftValue << " position =" << leftIncrement << std::endl;
        if (histogram[leftIncrement] > leftValue || histogram[leftIncrement] == 0)
            break;
        else
            leftValue = histogram[leftIncrement];

        //std::cout << "Actual right " << histogram[rightIncrement] << " hist RIGHT " << rightValue << " position =" << rightIncrement << std::endl;
        if (histogram[rightIncrement] > rightValue || histogram[rightIncrement] == 0)
            break;
        else
            rightValue = histogram[rightIncrement];
        ++intervalSize;
    }

    //std::cout << "Interval " << intervalSize << std::endl;
    return gethistogramAngleInterval(mainVector, histogram, maxPosition.x, intervalSize, residualVector);
}

std::vector<cv::Point2f> StixelTools::convertStixeisToPoint(std::vector<Stixel2D> stixeis, uint numberOfCandidateStixeis, uint numberOfPoints) {

    std::vector<cv::Point2f> points;

    for (uint i = 0; i < numberOfPoints; ++i) {
        std::map<uint, Stixel2D> mapCandidatesStixeis;
        while (mapCandidatesStixeis.size() < numberOfCandidateStixeis) {
            uint k = rand() % stixeis.size();
            mapCandidatesStixeis.insert(std::pair<uint, Stixel2D>(k, stixeis[k]));
        }

        std::cout << "\nITERATION " << i << std::endl;
        cv::Mat MatA = cv::Mat::zeros(numberOfCandidateStixeis, 3, CV_32FC1);
        cv::Mat MatX = cv::Mat::zeros(3, 1, CV_32FC1);
        std::map<uint, Stixel2D>::iterator p;

        uint j = 0;
        for (p = mapCandidatesStixeis.begin(); p != mapCandidatesStixeis.end(); ++p) {
            std::cout << "KEY " << p->first << " VALUE " << p->second << std::endl;
            MatA.at<float>(j, 0) = p->second.getLineEquation()[0];
            MatA.at<float>(j, 1) = p->second.getLineEquation()[1];
            MatA.at<float>(j, 2) = p->second.getLineEquation()[2];
            ++j;
        }
        std::cout << "\nMat A -->" << MatA << std::endl;
        cv::SVD::solveZ(MatA, MatX);
        std::cout << "\nMat X -->" << MatX << std::endl;
        cv::Point2f point(MatX.at<float>(0, 0) / MatX.at<float>(0, 2), MatX.at<float>(0, 1) / MatX.at<float>(0, 2));
        std::cout << "\nPOINT -->" << point << std::endl;

    }

    return points;
}

