﻿#define NOMINMAX
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

	//GameObject* Sina		 = engine->LoadPrefab("sina");
	GameObject* Sphere		 = engine->LoadPrefab("sphere");
	Sphere->transform.SetPosition({ 10, 0,0 });

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

	//Mesh* cube = new Mesh(_3D_Models::CubeVertex, { 1.f, 0.f, 1.f });
	//Mesh* cube2 = new Mesh(_3D_Models::CubeVertex, { 0.f, 1.f, 1.f });
	//Model* model2 = modManager->LoadModelFromObj("sphere.obj", { rock }, { 5, 2, 5 });
	//Model* model3 = modManager->LoadModelFromObj("stone1.obj", { new Material(Stone) }, { 0, 2, 0 });
	//Model* model4 = modManager->LoadModelFromObj("plane.obj", { brick }, { 0, 2, 5 });
	//Model* model5 = modManager->LoadModelFromObj("cube_triangulate.obj", { new Material(cubeTexture) }, { 4, 2, 0 });
	//Model* model6 = modManager->LoadModelFromObj("Player2.obj", 
	//	{ player_body, player_body, player_body, new Material(Top), new Material(Hair), new Material(Bottom), new Material(Shoes) }, { 40, 2, 4 });

	//Model* model4 = modManager->LoadModelFromObj((graph->GetResourcesFolder() + "\\Models\\plane.obj").c_str(), new Material(plane_texture), { 0, 2, 5});
	//Model* model2 = modManager->LoadModelFromObj((graph->GetResourcesFolder() + "\\Models\\cube.obj").c_str(), new Material(texture), { 0, 2, 5 });
	//Model* model = new Model(cube, new Material(texture));
	//Model* model2 = new Model(cube2, new Material(texture2));

	//render->AddModel(model);
	//render->AddModel(model2);
	//render->AddModel(model3);
	//render->AddModel(model4);
	//render->AddModel(model5);
	//render->AddModel(model6);

	engine->GetCompiler()->AddScript(new Script("script"));

	//?========================================================================================================

	render->AddUI(new UIWindow("Console", -2.15f, -0.2f, win, 1.0f, 0.5f, true));

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