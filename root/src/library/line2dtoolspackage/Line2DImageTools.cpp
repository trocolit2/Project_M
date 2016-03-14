/*
 * Line2DImageTools.cpp
 *
 *  Created on: Jan 20, 2015
 *      Author: tiagotrocoli
 */

#include "Line2DImageTools.h"

extern "C" {
#include "lsd.h"
}

#include <opencv2/imgproc/imgproc.hpp>
#include "Line2DMathTools.h"

cv::Mat Line2DImageTools::extractLine2DFromForeground(
    cv::Mat foreground, std::vector<Line2D>* stixeis, uint64 minPoints,
    cv::Mat showImage) {

  std::vector<Line2D> tempStixeis;
  std::vector<std::vector<cv::Point> > contours;

  bool draw = showImage.cols > 4 && showImage.rows > 4
      && showImage.channels() == 3;
  cv::Mat tempImage = showImage.clone();

  cv::findContours(foreground.clone(), contours, CV_RETR_EXTERNAL,
                   CV_CHAIN_APPROX_NONE);

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

    Line2D line(min, max);
    stixeis->push_back(line);

    if (draw) {
      cv::line(tempImage, min, max, colorAngle(line.angle()));
      cv::circle(tempImage, roteRect.center, line.size() * 0.03,
                 cv::Scalar(255, 255, 0), -1);
    }
  }

  if (draw) {
    cv::drawContours(tempImage, contours, -1, cv::Scalar(0, 255, 0));
  }
  return tempImage;
}

cv::Mat Line2DImageTools::extractLine2DFromBackground(
    cv::Mat background, std::vector<Line2D>* stixeis, cv::Mat showImage) {

  cv::Mat tempImage = background.clone();
  std::vector<Line2D> tempStixeis = getLine2DFromLSD(background.clone());

  bool draw = showImage.cols > 4 && showImage.rows > 4
      && showImage.channels() == 3;

  if (draw) {
    std::cout << "SIZE STIXEIS " << tempStixeis.size() << std::endl;
    for (uint64 i = 0; i < tempStixeis.size(); ++i)
      cv::line(showImage, tempStixeis[i].bottonPoint(),
               tempStixeis[i].topPoint(), colorAngle(tempStixeis[i].angle()));
  }

  stixeis->insert(stixeis->begin(), tempStixeis.begin(), tempStixeis.end());
  return showImage;
}

std::vector<std::vector<cv::Point> > Line2DImageTools::filterByNumberPoints(
    std::vector<std::vector<cv::Point> > contours, uint64 numberPoints) {

  std::vector<std::vector<cv::Point> > temp;
  for (uint64 k = 0; k < contours.size(); ++k)
    if (contours[k].size() > numberPoints)
      temp.push_back(contours[k]);
  return temp;
}

std::vector<Line2D> Line2DImageTools::getLine2DFromLSD(cv::Mat background) {

  std::vector<Line2D> Lines;
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
    cv::Point2f point1(out[7 * i + 0], out[7 * i + 1]), point2(out[7 * i + 2],
                                                               out[7 * i + 3]);
    Line2D line(point1, point2);
    Lines.push_back(line);
  }

  /* free memory */
  free((void *) image);
  free((void *) out);
  return Lines;
}

std::vector<uint> Line2DImageTools::histogramAngleLine2D(
    std::vector<Line2D> lines, uint beans, cv::Mat* image) {

  std::vector<uint> histVector(beans, 0);
  double slope = beans * 1.0 / 180.0;

  for (uint i = 0; i < lines.size(); ++i) {
    ++histVector[(uint) lines[i].angle() * slope];
  }

  if (image != 0) {
    if (image->size().height > 0 && image->size().width > 0)
      (*image) = drawHistogramAngleLine2D(histVector, image->size());
    else
      (*image) = drawHistogramAngleLine2D(histVector);
  }

  return histVector;
}

