/*
 * StixelTools_test.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: tiagotrocoli
 */

#include <string>

#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Stixel2D_test"
//VERY IMPORTANT - include this last

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <library/stixelPackage/StixelTools.h>
#include <TestTools.h>

#define STIXEL_RESOURCE_PATH "resource/stixelTests/"

#define BW_FOREGROUND_IMAGE_01 "bwForegroundImage01.jpeg"
#define BW_FOREGROUND_IMAGE_02 "bwForegroundImage02.jpeg"
#define BW_FOREGROUND_IMAGE_03 "bwForegroundImage03.jpeg"
#define BW_FOREGROUND_IMAGE_04 "bwForegroundImage04.jpeg"

#define BACKGROUND_IMAGE_01 "backgroundStixel01.jpg"
#define BACKGROUND_IMAGE_02 "backgroundStixel02.jpg"
#define BACKGROUND_IMAGE_03 "backgroundStixel03.jpg"
#define BACKGROUND_IMAGE_04 "backgroundStixel04.jpg"

//*******************************
// EXTRACT STIXEL FROM FOREGROUND
//*******************************

std::vector<Stixel2D> reduceVectorStixel2DPrecision(
		std::vector<Stixel2D> vector, int precision = 3) {
	std::vector<Stixel2D> temp;
	for (uint64 j = 0; j < vector.size(); ++j) {
		cv::Point2d p1, p2;
		p1.x = TestTools::setDigits((vector[j].getBottonPoint().x), 3);
		p1.y = TestTools::setDigits((vector[j].getBottonPoint().y), 3);
		p2.x = TestTools::setDigits((vector[j].getTopPoint().x), 3);
		p2.y = TestTools::setDigits((vector[j].getTopPoint().y), 3);
		Stixel2D stixel(p1, p2);
		temp.push_back(stixel);
	}
	return temp;
}

std::vector<Stixel2D> extractStixelFromForegroundGT() {

	std::vector<Stixel2D> vectorGT =
			{ Stixel2D(cv::Point2d(209.153, 507.74),
					cv::Point2d(164.107, 335.456)), Stixel2D(
					cv::Point2d(397.491, 163.577),
					cv::Point2d(397.746, 123.124)), Stixel2D(
					cv::Point2d(504.355, 172.357),
					cv::Point2d(505.777, 121.127)), Stixel2D(
					cv::Point2d(344.762, 148.146),
					cv::Point2d(339.655, 119.84)), Stixel2D(
					cv::Point2d(369.734, 163.843),
					cv::Point2d(376.917, 114.163)), Stixel2D(
					cv::Point2d(26.158, 271.657), cv::Point2d(22.204, 112.825)),
					Stixel2D(cv::Point2d(132.026, 196.576),
							cv::Point2d(121.467, 105.654)), Stixel2D(
							cv::Point2d(696.435, 545.242),
							cv::Point2d(639.709, 398.6)), Stixel2D(
							cv::Point2d(46.386, 405.003),
							cv::Point2d(39.884, 321.415)), Stixel2D(
							cv::Point2d(178.777, 366.744),
							cv::Point2d(166.449, 311.485)), Stixel2D(
							cv::Point2d(396.329, 373.562),
							cv::Point2d(412.882, 298.981)), Stixel2D(
							cv::Point2d(378.744, 315.884),
							cv::Point2d(364.901, 276.478)), Stixel2D(
							cv::Point2d(344.21, 295.087),
							cv::Point2d(336.356, 268.301)), Stixel2D(
							cv::Point2d(340.018, 495.152),
							cv::Point2d(343.654, 339.896)), Stixel2D(
							cv::Point2d(41.892, 363.732),
							cv::Point2d(34.123, 257.124)) };
	return vectorGT;
}

