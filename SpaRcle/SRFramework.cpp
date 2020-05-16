#include "pch.h"
#include "SRFramework.h"

namespace SpaRcle {
	SRFramework::SRFramework(Debug* debug, Settings* settings) {
		if (!debug) std::cout << "SRFramework -> fatal\n";

		isCreate = false;
		isInit = false;
		isRun = false;

		this->CNS = nullptr;

		this->debug = debug;
		if (settings) this->settings = settings; else this->settings = new Settings(Utils::GetPathToExe());
	}
	SRFramework::~SRFramework() { Close(); }

	bool SRFramework::Create() {
		debug->Info("Creating framework...");

		this->CNS = new CentralNeuralSystem();
		if (!this->CNS->Create(debug, settings)) return false;

		isCreate = true;
		return true;
	}
	bool SRFramework::Init() {
		debug->Info("Initializing framework...");
		if (!isCreate) { debug->Erorr("Framework is not create!"); return false; } else isInit = true;

		if (!this->CNS->Init()) return false;

		return true;
	}
	bool SRFramework::Run() {
		debug->Info("Running framework...");
		if (!isInit) { debug->Erorr("Framework is not initialize!"); return false; } else isRun = true;

		if (this->CNS->Run()) return false;

		while (isRun) {
			std::cin;
		}

		debug->Info("Completed framework!");

		return true;
	}
	bool SRFramework::Close() {
		debug->Info("Close framework...");

		if (!CNS->Close()) debug->Warn("Failed close CNS!");

		///////////////////////////////////////

		if (CNS) delete CNS;
		if (settings) delete settings;
		if (debug) delete debug;

		return true;
	}
}