cv::Mat Line2DImageTools::drawHistogramAngleLine2D(std::vector<uint> histogram,
                                                   cv::Size size) {

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
    cv::Scalar color = colorAngle(i * angleSlice);
    cv::Point pt1 = cv::Point(i * beanSize, size.height - 1);
    cv::Point pt2 = cv::Point(i * beanSize + beanSize,
                              size.height - histogram[i] * highNorm);
    cv::rectangle(histImage, pt1, pt2, color, -1);
  }
  return histImage;
}

std::vector<Line2D> Line2DImageTools::gethistogramAngleInterval(
    std::vector<Line2D> mainVector, std::vector<uint> histogram, uint midleBean,
    uint intevalSides, std::vector<Line2D>* residualVector) {

  std::vector<Line2D> result;
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
      if (mainVector[i].angle() < maxBean && mainVector[i].angle() >= minBean)
        result.push_back(mainVector[i]);
      else if (residualVector != 0)
        (*residualVector).push_back(mainVector[i]);
  } else {
    for (uint i = 0; i < mainVector.size(); ++i)
      if (mainVector[i].angle() < maxBean || mainVector[i].angle() >= minBean)
        result.push_back(mainVector[i]);
      else if (residualVector != 0)
        (*residualVector).push_back(mainVector[i]);
  }

  return result;
}

std::vector<Line2D> Line2DImageTools::getMaxBeanAngleInteval(
    std::vector<Line2D> mainVector, std::vector<uint> histogram,
    uint intervalSides, std::vector<Line2D>* residualVector) {

  cv::Mat histMat(1, histogram.size(), CV_32SC1);
  for (uint i = 0; i < histogram.size(); ++i) {
    histMat.at<uint>(0, i) = histogram[i];
  }

  cv::Point maxPosition;
  double maxValue;
  cv::minMaxLoc(histMat, 0, &maxValue, 0, &maxPosition);

  return gethistogramAngleInterval(mainVector, histogram, maxPosition.x,
                                   intervalSides, residualVector);
}

std::vector<Line2D> Line2DImageTools::getMaxBeanAngleIntevalsAdaptative(
    std::vector<Line2D> mainVector, std::vector<uint> histogram,
    std::vector<Line2D>* residualVector) {

  cv::Mat histMat(1, histogram.size(), CV_32SC1);
  for (uint i = 0; i < histogram.size(); ++i)
    histMat.at<uint>(0, i) = histogram[i];

  cv::Point maxPosition;
  double maxValue;
  cv::minMaxLoc(histMat, 0, &maxValue, 0, &maxPosition);

  int leftValue = maxPosition.x - 1;
  leftValue < 0 ? leftValue = histogram[histogram.size() - 1] : leftValue =
                      histogram[leftValue];

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
    if (histogram[rightIncrement] > rightValue
        || histogram[rightIncrement] == 0)
      break;
    else
      rightValue = histogram[rightIncrement];
    ++intervalSize;
  }

  //std::cout << "Interval " << intervalSize << std::endl;
  return gethistogramAngleInterval(mainVector, histogram, maxPosition.x,
                                   intervalSize, residualVector);
}

cv::Mat Line2DImageTools::drawStixeis(std::vector<Line2D> stixeis,
                                      cv::Mat image) {

  bool draw = image.cols > 4 && image.rows > 4 && image.channels() == 3;

  cv::Mat mat;
  if (draw)
    image.copyTo(mat);
  else
    mat = cv::Mat::zeros(500, 500, CV_8UC3);

  for (uint64 i = 0; i < stixeis.size(); ++i)
    cv::line(mat, stixeis[i].bottonPoint(), stixeis[i].topPoint(),
             colorAngle(stixeis[i].angle()));
  return mat;
}

