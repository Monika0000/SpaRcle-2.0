#pragma once
#include <iostream>
#include <string>
#include "SRHelper.h"
#include "Settings.h"
#include "Neuron.h"

namespace SpaRcle {
	using namespace Helper;

	class Hippocampus {
	public:
		Hippocampus();
		~Hippocampus();
	public:
		bool RegisterCore(std::string core_name) {
			if (!isRun) {
				debug->Info("Hippocampus : register core \"" + core_name + "\"...");
				this->core_names.push_back(core_name);
				this->core_is_sync.push_back(false);
				return true;
			}
			else {
				debug->Error("Hippocampus::RegisterCore() : hippocampus already runned! Register core before running.");
				return false;
			}
		}
		/*
		void Synchronize(std::string& core_name, std::vector<IKernel*> kernel_changes) {
			int index = Array::IndexOf(core_names, core_name);
			if (index != -1) {
				core_is_sync[index] = true;
			ret:
				for (bool b : core_is_sync)
					if (!b) goto ret;

				//! is synchronize!
			} 
		}*/
	public:
		bool Create(Debug*debug, Settings*settings, FileManager* file_manager);
		bool Init();
		bool Run();
		bool Close();
	private:
		bool isCreate;
		bool isInit;
		bool isRun;
	private:
		std::vector<std::string> core_names;
		std::vector<bool>	     core_is_sync;
	private:
		std::thread task;
		std::string path;
		std::ofstream file;
	private:
		Debug* debug;
		Settings* settings;
		FileManager* file_manager;
	};
}

