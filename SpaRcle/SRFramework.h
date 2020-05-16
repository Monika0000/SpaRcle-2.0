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
		SRFramework(Debug* debug, Settings* settings);
		~SRFramework();
	public:
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
		}
		bool LoadCore(Core* core) { 
			if (isCreate && !isInit) {
				return this->CNS->AddCore(core);
			}
			else if (isCreate) {
				debug->Error("LoadCore : framework is not create!");
				return false;
			}
			else if (!isInit) {
				debug->Error("LoadCore : framework already initialize! Load cores before init!");
				return false;
			}
		}
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
		TCP* tcp;
		Debug* debug;
		FileManager* file_manager;
	};
}