﻿#pragma once
#include "Debug.h"
#include "SRHelper.h"
#include "Settings.h"
#include "CentralNeuralSystem.h"

#include <vector>

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows

namespace SpaRcle {
	using namespace Helper;
	class SRFramework {
	public:
		SRFramework(Debug* debug, Settings* settings);
		~SRFramework();
	public:
		bool LoadCore(Core* core) { 
			if (isCreate && !isInit) {
				this->CNS->cores.push_back(core);
				return true;
			}
			else if (isCreate) {
				debug->Erorr("LoadCore : framework is not create!");
				return false;
			}
			else if (!isInit) {
				debug->Erorr("LoadCore : framework already initialize! Load cores before init!");
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
		Debug* debug;
	};
}