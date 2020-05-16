#pragma once
#include <vector>
#include "Core.h"
#include <SRHelper.h>
#include "Settings.h"

#include "Logicality.h"
#include "Causality.h"
#include "Reality.h"
#include "Emotionality.h"

namespace SpaRcle {
	using namespace Helper;
	class CentralNeuralSystem {
	public:
		CentralNeuralSystem() {
			debug = nullptr;
			settings = nullptr;

			//!//////////////////

			LSystem = nullptr;
			ESystem = nullptr;
			RSystem = nullptr;
			CSystem = nullptr;
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
		Reality*		RSystem;
		Emotionality*	ESystem;
		Causality*		CSystem;
		Logicality*		LSystem;
	};
}

