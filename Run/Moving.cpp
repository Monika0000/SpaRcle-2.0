#include "Moving.h"
#include <TCP.h>

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

	MoveKernel* mkernel = static_cast<MoveKernel*>(tcp->Recv<MoveKernel>());
	if (mkernel) { //! Если данные присутствуют


		debug->Log(mkernel->Save());
	}
	//!-----------------------------------------------------------------------------------------
	
	std::string name = "";
	if (Input::GetKey(KeyCode::W))
	{
		name = String::RandomString(10);
	}

	if(!name.empty()) if (!Helper::Array::Contains<std::string>(NNames, name)) {
		NNames.push_back(name);
		std::cout << name << std::endl;
	}

	return true;
}
