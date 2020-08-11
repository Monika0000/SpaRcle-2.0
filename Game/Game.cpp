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
	//std::cout << String::Remove(s, '/') << std::endl;
	//std::cout << String::Remove(s, '/') << std::endl;
	//std::cout << String::Remove(s, '/') << std::endl;

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

	Window* win = new Window(
		debug,
		NULL,
		"SpaRcle",
		new Screen_720_576(),
		new Screen_1600_900(),
		true, false
	);
	Render* render = new Render(debug);

	engine->Create(
		graph, 
		win,
		render,
		new Camera(debug)
	);

	//?========================================================================================================
	TextureManager* texManager  = render->GetTextureManager();
	ModelManager* modManager    = render->GetModelManager();
	MaterialManager* matManager = render->GetMaterialManager();

	render->SetSkybox(texManager->LoadSkybox("Skyboxes\\Winter", Image::Type::JPG));

	//Material* mat = matManager->LoadMaterial("engine\\yellow");
	//Model* model = modManager->LoadModelFromObj("engine\\lump");
	//engine->GetCurrentWorld()->Instantiate("Light demo", model);
	//GameObject* Sina		 = engine->LoadPrefab("sina");
	//Sina->transform.SetRotation(0, 270, 0);
	//Sina->transform.SetScale(0.3, 0.3, 0.3);

	//GameObject* Sphere = engine->LoadPrefab("sphere");
	//Sphere->transform.SetPosition(10, 0, 0);

	//GameObject* Sphere2 = engine->LoadPrefab("sphere");
	//Sphere2->transform.SetPosition(14, 0, 0);

	//GameObject* Sphere3 = engine->LoadPrefab("sphere");
	//Sphere3->transform.SetPosition(3, 5, -2);

	/*
	Material* player_body    = matManager->LoadMaterial("body");
	Material* brick          = matManager->LoadMaterial("brick");
	Material* rock           = matManager->LoadMaterial("rock");

	Texture* texture	     = texManager->LoadTexture("base.bmp", Texture::Type::Diffuse, Texture::Filter::NEAREST_MIPMAP_LINEAR);
	Texture* Stone			 = texManager->LoadTexture("Stone1.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* Weapon			 = texManager->LoadTexture("mccree_weapon_3d.bmp", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* AssassinBody    = texManager->LoadTexture("AssassinBody_Dif.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	//Texture* Body			 = texManager->LoadTexture("Textures\\Player\\Player_Body_diffuse.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* Hair			 = texManager->LoadTexture("Player\\Player_Hair_diffuse.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* Top			 = texManager->LoadTexture("Player\\Player_Top_diffuse.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* Bottom		     = texManager->LoadTexture("Player\\Player_Bottom_diffuse.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* Shoes   		 = texManager->LoadTexture("Player\\Player_Shoes_diffuse.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* cubeTexture     = texManager->LoadTexture("Cube_triangulate.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	Texture* plane_texture   = texManager->LoadTexture("plane.png", Texture::Type::Diffuse, Texture::Filter::LINEAR_MIPMAP_NEAREST);
	*/

	//render->GetRayTracing()->AddLight();

	engine->GetCompiler()->AddScript(new Script("script"));

	//?========================================================================================================

	render->AddUI(new UIWindow(win, "Console", -2.15f, -0.2f, 1.0f, 0.5f, true));

	engine->Init();

	//model2->Destroy(); 
	//model4->Destroy();
	//model6->Destroy();
	//std::cout << render->RemoveModel(model5);
	//std::cout << render->RemoveModel(model2);
	//std::cout << render->RemoveModel(model6);
	//std::cout << render->RemoveModel(model3);

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