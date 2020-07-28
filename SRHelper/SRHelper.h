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
			/*
				angle = angle * pi / 180
				rad   = rad * 180 / pi 

				angle = rad * pi / 180
				rad   = angle * 180 / pi
			*/
		private:
			Math() {};
			~Math() {};
		public:
			inline static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825;
			static const double RadToAngle(double rad) noexcept {
				return rad * PI / 180.0;
			}
			static const double AngleToRad(double angle) noexcept {
				return angle * 180.0 / PI;
			}
			inline static const size_t size_t_max = 18446744073709551615; //18446744073709551615
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
			inline static const CONTEXT GetContext() noexcept {
				CONTEXT context;
				GetThreadContext(GetCurrentThread(), &context);
				return context;
			}
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