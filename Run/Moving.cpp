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
		tcp->Begin();

		for (size_t t = 0; t < this->recive_data.size(); t++){
			if (((MoveKernel*)recive_data[t])->isNew) {
				///	���� ������ ���������� �� ����� �� ���������� � ��������� ����, �� ������������ ��� �����.
				///	���� �� �� ����������, ��� �� ������, ��� ����� �� ����������!
				RegisterBone((MoveKernel*)recive_data[t]);
			} else {
				MoveKernel* new_move = (MoveKernel*)recive_data[t];
				Neuron* bone = static_cast<Neuron*>(this->file_manager->Load<Neuron>(new_move->boneName));
				if (!bone) {
					debug->Error("Move : bone \"" + std::string(new_move->boneName) + "\" is not register!");
					return false;
				}
				//todo	���� ������ ���������� �� ����� ����������
				else {
					MoveKernel* old_move = (MoveKernel*)bone->kernel;
					//!--------------[������������ �������� �� ������ �����, ������� ����� �� �� �����]--------------

					new_move->boneRotation->x += 0.555f;

					tcp->Send(new_move);

					//!----------------------------------------------------------------------------------------------
					delete old_move;
					bone->kernel = new_move->Copy();
				}
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

		tcp->End();
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

			if(bone_neuron->kernel)
				delete (MoveKernel*)bone_neuron->kernel;
			bone_neuron->kernel = kernel->Copy();

			NAdress.push_back(bone_neuron);

			debug->Log("Moving : register new bone \"" + boneName + "\" has been successfully!");
		}
		else {
			Neuron* n = new Neuron();
			n->kernel = kernel->Copy();

			if (file_manager->Save<Neuron>((ISavable*)n, kernel->boneName)) {
				debug->Log("Moving : register and saving new bone \"" + boneName + "\" has been successfully!");

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
	else { debug->Warn("Moving::RegisterBone() : bone \"" + boneName + "\" already registred!"); boneName.clear(); return false; }

	boneName.clear();
	return true;
}
