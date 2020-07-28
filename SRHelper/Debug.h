#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <consoleapi2.h>
#include <WinBase.h>
#include <Psapi.h>
#include "Vectors.h"

namespace SpaRcle {
	namespace Helper {
		enum class ConsoleColor{
			Black = 0,
			Blue = 1,
			Green = 2,
			Cyan = 3,
			Red = 4,
			Magenta = 5,
			Brown = 6,
			LightGray = 7,
			DarkGray = 8,
			LightBlue = 9,
			LightGreen = 10,
			LightCyan = 11,
			LightRed = 12,
			LightMagenta = 13,
			Yellow = 14,
			White = 15
		};

		class Debug {
		 	enum class Type {
				_Log, _Info, _System, _Warning, _Error, _Fatal, _Debug, _Network, _Library, _Graph, _Shader, _Script, _ScriptError
			};
		public:
			Debug(std::string path, bool init_color_therme = true);
			~Debug();
		public:
			inline void SetConsoleEnable(bool v) { isConsole = v; }
			void SetShowMemoryLoad(bool v) { show_use_memory = v; }
		public:
			inline void Log(std::string msg) { Print(msg, Type::_Log, 0); } //, int deep_level = 0
			inline void Info(std::string msg) { Print(msg, Type::_Info, 0); }	
			inline void Warn(std::string msg) { Print(msg, Type::_Warning, 0); }
			inline void Error(std::string msg) { Print(msg, Type::_Error, 0); }
			inline void System(std::string msg) { Print(msg, Type::_System, 0); }
			inline void Network(std::string msg) { Print(msg, Type::_Network, 0); }
			inline void Graph(std::string msg) { Print(msg, Type::_Graph, 0); }
			inline void Shader(std::string msg) { Print(msg, Type::_Shader, 0); }
			inline void Script(std::string msg) { Print(msg, Type::_Script, 0); }
			inline void ScriptError(std::string msg) { Print(msg, Type::_ScriptError, 0); }

			static inline void SysGraphError(std::string msg) { 
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Red));
				std::cout << "[SysGraphError] ";
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Black));
				std::cout << msg + "\n";
			}
			static inline void InternalWarning(std::string msg) { 
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Brown));
				std::cout << "[Internal warning] ";
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Black));
				std::cout << msg + "\n"; 
			}
			static inline void InternalError(std::string msg) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Red));
				std::cout << "[Internal error] ";
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Black));
				std::cout << msg + "\n";
			}
			static inline void Library(std::string msg) {
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Green));
				std::cout << "[Library] ";
				SetConsoleTextAttribute(console, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Black));
				std::cout << msg + "\n";
			}

			static inline void InitColorTherme() {
				if(!ColorThermeIsEnabled)
					system("color 70");
				ColorThermeIsEnabled = true;
			}
		private:
			static bool ColorThermeIsEnabled;
			bool use = false;
			bool show_use_memory;
			HANDLE hConsole = 0;
		private:
			std::ofstream log_file;
			bool isConsole;
			std::string prefix;
			std::string path_log;
		private:
			void Print(std::string& msg, Type type, int deep_level = 0);
		};
	}
}

