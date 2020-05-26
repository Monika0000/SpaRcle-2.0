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
	IKernel* KernelPackagesReciveMethod() override {
		MoveKernel* mkernel = new MoveKernel();
		if (tcp->Recv(mkernel)) {
			return mkernel;
		}
		delete mkernel;
		return nullptr;
	}
	void FreeKernel(IKernel* kernel) override { delete (MoveKernel*)kernel; }

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
