#pragma once
#include <Core.h>
#include <vector>
#include <string>
#include <thread>
#include <SRHelper.h>
#include "MoveKernel.h"
#include "Neuron.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

class Moving : public Core {
public:
	Moving(std::string core_name, TCP* tcp, Debug* debug, Settings* settings, FileManager*file_manager) 
		: Core(core_name, tcp, debug, settings, file_manager) 
	{
		NBones  = std::vector<std::string>();
		NAdress = std::vector<Neuron*>();
	}

	bool Start() override;

	bool Update() override;

	bool Completed() override {	// Close
		NBones.clear();
		NAdress.clear();

		return true;
	}
private:
	bool RegisterBone(MoveKernel* kernel, Neuron* bone_neuron = nullptr);
private:
	std::vector<std::string> NBones;
	std::vector<Neuron*> NAdress;
};
