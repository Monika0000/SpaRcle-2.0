#pragma once
#include <Core.h>
#include <vector>
#include <string>
#include <thread>
#include <SRHelper.h>
#include "Neuron.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

class Moving : public Core {
public:
	Moving(std::string core_name, TCP* tcp, Debug* debug, Settings* settings, FileManager*file_manager) 
		: Core(core_name, tcp, debug, settings, file_manager) 
	{

	}

	bool Start() override;

	/*
	void ClearRecivePackages() {
		for (size_t t = 0; t < recive_data.size(); t++)
			if (recive_data[t]) {
				std::cout << "free " << recive_data[t] << std::endl;
				//delete recive_data[0];
				delete (MoveKernel*)recive_data[t];
			}
		if(recive_data.size() > 0)
			recive_data.clear();
		isWaitPackage = true;
	}
	*/
	bool Update() override;

	bool Completed() override {	// Close

		return true;
	}
//private:
	//bool RegisterBone(Neuron* bone_neuron);
private:
	//std::vector<std::string> NBones;
	//std::vector<Neuron*> NAdress;
};
