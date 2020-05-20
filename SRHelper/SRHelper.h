#pragma once
#include <Windows.h>
#include "Debug.h"
#include "FileManager.h"
#include "Input.h"
#include "TCP.h"
#include <thread>	
#include <random>
#include <ostream>
#include <string>
#include <sstream>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	namespace Helper {
		class Math {
		private:
			Math() {};
			~Math() {};
		public:
			inline static double Round(double x) { return ((x * 100) / 100); /*return floor(x * 100) / 100;*/ }
		};

		class Array {
		private:
			~Array() { };
			Array() { };
		public:
			template <typename T> static const bool Contains(std::vector<T>& Vec, const T& Element) {
				if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end()) return true;
				return false;
			};
		};

		class Utils {
		private:
			Utils() {};
			~Utils() {};
		public:
			inline static std::string GetPathToExe() {
				TCHAR cwd[100];
				GetCurrentDirectory(100, cwd);
				std::wstring ws(&cwd[0]);
				return std::string(ws.begin(), ws.end());
			}
		};

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
		};
	}
}