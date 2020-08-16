#define NOMINMAX
#define GLEW_STATIC 1

#include <iostream>
#include <SREngine.h>
#include <Debug.h>
#include <SRHelper.h>
#include <SRGraphics.h>

#pragma comment(lib, "SOIL.lib")

using namespace SpaRcle::Helper;
using namespace SpaRcle::Engine;
using namespace SpaRcle::Engine::Scripting;
using namespace SpaRcle::Graphics;

int main(int argcp, char* argv) {
	//while (true) Input::PrintPressIndexes();
	//if (_CrtDumpMemoryLeaks() == TRUE)
	//	std::cerr << "MEMORY LEAK!" << std::endl;
	//std::cout << ((0.1f + 0.2f) * pow(10, 30)) - (0.3f * pow(10, 30)) << std::endl;
	//std::string s = "5/2/1";

	//void* str = (int*)malloc(sizeof(int));
	//(*(int*)str) = 34;
	//std::cout << str << std::endl;
	//std::cout << (*(int*)str) << std::endl;
	//free(str);

	//Json* json = Json::Load("J:\\C++\\SpaRcle\\Resources\\Cache\\test.json");
	//std::cout << json->GetString("str") << std::endl;
	//delete json;

	Debug* debug = new Debug(Utils::GetPathToExe());
	debug->SetShowMemoryLoad(true);

	SREngine* engine = new SREngine(debug);
	SRGraphics* graph = new SRGraphics(argcp, &argv, debug, true);

	Window* window = new Window(
		debug,
		NULL,
		"SpaRcle",
		new ScreenFormats::_1280_720(),
		new ScreenFormats::_1600_900(),
		false, false
	);
	Render* render = new Render(debug);

	engine->Create(
		graph,
		window,
		render,
		new Camera(debug)
	);

	//?================================================[SCRIPTS]===============================================
	TextureManager* texManager = render->GetTextureManager();
	ModelManager* modManager = render->GetModelManager();
	MaterialManager* matManager = render->GetMaterialManager();

	render->SetSkybox(texManager->LoadSkybox("Skyboxes\\Winter", Image::Type::JPG));

	engine->GetCompiler()->AddScript(new Script("script"));
	//?================================================[SCRIPTS]===============================================

	//render->AddUI(new UIWindow(win, "Console", -2.15f, -0.2f, 1.0f, 0.5f, true));

	engine->Init();

	//?==================================================[GUI]=================================================

	Canvas* canvas = window->GetCanvas();
	
	/*
	GUIObject* main_object = new GUIObject(canvas);
	GUIObject* top_object = new GUIObject(canvas);

	Texture* gui_up = texManager->LoadTexture("GUI/GUI UP.png");
	Texture* gui_rt = texManager->LoadTexture("GUI/GUI RIGHT SMALL.png");

	main_object->SetTexture(gui_up);
	main_object->SetOrientationH(GUI::OrientationH::LEFT);
	main_object->SetScale(0.125, 1);
	main_object->SetColor(0.7, 0.7, 0.7,0.8);
	//main_object->SetPosition({ 0.75, 0 });

	top_object->SetTexture(gui_up);
	top_object->SetOrientationV(GUI::OrientationV::UP);
	top_object->SetOrientationH(GUI::OrientationH::LEFT);
	top_object->SetScale(0.125, 0.02);
	top_object->SetColor(0.6,0.6,0.6,0.8);
	//top_object->SetPosition()

	canvas->AddGUIObject(top_object);
	canvas->AddGUIObject(main_object);
	*/

	GUIList* list = new GUIList(
		canvas, "Hierarchy", 
		{ 0, 0 }, { 0.125, 1 }, {1,1,1,1},
		OrientationH::LEFT, OrientationV::CENTER
	);

	canvas->AddGUIList(list);

	GUIList* list2 = new GUIList(
		canvas, "Hierarchy2",
		{ 0, 0 }, { 0.2, 1 }, { 1,1,1,1 },
		OrientationH::RIGHT, OrientationV::CENTER
	);

	canvas->AddGUIList(list2);

	//GUIObject* obj = new GUIObject(canvas, OrientationH::CENTER, OrientationV::DOWN, {}, { 1,0.5 }, {1,1,1,1});
	//canvas->AddGUIObject(obj);


	//?==================================================[GUI]=================================================

	engine->Run();

	delete engine;
	delete debug;

	return 0;
}

/*
std::thread task = std::thread([cube, render]() {
	float pos = 0.f;
	while (true)
		if (Input::GetKey(KeyCode::T)) {
			if (Random::Bool(true))
				pos -= 0.00001f;
			else
				pos += 0.00001f;
			cube->SetPosition({ 0, 0, pos });
		}
	});

	task.detach();
*/

//model2->Destroy(); 
//model4->Destroy();
//model6->Destroy();
//std::cout << render->RemoveModel(model5);
//std::cout << render->RemoveModel(model2);
//std::cout << render->RemoveModel(model6);
//std::cout << render->RemoveModel(model3);

	/*
	//object->SetPosition({ 0.5, 0.5, 0});
	//GUIText* guiText = new GUIText(canvas);

	auto math = [](float size) -> float {
		if (size > 0)
			return (-1.0 / size) + 1.0;
		else if (size < 0)
			return (-1.0 / size) - 1.0;
		else
			return 0;
	};

	//float size = 0.125;
	//float pos = math(size);
	//object->SetGlobalScale({ size, 1 });
	//object->SetPosition({ pos, 0 });
	*/

	/*
	if(false)
	{	// SetSize Left
		float size = 1;
		float pos = (-1.0 / size) + 1.0;//pow(size, -0.5 - 1);

		object->SetGlobalScale({ size, 1 });
		object->SetPosition({ pos, 0 });
	}
	if (false)
	{	// SetSize Right
		float size = 0.5;
		float pos = (1.0 / size) - 1.0;

		object->SetGlobalScale({ size, 1 });
		object->SetPosition({ pos, 0 });
	}
	*/
	//object->SetGlobalScale({ 0.5, 1 });
	//object->SetPosition({ -1, 0 });

	//object->SetGlobalScale({ 0.25, 1 });
	//object->SetPosition({ -3, 0 });

	//object->SetGlobalScale({ 0.125, 1 });
	//object->SetPosition({ -7, 0 });

	//canvas->AddGUIText(guiText);