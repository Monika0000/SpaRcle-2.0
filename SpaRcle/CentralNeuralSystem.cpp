#include "pch.h"
#include "CentralNeuralSystem.h"
#include "Core.h"
#include "Logicality.h"

namespace SpaRcle {
	using namespace Network;
	using namespace Helper;

	bool CentralNeuralSystem::Create(Debug* debug, Settings* settings, FileManager* file_manager) {
		if (!debug) { Debug::InternalError("CNS : debug is nullptr!"); return false; } else this->debug = debug;

		debug->Info("Creating CNS...");

		if (!settings) { debug->Error("CNS : settings is nullptr!"); return false; } else this->settings = settings;

		if (!file_manager) { debug->Error("CNS : file manager is nullptr!"); return false; } else this->file_manager = file_manager;

		this->CSystem = new Causality(debug, settings);
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

		for (Core* core : cores) 
			if (!core->Init(LSystem, CSystem, hippocampus)) {
				debug->Error("Failed initializing core \"" + core->GetName() + "\"!");
				return false;
			}
			else if(!hippocampus->RegisterCore(core->GetName())) {
				debug->Error("Failed register core \"" + core->GetName() + "\"!");
				return false;
			}

		//!///////////////////////////////

		isInit = true;

		return true;
	}
	bool CentralNeuralSystem::Run() {
		debug->Info("Running CNS...");
		
		if (!isInit) { debug->Error("CNS is not initialize!"); return false; }

		//!/////////////////////////////////////////////////////////////

		CSystem->Run();
		//LSystem->Run();
		//ESystem->Run();
		//RSystem->Run();

		if (!this->hippocampus->Run()) { debug->Error("CNS : failed running hippocampus!"); return false; }

		for (Core* core : cores)
			if (!core->Run()) {
				debug->Error("Failed running core \"" + core->GetName() + "\"!");
				return false;
			}

		//!/////////////////////////////////////////////////////////////

		this->isRun = true;

		this->task = std::thread(&CentralNeuralSystem::TaskFunc, this);

		return true;
	}
	void CentralNeuralSystem::TaskFunc() {
		Sleep(1);
		while (this->IsRun()) {
			for (Core* core : this->cores) {
				//core->GetData();
			}
		}
	}

	bool CentralNeuralSystem::Close() {
		debug->Info("Close CNS...");

		isRun = false;

		CSystem->Close();
		//LSystem->Close();
		//ESystem->Close();
		//RSystem->Close();

		//!///////////////////////////////

		for (Core* core : cores) core->Close();

		if (this->hippocampus) this->hippocampus->Close();

		//!///////////////////////////////

		task.join();

		return true;
	}
}
