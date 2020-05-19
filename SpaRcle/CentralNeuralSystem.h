#pragma once
#include <vector>
#include "Core.h"
#include <SRHelper.h>
#include "Settings.h"

#include "Logicality.h"
#include "Causality.h"
#include "Reality.h"
#include "Emotionality.h"

#include "Hippocampus.h"

#include "Neuron.h"

namespace SpaRcle {
	using namespace Helper;

	class CentralNeuralSystem {
	public:
		CentralNeuralSystem() {
			debug = nullptr;
			settings = nullptr;
			file_manager = nullptr;

			isCreate = false;
			isInit = false;
			isRun = false;

			//!//////////////////

			LSystem = nullptr;
			ESystem = nullptr;
			RSystem = nullptr;
			CSystem = nullptr;

			//!//////////////////

			hippocampus = new Hippocampus();
		};
		~CentralNeuralSystem() { Close(); };
	public:
		bool IsRun() { return isRun; }
	public:
		bool Create(Debug* debug, Settings* settings, FileManager* file_manager);
		bool Init();
		bool Run();
		bool Close();
	private:
		bool isCreate;
		bool isInit;
		bool isRun;
	private:
		void TaskFunc();
		std::thread task;
	private:
		Debug* debug;
		Settings* settings;
		FileManager* file_manager;
	public:
		inline const bool AddCore(Core* core) { cores.push_back(core); return true; };
	private:
		std::vector<Core*> cores;
	private:
		Reality*		RSystem;
		Emotionality*	ESystem;
		Causality*		CSystem;
		Logicality*		LSystem;

		Hippocampus* hippocampus;
	};
}

