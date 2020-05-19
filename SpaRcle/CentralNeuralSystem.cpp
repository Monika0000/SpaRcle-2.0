#include "pch.h"
#include "CentralNeuralSystem.h"

namespace SpaRcle {
	bool CentralNeuralSystem::Create(Debug* debug, Settings* settings, FileManager* file_manager) {
		if (!debug) { Debug::InternalError("CNS : debug is nullptr!"); return false; } else this->debug = debug;

		debug->Info("Creating CNS...");

		if (!settings) { debug->Error("CNS : settings is nullptr!"); return false; } else this->settings = settings;

		if (!file_manager) { debug->Error("CNS : file manager is nullptr!"); return false; } else this->file_manager = file_manager;

		this->CSystem = new Causality();
		this->LSystem = new Logicality();
		this->RSystem = new Reality();
		this->ESystem = new Emotionality();

		if (!this->hippocampus->Create(debug, settings, file_manager)) { debug->Error("CNS : failed created hippocampus!"); return false; }

		isCreate = true;

		return true;
	}
	bool CentralNeuralSystem::Init() {
		debug->Info("Initializing CNS...");

		if (!isCreate) { debug->Error("CNS is not create!"); return false; }

		//!///////////////////////////////

		if (!this->hippocampus->Init()) { debug->Error("CNS : failed initialize hippocampus!"); return false; }

		//!///////////////////////////////

		isInit = true;

		return true;
	}
	bool CentralNeuralSystem::Run() {
		debug->Info("Running CNS...");
		
		if (!isInit) { debug->Error("CNS is not initialize!"); return false; }

		//!/////////////////////////////////////////////////////////////

		if (!this->hippocampus->Run()) { debug->Error("CNS : failed running hippocampus!"); return false; }

		//!/////////////////////////////////////////////////////////////

		this->isRun = true;

		this->task = std::thread(&CentralNeuralSystem::TaskFunc, this);

		return true;
	}
	void CentralNeuralSystem::TaskFunc() {
		while (this->IsRun()) {
			for (Core* core : this->cores) {
				//core->GetData();
			}
		}
	}

	bool CentralNeuralSystem::Close() {
		debug->Info("Close CNS...");

		isRun = false;

		if (this->hippocampus) this->hippocampus->Close();

		task.join();

		return true;
	}
}
