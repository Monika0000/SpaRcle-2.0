#pragma once
#include <vector>
#include <string>

namespace SpaRcle {
	namespace Helper {
		class Debug;
		class FileManager {
		public:
			FileManager();
			~FileManager();
		public:
			bool Start(Debug* debug);
		private:
			bool isStart;
		private:
			Debug* debug;
		private:
			std::vector<std::string> open_files;
		};
	}
}

