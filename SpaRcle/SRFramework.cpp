#include "pch.h"
#include "SRFramework.h"
#include <Input.h>
#include "Package.h"

namespace SpaRcle {
	using namespace Network;

	SRFramework::SRFramework(Debug* debug, Settings* settings) {
		if (!debug) Debug::InternalError("SRFramework : debug is nullptr!");
		if (!settings) debug->Error("SRFramework : settings is nullptr!");

		isCreate = false;
		isInit = false;
		isRun = false;

		this->file_manager = nullptr;

		this->CNS = nullptr;

		this->debug = debug;
		if (settings) this->settings = settings; else this->settings = new Settings(Utils::GetPathToExe());
	}
	SRFramework::~SRFramework() { Close(); }

	bool SRFramework::Create() {
		debug->Info("Creating framework...");

		this->file_manager = new FileManager();

		this->CNS = new CentralNeuralSystem();
		if (!this->CNS->Create(debug, settings, file_manager)) return false;

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
		//if (!this->tcp->Run()) { debug->Error("Failed running TCP client-server!"); return false; }

		//tcp->Send(new Move { "head", 1.f});

		debug->System("All systems are successfully activated!");

		isRun = true;

		while (isRun) {
			if (Input::GetKey(KeyCode::Esc)) break;
		}

		debug->Info("Completed framework!");

		return true;
	}
	bool SRFramework::Close() {
		isRun = false;

		debug->Info("Close framework...");

		if (CNS) delete CNS;
		if (settings) delete settings;

		debug->System("All system completed successfully!");

		if (debug) delete debug;

		return true;
	}
}