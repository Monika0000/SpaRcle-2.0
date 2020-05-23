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
	//!	�������� ������ �������� �� tcp �������
	//!	�������������� �� ��������� ����� ����������� � ������� �������

	MoveKernel* mkernel = static_cast<MoveKernel*>(tcp->Recv<MoveKernel>());
	if (mkernel) { //! ���� ������ ������������


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
