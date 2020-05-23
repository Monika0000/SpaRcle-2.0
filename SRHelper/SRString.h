#pragma once
#include <Windows.h>
#include <thread>	
#include <random>
#include <ostream>
#include <string>
#include <sstream>
#include "SRArray.h"
#include "Debug.h"
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
			static std::vector<std::string> Split(std::string text, std::string chr) {
				std::vector<std::string> arr;
				std::size_t prev = 0;
				std::size_t next;
				std::size_t delta = chr.length();

				while ((next = text.find(chr, prev)) != std::string::npos) {
					arr.push_back(text.substr(prev, next - prev));
					prev = next + delta;
				}
				arr.push_back(text.substr(prev));

				return arr;
			}
			
			/* WARNING : Can return nullptr! */
			static std::string* FixedSplit(std::string text, std::string chr, size_t count_elements) {
				std::string* fixed = new std::string[count_elements];

				std::size_t prev = 0;
				std::size_t next;
				std::size_t delta = chr.length();

				size_t found = 0;

				while ((next = text.find(chr, prev)) != std::string::npos) {
					fixed[found] = text.substr(prev, next - prev);
					prev = next + delta;

					found++;

					if (found >= count_elements) {
						Debug::InternalError("String::FixedSplit() : real count elements more fixed count!\n\tText : "+
							text+"\n\tFixed count : "+std::to_string(count_elements));
						return nullptr;
					}
				}
				fixed[found] = text.substr(prev);

				return fixed;
			}
		};
	}
}