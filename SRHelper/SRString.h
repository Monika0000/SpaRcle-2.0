#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <thread>	
#include <random>
#include <ostream>

#include <locale>
#include <iostream>

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
			static std::string ReadToChar(std::string& str, const char c, const size_t start = 0, size_t* end = nullptr) {
				std::string nstr = std::string();

				for (size_t t = start; t < str.size(); t++) {
					if (str[t] == c) {
						if (end)
							(*end) = t;
						break;
					}
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
			static std::string ReadWords(const std::string& str, size_t count) {
				std::string result = str;
				result.resize(count);
				return result;
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
			static std::string BetweenCharacters(const std::string text, const char first, const char second, const size_t start = 0, size_t* end = nullptr) {
				std::string result = std::string();

				bool f = false;

				for (size_t t = start; t < text.size(); t++) {
					//std::cout << "t = " << t << std::endl;
					if (!f) {
						if (text[t] == first)
							f = true;
					}
					else {
						if (text[t] != second)
							result += text[t];
						else {
							if (end)
								(*end) = t;

							break;
						}
					}
				}
				return result;
			}
			static int IndexOf(const std::string str, const char c) {
				for (size_t t = 0; t < str.size(); t++) {
					if (str[t] == c)
						return (int)t;
				}

				return -1;
			}
			static std::string Remove(std::string& text, const char c) {
				std::string result = std::string();
				size_t end = 0;

				for (size_t t = 0; t < text.size(); t++) {
					if (text[t] == c) {
						end = t;
						break;
					}
					else
						result += text[t];
				}

				if (text.size() > end)
					text = text.substr(end + 1);

				return result;
			}
			static bool Substring(std::string& str, const char c) {
				for (size_t t = 0; t < str.size(); t++)
					if (str[t] == c)
					{
						str.erase(0, t + 1);
						return true;
					}
				return false;
			}
			static bool Substring(std::string& str, const char c, const char c2) {
				for (size_t t = 0; t < str.size(); t++)
					if (str[t] == c || str[t] == c2) {
						str.erase(0, t + 1);
						return true;
					}
				return false;
			}

			inline static std::string FromCharVector(const std::vector<char>& vs) {
				std::string result(begin(vs), end(vs));
				return result;
			}

			inline static char* FastSubstring(const char* str, const char c, const char c2) {
				size_t len = strlen(str);

				for (size_t fast_sub_t = 0; fast_sub_t < len; fast_sub_t++)
					if (str[fast_sub_t] == c || str[fast_sub_t] == c2) {
						char* to = (char*)malloc(len - (fast_sub_t + 1) + 1);
						strncpy(to, str + (fast_sub_t + 1), len - (fast_sub_t + 1));
						to[len - (fast_sub_t + 1)] = '\0';
						return to;
					}
				return nullptr;
				/*
				static size_t fast_sub_t = 0;
				static size_t len = strlen(str);

				for (fast_sub_t = 0; fast_sub_t < len; fast_sub_t++)
					if (str[fast_sub_t] == c || str[fast_sub_t] == c2) {
						char* buffer = (char*)malloc(fast_sub_t - 0 + 1);
						strncpy(buffer, str + 0, fast_sub_t - 0);
						buffer[fast_sub_t - 0] = '\0';

						return buffer;
					}
				return nullptr;
					*/
			}

			static bool Contains(const char* str, char symb) {
				for (size_t t = 0; t < strlen(str); t++)
					if (str[t] == symb) {
						return true;
					}
				return false;
			}

			inline static bool isCon(std::string str) {
				for (auto& a : str)
					a = tolower(a);
				return (str == "con");
			}

			//!===================================================================
			static const wchar_t* CharsToWchars(const char* str) {
				Debug::InternalWarning("String::CharsToWchars() : It can work wrong! Use : CharsToLPWSTR()");

				std::wostringstream wstm;
				const  std::ctype<wchar_t>& ctfacet = std::use_facet<std::ctype<wchar_t>>(wstm.getloc());
				for (size_t i = 0; i < strlen(str); ++i)
					wstm << ctfacet.widen(str[i]);
				return wstm.str().c_str();
			}
			
			//static LPCWSTR CharsToLPCWSTR(const char* str) { }
			static LPWSTR CharsToLPWSTR(const char* str) {
				size_t size = strlen(str);
				wchar_t* wArr = new wchar_t[size];
				mbstowcs(wArr, str, size + 1);//Plus null
				return wArr;
			}
			static std::string LPWSTRToChars(const wchar_t* str) {
				size_t size = wcslen(str);
				std::cout << size << std::endl;

				std::string chs = std::string(size, ' ');
				for (size_t i = 0; i < size; ++i)
					chs[i] = str[i];
				return chs;
			}

			static std::string LPCWSTRToChars(LPCWSTR str) {
				size_t size = wcslen(str);
				std::string chs = std::string(size, ' ');
				for (size_t i = 0; i < size; ++i)
					chs[i] = str[i];
				return chs;
			}
			//!===================================================================

			static char* CopyChars(char* str) {
				char* rs = new char[strlen(str) + 1];
				strcpy(rs, str);
				return rs;
			}
			static char* CopyStringToCharPointer(std::string str) {
				char* rs = new char[str.size() + 1];
				strcpy(rs, str.c_str());
				return rs;
			}
			static char* CopyStringToCharPointer(std::string& str) {
				char* rs = new char[str.size() + 1];
				strcpy(rs, str.c_str());
				return rs;
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