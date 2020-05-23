#pragma once
#include <Windows.h>
#include <thread>	
#include <random>
#include <ostream>
#include <string>
#include <sstream>
#include "SRArray.h"
#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	namespace Helper {
		class String {
		private:
			static std::default_random_engine generator;
			static std::uniform_int_distribution<int> distribution;
			static const std::string VALID_CHARS;
		private:
			String() {  };
			~String() {  };
		public:
			static std::string RandomString(int size) {
				std::ostringstream oss;
				for (std::size_t i = 0; i < size; ++i)
				{
					oss << VALID_CHARS[distribution(generator)];
				}
				return oss.str();
			}
			static std::string ReadToChar(std::string& str, char c) {
				std::string nstr = std::string();

				for (size_t t = 0; t < str.size(); t++) {
					if (str[t] == c)
						break;
					else
						nstr.push_back(str[t]);
				}

				return nstr;
			}
			static std::string ReadToChars(std::string& str, std::vector<char> c) {
				std::string nstr = std::string();

				for (size_t t = 0; t < str.size(); t++) {
					if (Array::Contains<char>(c, str[t]))
						break;
					else
						nstr.push_back(str[t]);
				}

				return nstr;
			}
		};
	}
}