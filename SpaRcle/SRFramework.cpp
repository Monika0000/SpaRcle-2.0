#include "pch.h"
#include "SRFramework.h"
#include <Input.h>

namespace SpaRcle {
	using namespace Network;

	SRFramework::SRFramework(Debug* debug, Settings* settings, FileManager*file_manager) {
		if (!debug) Debug::InternalError("SRFramework : debug is nullptr!");
		if (!settings) debug->Error("SRFramework : settings is nullptr!");

		isCreate = false;
		isInit = false;
		isRun = false;

		this->CNS = nullptr;

		this->debug = debug;
		this->file_manager = file_manager;
		if (settings) this->settings = settings; else this->settings = new Settings(Utils::GetPathToExe());
	}
	SRFramework::~SRFramework() { Close(); }

	bool SRFramework::Create() {
		debug->Info("Creating framework...");

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

		//Sleep(1000);

		debug->System("All systems are successfully activated!");

		isRun = true;

		while (isRun) {
			if (Input::GetKeyDown(KeyCode::Esc) 
				|| EventsManager::PopEvent(EventsManager::Events::Exit)
				|| EventsManager::PopEvent(EventsManager::Events::Error))
				break;
			else if (Input::GetKeyDown(KeyCode::M)) {
				std::cout << "[Framework] Current memory load is " << Utils::GetCurrentMemoryLoad() / 1024 << "Kb" << std::endl;
			}
			else if (Input::GetKeyUp(KeyCode::M)) {

			}
		}

		debug->Info("Completed framework!");

		return true;
	}
	bool SRFramework::Close() {
		debug->Info("Close framework...");

		isRun = false;

		if (CNS) delete CNS;
		if (settings) delete settings;
		if (file_manager) delete file_manager;

		debug->System("All system completed successfully!");

		return true;
	}
} 