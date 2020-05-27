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
		for (int i = 0; i < NAdress.size(); i++) {
			IKernel* kernel = NAdress[i]->kernel;
			debug->Info(kernel->Save());
		}

		for (size_t t = 0; t < this->recive_data.size(); t++){
			if (((MoveKernel*)recive_data[t])->isNew) {
				///	���� ������ ���������� �� ����� �� ���������� � ��������� ����, �� ������������ ��� �����.
				///	���� �� �� ����������, ��� �� ������, ��� ����� �� ����������!
				RegisterBone((MoveKernel*)recive_data[t]);
			} else {
				///	���� ������ ���������� �� ����� ����������, 
				MoveKernel* move = (MoveKernel*)recive_data[t];
				Neuron* bone = static_cast<Neuron*>(this->file_manager->Load<Neuron>(move->boneName));
				if (!bone) {
					debug->Error("Move : bone \"" + std::string(move->boneName) + "\" is not register!");
					return false;
				}
				else {
					delete (MoveKernel*)bone->kernel;
					bone->kernel = move->Copy();
				}

				//MoveKernel* old_data = (MoveKernel*)bone->kernel;

				//debug->Log("Old : "+ old_data->Save());
				//debug->Log("New : "+ move->Save());

				/*
					//TODO: do someting...
				*/

			}
		}
		//std::cout << recive_data.size() << std::endl;

		hippocampus->Synchronize(core_name, recive_data);

		//for (size_t t = 0; t < this->NAdress.size(); t++) {
			//IPackage* pack = (IPackage*)NAdress[t]->kernel;
			//IKernel* bone = NAdress[t]->kernel;
		//tcp->Send(pack);
			//debug->Info("Sending data : " + pack->GetSendData());
			//debug->Info("Sending data : " + bone->Save());
		//	debug->Info(NAdress[t]->kernel->Save());
		//}

		ClearRecivePackages();
	}
	//!-----------------------------------------------------------------------------------------

	return true;
}

bool Moving::RegisterBone(MoveKernel* kernel, Neuron* bone_neuron) { ///\see bone_neuron is nullptr
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

			//bone_neuron->SetKernel(kernel);
			NAdress.push_back(bone_neuron);

			//if (bone_neuron->kernel) delete bone_neuron->kernel;
			//bone_neuron->kernel = kernel;

			debug->Log("Moving : register new bone \"" + boneName + "\" has been successfully!");
		}
		else {
			Neuron* n = new Neuron();
			n->kernel = kernel->Copy();

			if (file_manager->Save<Neuron>((ISavable*)n, kernel->boneName)) {
				debug->Log("Moving : register and saving new bone \"" + boneName + "\" has been successfully!");
				
				//std::cout << kernel << std::endl;

				NBones.push_back(kernel->boneName);
				NAdress.push_back(n);

				//if (n->kernel) delete n->kernel;
				//n->kernel = kernel;

				//NAdress.push_back(n);
				//debug->Info(n->kernel->Save());
				//debug->Info(NAdress[NAdress.size() - 1]->kernel->Save());
			} else {
				debug->Warn("Moving : register new bone \"" + boneName + "\" has been failed!");
				return false;
			}
		}
	}
	//else { debug->Warn("Moving::RegisterBone() : bone \"" + boneName + " already registred!"); boneName.clear(); return false; }

	boneName.clear();
	return true;
}
