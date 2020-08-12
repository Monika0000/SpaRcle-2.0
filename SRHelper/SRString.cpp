#include "pch.h"
#include "SRString.h"
#define _CRT_SECURE_NO_WARNINGS

std::vector<std::string> SpaRcle::Helper::String::SplitWithoutBacktick(std::string str, char c) {
	std::vector<std::string> arr;
	
	std::string temp = "";

	bool backtick = false;

	for (size_t t = 0; t < str.size(); t++) {
		if (str[t] == '\"') {
			temp += str[t];
			backtick = !backtick;
		}
		else
			if (!backtick && str[t] == c) {
				arr.push_back(temp);
				temp = "";
			}
			else temp += str[t];
	}

	if (!temp.empty()) arr.push_back(temp);

	return arr;
}