BOOST_AUTO_TEST_CASE(extractStixelFromForegroundTestCase) {

	int sizePaths = 4;
	std::vector<std::string> paths(sizePaths);
	paths[0] = BW_FOREGROUND_IMAGE_01;
	paths[1] = BW_FOREGROUND_IMAGE_02;
	paths[2] = BW_FOREGROUND_IMAGE_03;
	paths[3] = BW_FOREGROUND_IMAGE_04;

	std::vector<Stixel2D> vector, temp;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;

	for (int i = 0; i < sizePaths; ++i) {
		cv::Mat testImage = cv::imread(path + path_resource + paths[i],
				CV_LOAD_IMAGE_GRAYSCALE);
		testImage = testImage > 200;
		StixelTools::extractStixelFromForeground(testImage, &vector);
	}

	temp = reduceVectorStixel2DPrecision(vector, 3);
	vector = extractStixelFromForegroundGT();
	BOOST_CHECK_EQUAL_COLLECTIONS(temp.begin(), temp.end(), vector.begin(),
			vector.end());

}

//*******************************
// EXTRACT STIXEL FROM BACKGROUND
//*******************************

void checkVectorStixeis2DBackground(std::string inputPath,
		std::vector<Stixel2D> vectorGT) {

	std::vector<Stixel2D> vector, temp;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;

	cv::Mat testImage = cv::imread(path + path_resource + inputPath);
	StixelTools::extractStixelFromBackground(testImage, &vector);

	for (uint64 i = 0; i < 5; ++i) {
		cv::Point2d p1, p2;
		p1.x = TestTools::setDigits((vector[i].getBottonPoint().x), 3);
		p1.y = TestTools::setDigits((vector[i].getBottonPoint().y), 3);
		p2.x = TestTools::setDigits((vector[i].getTopPoint().x), 3);
		p2.y = TestTools::setDigits((vector[i].getTopPoint().y), 3);
		Stixel2D stixel(p1, p2);
		temp.push_back(stixel);
	}

	BOOST_CHECK_EQUAL_COLLECTIONS(temp.begin(), temp.begin() + 5,
			vectorGT.begin(), vectorGT.end());
}

std::vector<std::vector<Stixel2D> > extractStixelFromBackgroundGT() {

	std::vector<std::vector<Stixel2D> > vectorGT(4);
	vectorGT[0] = {Stixel2D(cv::Point2d(192.226, 414.253), cv::Point2d(185.401, 394.452)),
		Stixel2D(cv::Point2d(372.632, 386.803), cv::Point2d(368.866, 346.805)),
		Stixel2D(cv::Point2d(613.123, 425.886), cv::Point2d(488.133, 425.257)),
		Stixel2D(cv::Point2d(113.111, 436.791), cv::Point2d(131.766, 433.715)),
		Stixel2D(cv::Point2d(214.583, 420.816), cv::Point2d(225.779, 419.194))};

	vectorGT[1] = {Stixel2D(cv::Point2d(426.641, 136.975), cv::Point2d(440.822, 134.096)),
		Stixel2D(cv::Point2d(445.6, 133.006), cv::Point2d(483.287, 125.152)),
		Stixel2D(cv::Point2d(606.894, 199.982), cv::Point2d(586.836, 199.37)),
		Stixel2D(cv::Point2d(576.621, 189.559), cv::Point2d(554.375, 185.623)),
		Stixel2D(cv::Point2d(611.748, 202.219), cv::Point2d(638.351, 198.492))};

	vectorGT[2] = {Stixel2D(cv::Point2d(296.545, 282.035), cv::Point2d(324.374, 278.119)),
		Stixel2D(cv::Point2d(404.416, 145.068), cv::Point2d(389.405, 143.958)),
		Stixel2D(cv::Point2d(429.481, 236.896), cv::Point2d(430.547, 170.623)),
		Stixel2D(cv::Point2d(588.49, 203.141), cv::Point2d(590.338, 163.054)),
		Stixel2D(cv::Point2d(391.897, 160.755), cv::Point2d(393.182, 148.259))};

	vectorGT[3] = {Stixel2D(cv::Point2d(380.119, 235.633), cv::Point2d(380.515, 200.623)),
		Stixel2D(cv::Point2d(379.472, 255.665), cv::Point2d(379.995, 238.106)),
		Stixel2D(cv::Point2d(379.351, 274.399), cv::Point2d(379.604, 261.879)),
		Stixel2D(cv::Point2d(384.126, 43.434), cv::Point2d(367.381, 29.993)),
		Stixel2D(cv::Point2d(284.324, 40.125), cv::Point2d(300.66, 38.478))};

	return vectorGT;
}

