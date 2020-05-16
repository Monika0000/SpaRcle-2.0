#include "pch.h"
#include "SRFramework.h"
#include <Input.h>

namespace SpaRcle {
	SRFramework::SRFramework(Debug* debug, Settings* settings) {
		if (!debug) Debug::InternalError("SRFramework : fatal error!");

		isCreate = false;
		isInit = false;
		isRun = false;

		this->file_manager = nullptr;
		this->tcp = nullptr;

		this->CNS = nullptr;

		this->debug = debug;
		if (settings) this->settings = settings; else this->settings = new Settings(Utils::GetPathToExe());
	}
	SRFramework::~SRFramework() { Close(); }

	bool SRFramework::Create() {
		debug->Info("Creating framework...");

		this->CNS = new CentralNeuralSystem();
		if (!this->CNS->Create(debug, settings)) return false;

		this->file_manager = new FileManager();

		isCreate = true;
		return true;
	}
	bool SRFramework::Init() {
		debug->Info("Initializing framework...");
		if (!isCreate) { debug->Error("Framework is not create!"); return false; } else isInit = true;

		this->file_manager->Start(debug);

		if (!this->CNS->Init()) return false;

		return true;
	}
	bool SRFramework::Run() {
		debug->Info("Running framework...");
		if (!isInit) { debug->Error("Framework is not initialize!"); return false; }

		if (!this->CNS->Run()) { debug->Error("Failed running CNS!"); return false; }

		if (!this->tcp->Run()) { debug->Error("Failed running TCP client-server!"); return false; }

		debug->System("All systems are successfully activated!");

		isRun = true;

		while (isRun) {
			if (Input::GetKey(KeyCode::Esc)) break;
		}

		debug->Info("Completed framework!");

		return true;
	}
	bool SRFramework::Close() {
		debug->Info("Close framework...");

		if (CNS) delete CNS;
		if (settings) delete settings;
		if (debug) delete debug;

		return true;
	}
}