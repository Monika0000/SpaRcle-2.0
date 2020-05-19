#pragma once
#include <iostream>
#include <string>
#include "SRHelper.h"
#include "Settings.h"

namespace SpaRcle {
	using namespace Helper;

	class Hippocampus {
	public:
		Hippocampus();
		~Hippocampus();
	public:
		void SaveDataPack(void*data);
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
		std::string path;
		std::ofstream file;
	private:
		Debug* debug;
		Settings* settings;
		FileManager* file_manager;
	};
}

