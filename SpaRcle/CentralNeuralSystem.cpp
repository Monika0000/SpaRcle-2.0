#include "pch.h"
#include "CentralNeuralSystem.h"

namespace SpaRcle {
	bool CentralNeuralSystem::Create(Debug* debug, Settings* settings) {
		this->debug = debug;
		this->settings = settings;

		if (!debug) { Debug::InternalError("CNS : debug is nullptr!"); return false; }

		debug->Info("Creating CNS...");

		if (!settings) { debug->Error("CNS : settings is nullptr!"); return false; }

		this->CSystem = new Causality();
		this->LSystem = new Logicality();
		this->RSystem = new Reality();
		this->ESystem = new Emotionality();

		isCreate = true;

		return true;
	}
	bool CentralNeuralSystem::Init() {
		debug->Info("Initializing CNS...");

		if (!isCreate) { debug->Error("CNS is not create!"); return false; }

		//!///////////////////////////////

		

		//!///////////////////////////////

		isInit = true;

		return true;
	}
	bool CentralNeuralSystem::Run() {
		debug->Info("Running CNS...");
		
		if (!isInit) { debug->Error("CNS is not initialize!"); return false; }

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

		task.join();

		return true;
	}
}
