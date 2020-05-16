#pragma once
#include <string>
#include <iostream>
#include <fstream>

namespace SpaRcle {
	namespace Helper {
		enum ConsoleColor {
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
				_Log, _Info, _System, _Warning, _Error, _Fatal
			};
		public:
			Debug(std::string path);
			~Debug();
		public:
			inline void SetConsole(bool v) { isConsole = v; }
		public:
			inline void Log(std::string msg) { Print(msg, Type::_Log); }
			inline void Info(std::string msg) { Print(msg, Type::_Info); }
			inline void Warn(std::string msg) { Print(msg, Type::_Warning); }
			inline void Erorr(std::string msg) { Print(msg, Type::_Error); }
		private:
			std::ofstream log_file;
			bool isConsole;
			std::string prefix;
			std::string path_log;
		private:
			void Print(std::string& msg, Type type);
		};
	}
}

