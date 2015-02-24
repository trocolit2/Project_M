/*
 * RegexStringTools.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: tiagotrocoli
 */

#include <boost/regex.hpp>
#include "RegexStringTools.h"
#include <iostream>

using namespace std;

std::vector<std::string> RegexStringTools::regexGet(std::string input,
		std::string regex, unsigned int* firstPosition) {

//	cout << " --> INPUT " << input << endl;
	std::vector<std::string> tempVector;
	boost::regex expression(regex, boost::regex::extended);
	boost::smatch stringMatch;
	boost::regex_match(input, stringMatch, expression);
	for (unsigned int i = 1; i < stringMatch.size(); ++i) {
		//	cout << " INDEX " << i << " " << stringMatch[i] << endl;
		if (stringMatch[i].matched) {
			tempVector.push_back(stringMatch[i].str());
			firstPosition == 0 ? (*firstPosition) : (*firstPosition) = i;
		}
//		firstPosition != 0 ?
//				cout << " FIRST POSITION " << (*firstPosition) << endl :
//				cout << " FIRST POSITION " << firstPosition << endl;
	}
	//cout << " SIZE OUT " << tempVector.size() << endl;
	return tempVector;
}

std::string RegexStringTools::fillSizeDigit(int number,
		unsigned int digitSize) {
	std::stringstream out;
	out << number;
	string numeroStr = out.str();

	//cout << "\nNUMBER " << number << " SIZE " << digitSize << endl;
	char saida[digitSize];
	digitSize = digitSize - numeroStr.length();
	saida[digitSize] = '\0';
	for (unsigned int i = 0; i < digitSize; ++i) {
		saida[i] = '0';
	}
	return saida + out.str();
}
