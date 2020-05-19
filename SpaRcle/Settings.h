#pragma once
#include <string>

namespace SpaRcle {
	class Settings {
	public:
		Settings(std::string path = "");
		~Settings();
	private:
		std::string path_to_exe;
		std::string memory_path;
	public:
		inline const std::string GetPath() { return path_to_exe; }
		inline const std::string GetMemoryPath() { return memory_path;  }
	};
}

