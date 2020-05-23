#pragma once
#include <Core.h>
#include <vector>
#include <string>
#include <thread>
#include <SRHelper.h>
#include "MoveKernel.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

class Moving : public Core {
public:
	Moving(std::string core_name, TCP* tcp, Debug* debug, Settings* settings) 
		: Core(core_name, tcp, debug, settings) 
	{
		NNames  = std::vector<std::string>();
		NAdress = std::vector<Neuron*>();
	}

	bool Start() override;

	bool Update() override;

	bool Completed() override {	// Close
		NNames.clear();
		NAdress.clear();

		return true;
	}
private:
	std::vector<std::string> NNames;
	std::vector<Neuron*> NAdress;
};
