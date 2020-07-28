#include "pch.h"
#include "SREngine.h"
#include "Window.h"

namespace SpaRcle {
	namespace Engine {
		SREngine::SREngine(Debug* debug) {
			this->debug = debug;
			this->graph = NULL;
			this->window = NULL;
			this->isCreate = false;
			this->isInit = false;
			this->isRun = false;
		}
		SREngine::~SREngine() {
			Close();
		}
		bool SREngine::Create(SRGraphics* graph, Window*win, Render* render, Camera* camera) {
			if (!isCreate) {
				debug->Info("Creating engine...");

				this->graph = graph;

				graph->Create(
					win, 
					render,
					camera
				);

				this->compiler = new Compiler(this, debug);

				isCreate = true;

				Arrows = LoadPrefab("Engine//Arrows");
				Rings  = LoadPrefab("Engine//Rings");
				//Arrows->transform.SetRotation({ 45, 0, 0 });
				//Arrows->SetActive(false);
				Rings->SetActive(false);

				this->Hierarchy = new UIList("Hierarchy", -2.21f, -0.25f, win, 0.60f, 2.45f);
				render->AddUI(this->Hierarchy);

				return true;
			} else return false;
		}
		bool SREngine::Init() {
			if (isCreate) {
				debug->Info("Initializing engine...");

				this->graph->Init();
				this->window = graph->GetWindow();

				this->compiler->Compile();

				isInit = true;
				return true;
			}
			else { debug->Error("Engine is not create!"); return false; }
		}
		bool SREngine::Run() {
			debug->Info("Running engine...");

			if (!this->graph->Run()) {
				debug->Error("Failed running graphics engine!");
				return false;
			}

			//this->window->MouseLock(!this->window->MouseLock());

			//Texture* texture = graph->GetRender()->GetTextureManager()->LoadTexture((graph->GetResourcesFolder() + "\\Textures\\rock.bmp").c_str());

			debug->System("All systems are running successfully!");
			while (true) {
				//std::cout << 1 << std::endl;
				if (EventsManager::PopEvent(EventsManager::Events::Exit)
					|| EventsManager::PopEvent(EventsManager::Events::Error))
					break;

				if (Input::FixedGetKeyDown(KeyCode::Esc))
					break;
				if (Input::FixedGetKeyDown(KeyCode::M))
					std::cout << ("Current memory load is " + std::to_string(Utils::GetCurrentMemoryLoad() / 1024) + "Kb\n");
				if (Input::FixedGetKeyDown(KeyCode::L))
					this->window->MouseLock(!this->window->MouseLock());

				for (auto script : compiler->scripts)
					if(!script->HasErrors() && script->IsCompile()) 
						if (!script->Update()) {
							//debug->ScriptError("Engine::Run() : An exception has been occured!\n\tFile script : " + script->GetName());
							//Sleep(500);
						}

				//!========================================================

				if (Input::GetKey(KeyCode::R)) {
					//continue; //TODO: add texture
					int x = rand() % 100;
					int y = rand() % 100;
					int z = rand() % 100;

					#ifdef false
					Mesh* mesh = new Mesh(_3D_Models::Cube, _3D_Models::CubeUV, { (float)x, (float)y, (float)z });
					Model* model = new Model(mesh, texture);
					//std::cout << texture->id << std::endl;

					if ((unsigned long long)mesh == 0xdddddddddddddddd || (unsigned long long)model == 0xdddddddddddddddd) {
						continue;
					}

					static int count = 0;
					count++;

					debug->Log("Summon new cube in pos ("
						+ std::to_string(x) + ", "
						+ std::to_string(y) + ", "
						+ std::to_string(z) + ") total cubes = " + std::to_string(count) + "; total verts = " + std::to_string(count * 3 * 24));

					this->graph->GetRender()->AddModel(model);
					Sleep(10);
					#endif
				}

				if (Input::FixedGetKeyDown(KeyCode::C)) {
					this->graph->GetRender()->Clear();
				}
				
				if (Input::FixedGetKeyDown(KeyCode::Y)) {
					this->graph->GetRender()->SetFog(!this->graph->GetRender()->GetFog());
				}

				if (Input::GetKey(KeyCode::LeftArrow)) Arrows->transform.Rotate({ 0.1, 0, 0 });
				else if (Input::GetKey(KeyCode::RightArrow)) Arrows->transform.Rotate({ -0.1, 0, 0 });
			}

			debug->Info("Engine has been completed work!");
			return true;
		}
		bool SREngine::Close() {
			debug->Info("Close engine...");

			this->graph->Close();

			debug->System("All systems are completed successfully!");
			return true;
		}
	}
}