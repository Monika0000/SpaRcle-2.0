#include <iostream>
#include <SRFramework.h>
#include <SRHelper.h>

#include "Moving.h"

using namespace SpaRcle;
using namespace SpaRcle::Helper;

int main() {
	while (false) {
		std::vector<int> keys = Input::GetPressKeyIndexes();
		for (int k : keys)
			std::cout << k << " ";
		if(keys.size() > 0)
			std::cout << "\n";
	}


	Settings* settings = new Settings();
	Debug* debug = new Debug(settings->GetPath());

	SRFramework* framework = new SRFramework(debug, settings);
	framework->Create();

	//framework->SetTCP(new TCP("localhost", 1111, debug));
	Moving* moving = new Moving(
		"moving",
		new TCP("localhost", 1000, debug),
		debug,
		settings);

	framework->LoadCore(moving);

	framework->Init();
	framework->Run();
	framework->Close();
}