BOOST_AUTO_TEST_CASE(extractStStixelFromBackgroundCaseTest) {

	std::vector<std::string> paths(4);
	paths[0] = BACKGROUND_IMAGE_01;
	paths[1] = BACKGROUND_IMAGE_02;
	paths[2] = BACKGROUND_IMAGE_03;
	paths[3] = BACKGROUND_IMAGE_04;

	std::vector<std::vector<Stixel2D> > vectorGT;
	vectorGT = extractStixelFromBackgroundGT();

	for (uint i = 0; i < vectorGT.size(); ++i) {
		checkVectorStixeis2DBackground(paths[i], vectorGT[i]);
	}
}

//******************
// HISTOGRAM STIXEL
//******************

BOOST_AUTO_TEST_CASE(histogramAngleStixel2DSimpleTestCase) {

	std::vector<Stixel2D> stixeis1;
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(0, 1)));
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(1, 0)));
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(1, 1)));
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(0, 1)));
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(1, 0)));
	stixeis1.push_back(Stixel2D(cv::Point2d(0, 0), cv::Point2d(1, 1)));

	std::vector<uint> out = StixelTools::histogramAngleStixel2D(stixeis1, 18);
	std::vector<uint> gtOut = { 2, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
			0, 0 };

	BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(), out.end(), gtOut.begin(),
			gtOut.end());
}

BOOST_AUTO_TEST_CASE(histogramAngleStixel2DTestCase) {

	std::vector<Stixel2D> stixeis1;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;
	std::string inputPath = BACKGROUND_IMAGE_01;
	uint stixelTotal = 0;

	cv::Mat testImage = cv::imread(path + path_resource + inputPath);
	StixelTools::extractStixelFromBackground(testImage, &stixeis1);

	std::vector<uint> out = StixelTools::histogramAngleStixel2D(stixeis1, 18);
	std::vector<uint> gtOut = { 119, 60, 17, 3, 4, 7, 6, 34, 327, 43, 3, 4, 2,
			6, 4, 8, 39, 95 };

	stixelTotal = stixeis1.size();

	for (uint i = 0; i < out.size(); ++i)
		stixelTotal -= out[i];

	BOOST_CHECK_EQUAL(0, stixelTotal);

	BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(), out.end(), gtOut.begin(),
			gtOut.end());
}

BOOST_AUTO_TEST_CASE(histogramAngleStixel2DDrawTestCase) {

	std::vector<Stixel2D> stixeis1;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;
	std::string inputPath = BACKGROUND_IMAGE_01;

	cv::Mat testImage = cv::imread(path + path_resource + inputPath);
	StixelTools::extractStixelFromBackground(testImage, &stixeis1);

	cv::Mat gtImageHist10Beans = cv::imread(
			path + path_resource + "histAngleStixel2D10Beans.jpeg");
	cv::Mat gtImageHist20Beans = cv::imread(
			path + path_resource + "histAngleStixel2D20Beans.jpeg");
	cv::Mat gtImageHist180Beans = cv::imread(
			path + path_resource + "histAngleStixel2D180Beans.jpeg");

	cv::Mat bigImage;
	std::string nameImage = "actualHistogram.jpeg";

	StixelTools::histogramAngleStixel2D(stixeis1, 10, &bigImage);
	TestTools::writeImageJpeg(nameImage, bigImage);
	bigImage = cv::imread(nameImage);

	cv::Scalar gtCheck = cv::sum(gtImageHist10Beans);
	cv::Scalar outCheck = cv::sum(bigImage);

	BOOST_CHECK_EQUAL(gtCheck, outCheck);

	StixelTools::histogramAngleStixel2D(stixeis1, 20, &bigImage);
	TestTools::writeImageJpeg(nameImage, bigImage);
	bigImage = cv::imread(nameImage);

	gtCheck = cv::sum(gtImageHist20Beans);
	outCheck = cv::sum(bigImage);

	BOOST_CHECK_EQUAL(gtCheck, outCheck);

	StixelTools::histogramAngleStixel2D(stixeis1, 180, &bigImage);
	TestTools::writeImageJpeg(nameImage, bigImage);
	bigImage = cv::imread(nameImage);

	gtCheck = cv::sum(gtImageHist180Beans);
	outCheck = cv::sum(bigImage);

	BOOST_CHECK_EQUAL(gtCheck, outCheck);
}

