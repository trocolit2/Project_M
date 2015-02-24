#define BOOST_TEST_DYN_LINK
//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "RegexStringTools_test"
//VERY IMPORTANT - include this last

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <cmath>
#include <library/RegexStringTools.h>

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

#include <iostream>

/*REGEX GET SESSION TEST CASES
 *
 * Teste all cases used in VideoTools class.
 * */

// INPUT TEST CASES
std::vector<std::string> imageSequencePathCompleteTest(std::string *inputText) {

	std::vector<std::string> groundTruthVector(4);
	groundTruthVector[0] = "path/to/the/image/sequence";
	groundTruthVector[1] = "bla1";
	groundTruthVector[2] = "2";
	groundTruthVector[3] = ".jpg";
	(*inputText) = groundTruthVector[0] + "/" + groundTruthVector[1] + "|"
			+ groundTruthVector[2] + "|" + groundTruthVector[3];
	return groundTruthVector;
}

std::vector<std::string> imageSequenceWithoutPathTest(std::string *inputText) {

	std::vector<std::string> groundTruthVector(3);
	groundTruthVector[0] = "bla1";
	groundTruthVector[1] = "2";
	groundTruthVector[2] = ".jpg";
	(*inputText) = groundTruthVector[0] + "|" + groundTruthVector[1] + "|"
			+ groundTruthVector[2];
	return groundTruthVector;
}

std::vector<std::string> pathNameSimple(std::string *inputText) {

	std::vector<std::string> groundTruthVector(2);
	groundTruthVector[0] = "path/to/video";
	groundTruthVector[1] = "mov.mp4";
	(*inputText) = groundTruthVector[0] + "/" + groundTruthVector[1];
	return groundTruthVector;
}

std::vector<std::string> nameSimple(std::string *inputText) {

	std::vector<std::string> groundTruthVector(1);
	groundTruthVector[0] = "mov.mp4";
	(*inputText) = groundTruthVector[0];
	return groundTruthVector;
}

std::vector<std::string> imageSequenceWithouPrefix(std::string *inputText) {

	std::vector<std::string> groundTruthVector(3);
	groundTruthVector[0] = "path/to/the/image/sequence";
	groundTruthVector[1] = "2";
	groundTruthVector[2] = ".jpg";
	(*inputText) = groundTruthVector[0] + "/|" + groundTruthVector[1] + "|"
			+ groundTruthVector[2];
	return groundTruthVector;
}

std::vector<std::string> imageSequenceNameOnly(std::string *inputText) {

	std::vector<std::string> groundTruthVector(2);
	groundTruthVector[0] = "2";
	groundTruthVector[1] = ".jpg";
	(*inputText) = "|" + groundTruthVector[0] + "|" + groundTruthVector[1];
	return groundTruthVector;
}

std::string regexAll() {
	std::string allregex = std::string(REGEX_WITHOUT_PREFIX_AND_PATH) + "|"
			+ std::string(REGEX_WITHOUT_PREFIX) + "|"
			+ std::string(REGEX_PATH_COMPLETE) + "|"
			+ std::string(REGEX_WITHOUT_PATH) + "|"
			+ std::string(REGEX_PATH_FILE) + "|" + std::string(REGEX_ONLY_FILE);
	return allregex;
}

// TEST CASES

BOOST_AUTO_TEST_CASE(regexGetCompletePathImageSequence) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequencePathCompleteTest(
			&inputText);
	std::string regex = REGEX_PATH_COMPLETE;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetWithoutPathImageSequence) {
	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceWithoutPathTest(
			&inputText);
	std::string regex = REGEX_WITHOUT_PATH;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetWrongPathPattern) {

	std::string inputText = " ouahsuohda121230712-1_(&-12)";
	std::string regex = REGEX_WITHOUT_PATH;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL(0, regexOut.size());
}

BOOST_AUTO_TEST_CASE(regexGetPathName) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = pathNameSimple(&inputText);
	std::string regex = REGEX_PATH_FILE;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetNameWithoutPath) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = nameSimple(&inputText);
	std::string regex = REGEX_ONLY_FILE;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetWithoutPrefix) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceWithouPrefix(
			&inputText);
	std::string regex = REGEX_WITHOUT_PREFIX;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetWithoutPrefixAndPath) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceNameOnly(
			&inputText);
	std::string regex = REGEX_WITHOUT_PREFIX_AND_PATH;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetALL4PathImageSequencePathCompleteTest) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequencePathCompleteTest(
			&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_PATH_COMPLETE_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());

}
BOOST_AUTO_TEST_CASE(regexGetALL4PathImageSequenceWithoutPath) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceWithoutPathTest(
			&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_WITHOUT_PATH_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}
BOOST_AUTO_TEST_CASE(regexGetALL4PathNameSimple) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = pathNameSimple(&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_PATH_FILE_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}
BOOST_AUTO_TEST_CASE(regexGetALL4NameSimple) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = nameSimple(&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_ONLY_FILE_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetALL4ImageSequenceWithouPrefix) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceWithouPrefix(
			&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_WITHOUT_PREFIX_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

BOOST_AUTO_TEST_CASE(regexGetALL4ImageSequenceNameOnly) {

	std::string inputText = "";
	std::vector<std::string> groundTruthVector = imageSequenceNameOnly(
			&inputText);
	std::string regex = regexAll();
	unsigned int position = 0;
	std::vector<std::string> regexOut = RegexStringTools::regexGet(inputText,
			regex, &position);
	BOOST_CHECK_EQUAL(REGEX_WITHOUT_PREFIX_AND_PATH_FLAG, position);
	BOOST_CHECK_EQUAL_COLLECTIONS(groundTruthVector.begin(),
			groundTruthVector.end(), regexOut.begin(), regexOut.end());
}

//=====================
// FILL SIZE DIGIT TEST
//=====================

BOOST_AUTO_TEST_CASE(fillDigitSizeTestCase) {
	std::vector<std::string> groundTruth;
	groundTruth.push_back("0000001");
	groundTruth.push_back("0101");
	groundTruth.push_back("012340000");
	groundTruth.push_back("-1234");
	groundTruth.push_back("98760");

	for (unsigned int i = 0; i < groundTruth.size(); ++i) {
		int number = std::stoi(groundTruth[i]);
		int size = groundTruth[i].size();
		BOOST_CHECK_EQUAL(groundTruth[i],
				RegexStringTools::fillSizeDigit(number, size));
	}

}
