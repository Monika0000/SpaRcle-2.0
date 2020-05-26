#include "Moving.h"
#include <TCP.h>
#include "Neuron.h"
#include "MoveKernel.h"
#include "FileManager.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

bool Moving::Start() { // Initializing
	this->isCanGetKernelPackages = true;

	return true;
}

bool Moving::Update() {	// Running
	//!-----------------------------------------------------------------------------------------
	//!	�������� ������ �������� �� tcp �������
	//!	�������������� �� ��������� ����� ����������� � ������� �������

	if (HasPackages()) {
		for (size_t t = 0; t < this->recive_data.size(); t++){
			if (((MoveKernel*)recive_data[t])->isNew) {
				///	���� ������ ���������� �� ����� �� ���������� � ��������� ����, �� ������������ ��� �����.
				///	���� �� �� ����������, ��� �� ������, ��� ����� �� ����������!
				RegisterBone((MoveKernel*)recive_data[t]);
			} else {
				///	���� ������ ���������� �� ����� ����������, 
				debug->Log("Changed : "+((MoveKernel*)recive_data[t])->Save());


				/*
					//TODO: do someting...
				*/
			}
		}
		//std::cout << recive_data.size() << std::endl;

		hippocampus->Synchronize(core_name, recive_data);

		ClearRecivePackages();
	}
	//!-----------------------------------------------------------------------------------------

	return true;
}

bool Moving::RegisterBone(MoveKernel* kernel, Neuron* bone_neuron) {
	if (bone_neuron) {
		debug->Error("Moving::RegisterBone() : Neuron does not have to be initialized!");
		return false;
	}

	std::string boneName = kernel->boneName;

	if (!Array::Contains<std::string>(NBones, boneName)) {
		//	TODO:  ����� �������� ����� ���������� ��������� ������, ���� �� ���������� - ������� �����
		//	��� �������� ������������� ���� �������, �� ������� ���� �� ����� � �������, ����������� ����� ������ ������, ������� � ��������
		//
		//	������� ����� ��������� � ����� �����, � ����, � ������
		bone_neuron = static_cast<Neuron*>(file_manager->Load<Neuron>(kernel->boneName));

		if (bone_neuron) {
			NBones.push_back(kernel->boneName);

			bone_neuron->kernel = kernel;
			NAdress.push_back(bone_neuron);

			debug->Log("Moving : register new bone \"" + boneName + "\" has been successfully!");
		}
		else {
			Neuron* n = new Neuron(kernel);
			if (file_manager->Save<Neuron>(n, kernel->boneName)) {
				debug->Log("Moving : register and saving new bone \"" + boneName + "\" has been successfully!");
			} else {
				debug->Warn("Moving : register new bone \"" + boneName + "\" has been failed!");
				return false;
			}
		}
	}

	boneName.clear();
	return true;
}
