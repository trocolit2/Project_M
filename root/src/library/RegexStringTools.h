/*
 * RegexStringTools.h
 *
 *  Created on: Nov 26, 2014
 *      Author: tiagotrocoli
 */

#ifndef SRC_LIBRARY_REGEXSTRINGTOOLS_H_
#define SRC_LIBRARY_REGEXSTRINGTOOLS_H_

#include <string>
#include <vector>

class RegexStringTools {
public:
	static std::vector<std::string> regexGet(std::string input,
			std::string regex, unsigned int* firstPosition = 0);
	static std::string fillSizeDigit(int number, unsigned int digitSize);
};

#endif /* SRC_LIBRARY_REGEXSTRINGTOOLS_H_ */