cv::Scalar Line2DImageTools::colorAngle(double angle) {

  float r[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0.00588235294117645, 0.02156862745098032, 0.03725490196078418,
      0.05294117647058827, 0.06862745098039214, 0.084313725490196,
      0.1000000000000001, 0.115686274509804, 0.1313725490196078,
      0.1470588235294117, 0.1627450980392156, 0.1784313725490196,
      0.1941176470588235, 0.2098039215686274, 0.2254901960784315,
      0.2411764705882353, 0.2568627450980392, 0.2725490196078431,
      0.2882352941176469, 0.303921568627451, 0.3196078431372549,
      0.3352941176470587, 0.3509803921568628, 0.3666666666666667,
      0.3823529411764706, 0.3980392156862744, 0.4137254901960783,
      0.4294117647058824, 0.4450980392156862, 0.4607843137254901,
      0.4764705882352942, 0.4921568627450981, 0.5078431372549019,
      0.5235294117647058, 0.5392156862745097, 0.5549019607843135,
      0.5705882352941174, 0.5862745098039217, 0.6019607843137256,
      0.6176470588235294, 0.6333333333333333, 0.6490196078431372,
      0.664705882352941, 0.6803921568627449, 0.6960784313725492,
      0.7117647058823531, 0.7274509803921569, 0.7431372549019608,
      0.7588235294117647, 0.7745098039215685, 0.7901960784313724,
      0.8058823529411763, 0.8215686274509801, 0.8372549019607844,
      0.8529411764705883, 0.8686274509803922, 0.884313725490196,
      0.8999999999999999, 0.9156862745098038, 0.9313725490196076,
      0.947058823529412, 0.9627450980392158, 0.9784313725490197,
      0.9941176470588236, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0.9862745098039216, 0.9705882352941178, 0.9549019607843139,
      0.93921568627451, 0.9235294117647062, 0.9078431372549018,
      0.892156862745098, 0.8764705882352941, 0.8607843137254902,
      0.8450980392156864, 0.8294117647058825, 0.8137254901960786,
      0.7980392156862743, 0.7823529411764705, 0.7666666666666666,
      0.7509803921568627, 0.7352941176470589, 0.719607843137255,
      0.7039215686274511, 0.6882352941176473, 0.6725490196078434,
      0.6568627450980391, 0.6411764705882352, 0.6254901960784314,
      0.6098039215686275, 0.5941176470588236, 0.5784313725490198,
      0.5627450980392159, 0.5470588235294116, 0.5313725490196077,
      0.5156862745098039, 0.5 };

  float g[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.001960784313725483,
      0.01764705882352935, 0.03333333333333333, 0.0490196078431373,
      0.06470588235294117, 0.08039215686274503, 0.09607843137254901,
      0.111764705882353, 0.1274509803921569, 0.1431372549019607,
      0.1588235294117647, 0.1745098039215687, 0.1901960784313725,
      0.2058823529411764, 0.2215686274509804, 0.2372549019607844,
      0.2529411764705882, 0.2686274509803921, 0.2843137254901961, 0.3,
      0.3156862745098039, 0.3313725490196078, 0.3470588235294118,
      0.3627450980392157, 0.3784313725490196, 0.3941176470588235,
      0.4098039215686274, 0.4254901960784314, 0.4411764705882353,
      0.4568627450980391, 0.4725490196078431, 0.4882352941176471,
      0.503921568627451, 0.5196078431372548, 0.5352941176470587,
      0.5509803921568628, 0.5666666666666667, 0.5823529411764705,
      0.5980392156862746, 0.6137254901960785, 0.6294117647058823,
      0.6450980392156862, 0.6607843137254901, 0.6764705882352942,
      0.692156862745098, 0.7078431372549019, 0.723529411764706,
      0.7392156862745098, 0.7549019607843137, 0.7705882352941176,
      0.7862745098039214, 0.8019607843137255, 0.8176470588235294,
      0.8333333333333333, 0.8490196078431373, 0.8647058823529412,
      0.8803921568627451, 0.8960784313725489, 0.9117647058823528,
      0.9274509803921569, 0.9431372549019608, 0.9588235294117646,
      0.9745098039215687, 0.9901960784313726, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 0.9901960784313726, 0.9745098039215687, 0.9588235294117649,
      0.943137254901961, 0.9274509803921571, 0.9117647058823528,
      0.8960784313725489, 0.8803921568627451, 0.8647058823529412,
      0.8490196078431373, 0.8333333333333335, 0.8176470588235296,
      0.8019607843137253, 0.7862745098039214, 0.7705882352941176,
      0.7549019607843137, 0.7392156862745098, 0.723529411764706,
      0.7078431372549021, 0.6921568627450982, 0.6764705882352944,
      0.6607843137254901, 0.6450980392156862, 0.6294117647058823,
      0.6137254901960785, 0.5980392156862746, 0.5823529411764707,
      0.5666666666666669, 0.5509803921568626, 0.5352941176470587,
      0.5196078431372548, 0.503921568627451, 0.4882352941176471,
      0.4725490196078432, 0.4568627450980394, 0.4411764705882355,
      0.4254901960784316, 0.4098039215686273, 0.3941176470588235,
      0.3784313725490196, 0.3627450980392157, 0.3470588235294119,
      0.331372549019608, 0.3156862745098041, 0.2999999999999998,
      0.284313725490196, 0.2686274509803921, 0.2529411764705882,
      0.2372549019607844, 0.2215686274509805, 0.2058823529411766,
      0.1901960784313728, 0.1745098039215689, 0.1588235294117646,
      0.1431372549019607, 0.1274509803921569, 0.111764705882353,
      0.09607843137254912, 0.08039215686274526, 0.06470588235294139,
      0.04901960784313708, 0.03333333333333321, 0.01764705882352935,
      0.001960784313725483, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  float b[] = { 0.5, 0.5156862745098039, 0.5313725490196078, 0.5470588235294118,
      0.5627450980392157, 0.5784313725490196, 0.5941176470588235,
      0.6098039215686275, 0.6254901960784314, 0.6411764705882352,
      0.6568627450980392, 0.6725490196078432, 0.6882352941176471,
      0.7039215686274509, 0.7196078431372549, 0.7352941176470589,
      0.7509803921568627, 0.7666666666666666, 0.7823529411764706,
      0.7980392156862746, 0.8137254901960784, 0.8294117647058823,
      0.8450980392156863, 0.8607843137254902, 0.8764705882352941,
      0.892156862745098, 0.907843137254902, 0.9235294117647059,
      0.9392156862745098, 0.9549019607843137, 0.9705882352941176,
      0.9862745098039216, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      0.9941176470588236, 0.9784313725490197, 0.9627450980392158,
      0.9470588235294117, 0.9313725490196079, 0.915686274509804,
      0.8999999999999999, 0.884313725490196, 0.8686274509803922,
      0.8529411764705883, 0.8372549019607844, 0.8215686274509804,
      0.8058823529411765, 0.7901960784313726, 0.7745098039215685,
      0.7588235294117647, 0.7431372549019608, 0.7274509803921569,
      0.7117647058823531, 0.696078431372549, 0.6803921568627451,
      0.6647058823529413, 0.6490196078431372, 0.6333333333333333,
      0.6176470588235294, 0.6019607843137256, 0.5862745098039217,
      0.5705882352941176, 0.5549019607843138, 0.5392156862745099,
      0.5235294117647058, 0.5078431372549019, 0.4921568627450981,
      0.4764705882352942, 0.4607843137254903, 0.4450980392156865,
      0.4294117647058826, 0.4137254901960783, 0.3980392156862744,
      0.3823529411764706, 0.3666666666666667, 0.3509803921568628,
      0.335294117647059, 0.3196078431372551, 0.3039215686274508,
      0.2882352941176469, 0.2725490196078431, 0.2568627450980392,
      0.2411764705882353, 0.2254901960784315, 0.2098039215686276,
      0.1941176470588237, 0.1784313725490199, 0.1627450980392156,
      0.1470588235294117, 0.1313725490196078, 0.115686274509804,
      0.1000000000000001, 0.08431372549019622, 0.06862745098039236,
      0.05294117647058805, 0.03725490196078418, 0.02156862745098032,
      0.00588235294117645, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0 };

  uint64 index = 255.0 * angle / 180.0;
  return cv::Scalar(255 * b[index], 255 * g[index], 255 * r[index]);
}
