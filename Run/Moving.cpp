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

	//MoveKernel* mkernel = static_cast<MoveKernel*>(tcp->Recv<MoveKernel>());
	MoveKernel* mkernel = (MoveKernel*)(tcp->Recv<MoveKernel>());
	//std::string data;// = 
	//tcp->Recv();
	//PackageString* str = (PackageString*)(tcp->Recv<PackageString>());
	//if (str) std::cout << str->str << std::endl;
	//delete str;


	if (mkernel) {
		debug->Log(mkernel->Save());
	//
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

	if(!name.empty()) if (!Helper::Array::Contains<std::string>(NNames, name)) {
		NNames.push_back(name);
		//std::cout << name << std::endl;
	}

	return true;
}
