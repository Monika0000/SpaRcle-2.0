#include <iostream>
#include <SRFramework.h>
#include <SRHelper.h>

#include "Moving.h"

using namespace SpaRcle;
using namespace SpaRcle::Helper;

int main() {
	/*
	//Vector3* vector = Vector3::FromString("(2,sf3 d25 1.3)");
	//std::cout << vector->GetString() << std::endl;

	//std::string* arr = String::FixedSplit("data data1 lol hah", " ", 4);
	//for (int i = 0; i < 4; i++) std::cout << arr[i] << std::endl;

	while (false) {
		std::vector<int> keys = Input::GetPressKeyIndexes();
		for (int k : keys)
			std::cout << k << " ";
		if(keys.size() > 0)
			std::cout << "\n";
	}

	*/

	//std::string str = "123123[LOL]flkdgfgds;lk"; size_t end = 0;
	//std::cout << String::BetweenCharacters(str, '[', ']', 0, &end) << " " << end << std::endl;

	//std::string str = "12345|qqqqq";
	//std::cout << String::Remove(str, '|') << "\n" << str << std::endl;

	Settings* settings = new Settings();
	Debug* debug = new Debug(settings->GetPath());

	SRFramework* framework = new SRFramework(debug, settings);
	framework->Create();

	//framework->SetTCP(new TCP("localhost", 1111, debug));
	Moving* moving = new Moving(
		"moving",
		//new TCP("127.0.0.1", 1025, debug),
		new TCP("127.0.0.1", 1025, debug),
		debug,
		settings);

	framework->LoadCore(moving);

	framework->Init();
	framework->Run();
	framework->Close();
	
}