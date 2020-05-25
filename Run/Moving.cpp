#include "Moving.h"
#include <TCP.h>
#include "Neuron.h"
#include "MoveKernel.h"
#include "FileManager.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

bool Moving::Start() { // Initializing

	return true;
}

bool Moving::Update() {	// Running
	//!-----------------------------------------------------------------------------------------
	//!	Получить данные движения из tcp сервера
	//!	Воздействовать на нейронные связи относящиеся к данному сектору

	//MoveKernel* mkernel = static_cast<MoveKernel*>(tcp->Recv<MoveKernel>());
	MoveKernel* mkernel = (MoveKernel*)(tcp->Recv<MoveKernel>());

	if (mkernel) {
		if (mkernel->isNew) {
			RegisterBone(mkernel);

			MoveKernel* k = (MoveKernel *)((Neuron*)(file_manager->Load<Neuron>(mkernel->boneName)))->kernel;
			debug->Info(k->boneName);
		}
		else
			debug->Log(mkernel->Save());

		delete mkernel;
	}
	//if (!data.empty()) { //! Если данные присутствуют
		//std::cout << mkernel->boneName << std::endl;
		//debug->Log("sdsad");
		//std::cout << debug << std::endl;
	//}
	//!-----------------------------------------------------------------------------------------
	
	std::string name = "";
	if (Input::GetKey(KeyCode::W))
	{
		name = String::RandomString(10);
	}

	return true;
}

bool Moving::RegisterBone(MoveKernel* kernel, Neuron* bone_neuron) {
	if (bone_neuron) {
		debug->Error("Moving::RegisterBone() : Neuron does not have to be initialized!");
		return false;
	}

	if (!Array::Contains<std::string>(NBones, kernel->boneName)) {
		/*
			TODO:  Здесь вероятно нужно попытаться загрузить нейрон, если не загрузится - создать новый
			При загрузке устанавливаем ядро нейрону, по дефолту ядра не будет в нейроне, загружаться будут только аксоны, синапсы и дендриты

			Нейроны будут зраниться в одной папке, а ядра, в другой
		*/
		bone_neuron = static_cast<Neuron*>(file_manager->Load<Neuron>(kernel->boneName));

		if (bone_neuron) {
			NBones.push_back(kernel->boneName);

			bone_neuron->kernel = kernel;
			NAdress.push_back(bone_neuron);

			debug->Log("Moving : register new bone \"" + kernel->boneName + "\" has been successfully!");
		}
		else {
			Neuron* n = new Neuron(kernel);
			if (file_manager->Save<Neuron>(n, kernel->boneName)) {
				debug->Log("Moving : register and saving new bone \"" + kernel->boneName + "\" has been successfully!");
			} else {
				debug->Warn("Moving : register new bone \"" + kernel->boneName + "\" has been failed!");
				return false;
			}
		}
	}
	return true;
}