BOOST_AUTO_TEST_CASE(gethistogramAngleIntervalTestCase) {

	std::vector<Stixel2D> stixeis;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;
	std::string inputPath = BACKGROUND_IMAGE_01;

	cv::Mat testImage = cv::imread(path + path_resource + inputPath);
	StixelTools::extractStixelFromBackground(testImage, &stixeis);

	std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18,
			&testImage);

	std::vector<Stixel2D> stixeis1, stixeis2, stixeis3, residual;

	stixeis1 = StixelTools::gethistogramAngleInterval(stixeis, hist, 9, 2);
	stixeis2 = StixelTools::gethistogramAngleInterval(stixeis, hist, 0, 2);
	stixeis3 = StixelTools::gethistogramAngleInterval(stixeis, hist, 17, 2,
			&residual);

	std::vector<uint> hist1 = StixelTools::histogramAngleStixel2D(stixeis1, 18);
	std::vector<uint> hist2 = StixelTools::histogramAngleStixel2D(stixeis2, 18);
	std::vector<uint> hist3 = StixelTools::histogramAngleStixel2D(stixeis3, 18);
	std::vector<uint> hist4 = StixelTools::histogramAngleStixel2D(residual, 18);

	std::vector<uint> gtHist1 = { 0, 0, 0, 0, 0, 0, 0, 34, 327, 43, 3, 4, 0, 0,
			0, 0, 0, 0 };
	std::vector<uint> gtHist2 = { 119, 60, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 39, 95 };
	std::vector<uint> gtHist3 = { 119, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 8, 39, 95 };
	std::vector<uint> gtHist4 = { 0, 0, 17, 3, 4, 7, 6, 34, 327, 43, 3, 4, 2, 6,
			4, 0, 0, 0 };
	BOOST_CHECK_EQUAL_COLLECTIONS(hist1.begin(), hist1.end(), gtHist1.begin(),
			gtHist1.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(hist2.begin(), hist2.end(), gtHist2.begin(),
			gtHist2.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(hist3.begin(), hist3.end(), gtHist3.begin(),
			gtHist3.end());
	BOOST_CHECK_EQUAL_COLLECTIONS(hist4.begin(), hist4.end(), gtHist4.begin(),
			gtHist4.end());
}

BOOST_AUTO_TEST_CASE(getMaxBeanAngleIntevalTestCase) {

	std::vector<Stixel2D> stixeis, stixeis1;
	std::string path = PATH_RELATIVE_ROOT_TESTBIN;
	std::string path_resource = STIXEL_RESOURCE_PATH;
	std::string inputPath = BACKGROUND_IMAGE_01;

	cv::Mat testImage = cv::imread(path + path_resource + inputPath);
	StixelTools::extractStixelFromBackground(testImage, &stixeis);

	std::vector<uint> hist = StixelTools::histogramAngleStixel2D(stixeis, 18);

	stixeis1 = StixelTools::getMaxBeanAngleInteval(stixeis, hist, 4);
	std::vector<uint> hist1 = StixelTools::histogramAngleStixel2D(stixeis1, 18);

	std::vector<uint> gtHist1 = { 0, 0, 0, 0, 4, 7, 6, 34, 327, 43, 3, 4, 2, 0,
			0, 0, 0, 0 };

	BOOST_CHECK_EQUAL_COLLECTIONS(gtHist1.begin(), gtHist1.end(), hist1.begin(),
			hist1.end());
}
