#include <iostream>
#include <SRFramework.h>
#include <SRHelper.h>
#include <SRGraphics.h>

#include "Moving.h"

using namespace SpaRcle;
using namespace SpaRcle::Helper;
using namespace SpaRcle::Graphics;

int main(int argcp, char** argv) {
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

	//while(true) Input::PrintPressIndexes();
	while (false) {
		if(Input::GetKeyDown(KeyCode::Enter))
			std::cout << "Down\n";
		if (Input::GetKeyUp(KeyCode::Enter))
			std::cout << "Up\n";
		//std::cout << Input::GetKeyDown(KeyCode::Enter) << " " << Input::GetKeyUp(KeyCode::Enter) << "\n";
	}

	Settings* settings = new Settings();
	Debug* debug = new Debug(settings->GetPath());
	debug->SetShowMemoryLoad(true);

	FileManager* file_manager = new FileManager();

	//!-------------------------------------------------

	SRGraphics* graph = new SRGraphics(argcp, argv, debug);
	if (!graph->Create(
		new Window(
			debug,
			new Camera(debug),
			"SpaRcle",
			600, 500,
			false),
		new Render(debug),
		new Camera(debug))
	) {
		debug->Error("Failed running application! Graph create return's false.");
		return false;
	}
	if (!graph->Init()) {
		debug->Error("Failed running application! Graph init return's false.");
		return false;
	}
	if (!graph->Run()) {
		debug->Error("Failed running application! Graph run return's false.");
		return false;
	}

	//!-------------------------------------------------

	SRFramework* framework = new SRFramework(debug, settings, file_manager);
	framework->Create();

	Moving* moving = new Moving(
		"moving",
		//new TCP("127.0.0.1", 1025, debug),
		new TCP("127.0.0.1", 1025, debug),
		debug,
		settings,
		file_manager);

	framework->LoadCore(moving);

	framework->Init();
	framework->Run();
	framework->Close();

	graph->Close();

	if (debug) delete debug;
}



