#include "Moving.h"

bool Moving::Start() { // Initializing

	return true;
}

bool Moving::Update() {	// Running
	/*
		Получить данные движения из tcp сервера
		Воздействовать на нейронные связи относящиеся к данному сектору
	*/

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
