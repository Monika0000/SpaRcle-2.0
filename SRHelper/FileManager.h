#pragma once
#include <vector>
#include <string>
#include "SRArray.h"
#include "Debug.h"

namespace SpaRcle {
	namespace Helper {
		__interface ISavable {
			virtual bool Save(std::ofstream file) = 0;
			virtual bool Load(std::ifstream file) = 0;
		};

		class Debug;

		class FileManager {
		public:
			FileManager();
			~FileManager() { Destroy(); }
		public:
			bool Start(Debug* debug);
			void Destroy() {
				debug->System("Destroying file manager...");

				for (size_t t = 0; t < data_adress.size(); t++)
					delete data_adress[t];

				this->data_names.clear();
				this->isStart = false;
				this->isLoad = false;
			}

			template <typename T> bool Save(ISavable* data, std::string name) {
			ret:
				if (isSave)
					goto ret;
				isSave = true;

				if (Array::Contains(data_names, name)) {
					debug->Warn("FileManager::Save() : \"" + name + "\" already exists! Skip saving...");
				}
				else {
					this->data_adress.push_back(data);
					this->data_names.push_back(name);
				}

				isSave = false;

				return true;
			}
			template <typename T> ISavable* Load(std::string name) {
			ret:
				if (!isLoad) {
					isLoad = true;
					int index = Array::IndexOf(data_names, name);
					if (index == -1) {


						isLoad = false;
						return nullptr;
					}
					else {
						isLoad = false;
						return data_adress[index];
					}
				}
				else goto ret;
			}
		private:
			bool isStart;
			bool isLoad;
			bool isSave;
		private:
			Debug* debug;
		private:
			//std::vector<std::string> open_files;
			//!=====================================
			std::vector<std::string> data_names;
			std::vector<ISavable*>  data_adress;
		};
	}
}

