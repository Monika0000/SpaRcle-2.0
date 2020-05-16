#pragma once
#include <Windows.h>
#include "Debug.h"
#include "FileManager.h"
#include "Input.h"
#include <thread>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	namespace Helper {
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