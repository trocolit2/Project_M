/*
 * VideoTools.h
 *
 *  Created on: Nov 25, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_VIDEOTOOLS_H_
#define SRC_LIBRARY_VIDEOTOOLS_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>

#define REGEX_PATH_COMPLETE "(.+)/(.+)\\|([0-9]+)\\|(.+)"
#define REGEX_WITHOUT_PATH "(.+)\\|([0-9]+)\\|(.+)"
#define REGEX_WITHOUT_PREFIX "(.+)/\\|([0-9]+)\\|(.+)"
#define REGEX_PATH_FILE "(.+)/(.+)"
#define REGEX_ONLY_FILE "(.+)"
#define REGEX_WITHOUT_PREFIX_AND_PATH "\\|([0-9]+)\\|(.+)"

#define REGEX_PATH_COMPLETE_FLAG 9
#define REGEX_WITHOUT_PATH_FLAG 12
#define REGEX_WITHOUT_PREFIX_FLAG 5
#define REGEX_PATH_FILE_FLAG 14
#define REGEX_ONLY_FILE_FLAG 15
#define REGEX_WITHOUT_PREFIX_AND_PATH_FLAG 2

#define INPUT_READ_IMAGE_SEQUENCE 'S'
#define INPUT_READ_VIDEO 'V'
#define INPUT_READ_CAMERA 'C'

class VideoTools {
public:

	/*
	 * Input for sequence -> flag S
	 * 	EXEC -<FLAG> <PATH>/<PREFIX>|<SIZE_OF_DIGITS>|<SUFIX> <INITIAL_NUMBER> <LENGTH_IMAGES_SEQUENCE>
	 * Example
	 *  EXEC -S path/to/folder/image/sequence/s1.|2|.jpg 0 100
	 *
	 * Input for video -> flag V
	 *  EXEC -<FLAG> <PATH>/<NAME> <INITIAL_NUMBER> <LENGTH_NUMBER>
	 * Example
	 *  EXEC -V path/to/folder/video/mov.mp4
	 *
	 * Input for camera device -> flag C
	 *  EXEC -<FLAG> <DEVICE_NUMBER> <DURATION><SYSTEM_UNIT[hour h, minute m, second s]>
	 * Example
	 *  EXEC -C 0 1.5m
	 *
	 *  Where each <PARAMETER> split for blank space is an item for a vector
	 *  The first position is always the <FLAG>
	 *  Example for image Sequence
	 *  fileInfo[0] = <FLAG>
	 *  fileInfo[1] = <PATH>/<PREFIX>|<SIZE_OF_DIGITS>|<SUFIX>
	 *  fileInfo[2] = <INITIAL_NUMBER>
	 *
	 */
	VideoTools(std::vector<std::string> fileInfo);
	virtual ~VideoTools();
	void initVideoTools(std::vector<std::string> fileInfo);

	std::vector<std::string> getFileInfo();
	cv::Mat getFrame();
	bool isNextFrame();

private:

	// control file type and path
	char flag;
	std::string path;

	// image sequence informations
	std::string prefixName;
	unsigned int sequenceDigitSize;
	std::string sufixName;

	// video properties
	std::string videoName;
	cv::VideoCapture videoCapture;

	// frameControl
	unsigned int frameCurrent;
	unsigned int frameNext;
	unsigned int frameMax;

	// Current frame
	cv::Mat frame;

	//valid and set file information
	void readVideo(std::vector<std::string> fileInfo);
	void readDeviceCamera(std::vector<std::string> fileInfo);
	void readSequenceFrames(std::vector<std::string> fileInfo);

	// INIT firstFrame
	bool isNextImageSequenceFrame();
	bool isNextVideoFrame();

	//tools function
	std::string regexAssemble();
	void inputFrameControl(std::vector<std::string> fileInfo);

};

#endif /* SRC_LIBRARY_VIDEOTOOLS_H_ */
