#pragma once
#include "Debug.h"
#include <SRHelper.h>
#include "Settings.h"
#include "CentralNeuralSystem.h"

#include <vector>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	using namespace Helper;
	using namespace Network;

	class SRFramework {
	public:
		SRFramework(Debug* debug, Settings* settings, FileManager* file_manager);
		~SRFramework();
	public:
		/*
		bool SetTCP(TCP* tcp) {
			if (isCreate && !isInit) {
				return this->tcp = tcp;
			}
			else if (isCreate) {
				debug->Error("SetTCP : framework is not create!");
				return false;
			}
			else if (!isInit) {
				debug->Error("SetTCP : framework already initialize! Set TCP before init!");
				return false;
			}
		}*/
		bool LoadCore(Core* core) { 
			if (isCreate && !isInit) {
				return this->CNS->AddCore(core);
			}
			else if (isCreate) {
				debug->Error("SRFramework::LoadCore() : framework is not create!");
				return false;
			}
			else if (!isInit) {
				debug->Error("SRFramework::LoadCore() : framework already initialize! Load cores before init!");
				return false;
			}
			else {
				debug->Error("SRFramework::LoadCore() : unknown error!");
				return false;
			}
		}
	public:
		bool IsRun() const { return isRun; }
	public:
		bool Create();
		bool Init();
		bool Run();
		bool Close();
	private:
		bool isCreate;
		bool isInit;
		bool isRun;
	private:
		CentralNeuralSystem* CNS;
	private:
		Settings* settings;
		Debug* debug;
		FileManager* file_manager;
	};
}