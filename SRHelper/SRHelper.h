#pragma once
#include <Windows.h>
#include "Debug.h"
#include "FileManager.h"
#include "Input.h"
#include "TCP.h"
#include <thread>	

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	namespace Helper {
		class Math {
		private:
			Math() {};
			~Math() {};
		public:
			inline double Round(double x) { return ((x * 100) / 100); /*return floor(x * 100) / 100;*/ }
		};

		class Array {
		private:
			~Array() { };
			Array() { };
		public:
			template <typename T> const bool Contains(std::vector<T>& Vec, const T& Element) {
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
	}
}