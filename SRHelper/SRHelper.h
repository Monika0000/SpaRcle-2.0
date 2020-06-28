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
#include <cstdio>
#include "GraphUtils.h"
#include "SRRandom.h"

#include "File.h"

#include "SRString.h"

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

		class EventsManager {
		private:
			EventsManager() {};
			~EventsManager() {};
		public:
			enum class Events {
				Exit, Error
			};
		private:
			static std::vector<Events> events;
		public:
			static void PushEvent(Events _event) {
				if (Array::Contains<EventsManager::Events>(events, _event))
					return;
				else
					events.push_back(_event);
			}
			static bool PopEvent(Events _event) {
				int index = Array::IndexOf<EventsManager::Events>(events, _event);
				if (index != -1) {
					events.erase(events.begin() + index);
					return true;
				}
				else
					return false;
			}
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
			static long int GetCurrentMemoryLoad() {
				PROCESS_MEMORY_COUNTERS pmc;
				BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
				//	&memCounter,
				//	sizeof(memCounter));
				if (result)
					return (long int)pmc.PeakWorkingSetSize;
				else
					return -1;
			}
		};
	}
}