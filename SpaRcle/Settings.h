#pragma once
#include <string>

namespace SpaRcle {
	class Settings {
	public:
		Settings(std::string path = "");
		~Settings();
	private:
		std::string path_to_exe;
	public:
		inline const std::string GetPath() { return path_to_exe; }
	};
}

