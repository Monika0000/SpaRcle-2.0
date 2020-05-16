#pragma once
#include <vector>
#include "Logicality.h"
#include "Core.h"
#include <SRHelper.h>
#include "Settings.h"

namespace SpaRcle {
	using namespace Helper;
	class CentralNeuralSystem {
	public:
		CentralNeuralSystem() {
			debug = nullptr;
			settings = nullptr;

			//!//////////////////

			LogicSystem = nullptr;
		};
		~CentralNeuralSystem() { Close(); };
	public:
		bool Create(Debug* debug, Settings* settings);
		bool Init();
		bool Run();
		bool Close();
	private:
		Debug* debug;
		Settings* settings;
	public:
		std::vector<Core*> cores;
	private:
		Logicality* LogicSystem;
	};
}

