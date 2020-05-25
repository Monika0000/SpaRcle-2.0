#include "pch.h"
#include "FileManager.h"
#include "Debug.h"
#include <iostream>
#include <istream>
#include <fstream>
#include "SRHelper.h"

namespace SpaRcle {
	namespace Helper {

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
			this->data_names  = std::vector<std::string>();
			this->data_adress = std::vector<ISavable*>();
			this->isStart     = false;
			this->isLoad      = false;
		}
		bool FileManager::Start(Debug* debug) {
			if (debug) this->debug = debug; else {
				Debug::InternalError("FileManager::Start : debugger is nullptr!");
				return false;
			}

			isStart = true;

			return true;
		}

		/*
		template <typename T> bool FileManager::Save(ISavable* data, std::string name) {
		ret:
			if (isSave)
				goto ret;
			isSave = true;

			if (Array::Contains(data_names, name)) {
				//debug->Warn("FileManager::Save() : \"" + name + "\" already exists! Skip saving...");
			}
			else {
				this->data_adress.push_back(data);
				this->data_names.push_back(name);
			}

			isSave = false;

			return true;
		}*/
	}
}