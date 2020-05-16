#include "pch.h"
#include "FileManager.h"
#include "Debug.h"
#include <iostream>
#include <istream>
#include <fstream>

namespace SpaRcle {
	namespace Helper {
		__interface ISavable {
			virtual bool Save(std::ofstream file) = 0;
			virtual bool Load(std::ifstream file) = 0;
		};

		/*
		class MyClass : public ISavable
		{
		public:
			MyClass(){}
			~MyClass(){}
			bool Save(std::ofstream file) override {

			}
		};
		*/

		FileManager::FileManager() {
			this->open_files = std::vector<std::string>();
		}
		FileManager::~FileManager() {
			this->open_files.clear();
		}
		bool FileManager::Start(Debug* debug) {
			if (debug) this->debug = debug; else {
				Debug::InternalError("FileManager::Start : debugger is nullptr!");
				return false;
			}

			return true;
		}
	}
}