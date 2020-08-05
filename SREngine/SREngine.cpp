#include "pch.h"
#include "SREngine.h"
#include "Window.h"
#include <Shlobj_core.h> 
#include <UIList.h>

namespace SpaRcle {
	using namespace Graphics;
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

				if (!world) SetWorld(CreateWorld("New world"));

				Arrows = LoadPrefab("Engine//Arrows"); //Arrows->model->DepthTesting = false;
				Rings  = LoadPrefab("Engine//Rings");  //Rings->model->DepthTesting  = false;
				SetToolMode(ToolMode::None);

				//!====================================================================================================
				this->Hierarchy = new UIList<GameObject*>(win, "Hierarchy", -2.2075f, -0.25f, 0.60f, 2.45f);
				Hierarchy->SetList(world->gameObjects);
				//std::next(world->gameObjects.begin(), 1)->second;
				Hierarchy->SetEvent_GetName([](GameObject* gm) -> std::string { return gm->name; });

				render->AddUI(this->Hierarchy);
				//!====================================================================================================

				return true;
			} else return false;
		}
		bool SREngine::Init() {
			if (isCreate) {
				debug->Info("Initializing engine...");

				this->graph->Init();
				this->window = graph->GetWindow();

				this->compiler->Compile();

				//for (Mesh* mesh : Arrows->GetComponent<Model*>()->meshes) {
				//	this->window->GetRender()->AddAimingMesh(mesh);
				//}
				SetToolMode(ToolMode::Locate); DisableTools();

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

			float num_fps_limit = 120.f;
			float fps_limit_timer = 0.f;
			float fps_lim = 1 / num_fps_limit;
			float frameDeltaTime;
			int now = 0, then = 0;

			float frame = 0;

			debug->System("All systems are running successfully!");

			for (auto script : compiler->scripts)
				if (script->IsCompile())
					script->Start();

			while (true) {
				if (EventsManager::PopEvent(EventsManager::Events::Exit)
					|| EventsManager::PopEvent(EventsManager::Events::Error)) {
					debug->System("Exit or error message has been recived!");
					break;
				}

				if (Input::FixedGetKeyDown(KeyCode::Esc)) {
					debug->System("Escape key has been pressed!");
					break;
				}
				if (Input::FixedGetKeyDown(KeyCode::M))
					std::cout << ("Current memory load is " + std::to_string(Utils::GetCurrentMemoryLoad() / 1024) + "Kb\n");
				if (Input::FixedGetKeyDown(KeyCode::L))
					this->window->MouseLock(!this->window->MouseLock());
				else if (Input::FixedGetKeyDown(KeyCode::O)) {
					/*
					OPENFILENAME l = { sizeof(l), };
					TCHAR buf[1024];

					HWND hwnd = ::CreateWindowA("STATIC", "explore", WS_VISIBLE, 0, 0, 100, 100, NULL, NULL, NULL, NULL);
					l.hwndOwner = hwnd;
					//l.lpstrFilter = L"ZIP Files\0*.zip\0All Files\0*.*\0";
					l.lpstrFilter = L"*.*\0";
					l.lpstrFile = buf;
					l.nMaxFile = 1023;
					l.lpstrTitle =L"Open resource";
					//l.lpstrDefExt = L"zip";
					l.lpstrInitialDir = String::CharsToLPWSTR(graph->GetResourcesFolder().c_str());
					l.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST;
					buf[0] = 0;
					if (GetOpenFileName(&l)) {

					}
					*/
				}
				//?========================================================

				now = clock();
				frameDeltaTime = (float)(now - then) / 1000.f;
				fps_limit_timer += frameDeltaTime;

				if (fps_limit_timer >= fps_lim) {
					fps_limit_timer = 0.0f;

					for (auto script : compiler->scripts)
						if (!script->HasErrors() && script->IsCompile())
							if (!script->Update(frame)) {
								//debug->ScriptError("Engine::Run() : An exception has been occured!\n\tFile script : " + script->GetName());
								//Sleep(500);
							}
					frame += 0.001;
					if (frame == 1) frame = 0;

					if (graph->EditorMode) {
						Model* model = window->GetSelectedModel();
						if (model) {						
							vec2d mouse = window->GetMousePos();


							bool left = Input::GetKey(KeyCode::MouseLeft);

							if (TempSelectedModel != model) {
								TempSelectedModel = model;
								SelectedGameObject = world->Find(model);
							}

							if (!toolsEnabled) SetToolMode(tool);

							float dist = window->GetCamera()->Distance(Arrows->transform.position);
							if (dist < 10) dist = 10; else if (dist > 500) dist = 500;
							switch (tool) {
							case SpaRcle::Engine::SREngine::ToolMode::Locate:
								Arrows->transform.SetScale(
									dist / 50.f,
									dist / 50.f,
									dist / 50.f);
								Arrows->transform.SetPosition(model->GetPosition());
								break;
							}

							if (!this->window->MouseLock() && left) {
								POINT p; auto size = window->GetScreenSize();
								GetCursorPos(&p);
								if (p.x >= size->x - 1) { SetCursorPos(0, p.y); mouse = mouse_pos = window->GetMousePos(); }
								else if (p.x <= 0) { SetCursorPos(size->x - 1, p.y); mouse = mouse_pos = window->GetMousePos(); }
								else 
								if (p.y >= size->y - 1) { SetCursorPos(p.x, 0); mouse = mouse_pos = window->GetMousePos(); }
								else if (p.y <= 0) { SetCursorPos(p.x, size->y - 1); mouse = mouse_pos = window->GetMousePos(); }

								Mesh* mesh = window->GetAimedMesh();
								if (mesh) {
									float dx = mouse.x - mouse_pos.x;
									float dy = mouse.y - mouse_pos.y;

									glm::vec3 dir = { 0,0,0 };

									switch (tool) {
									case SpaRcle::Engine::SREngine::ToolMode::Locate: {
										int id = Arrows->model->GetMeshIndex(mesh);
										if (!mesh) break;
										switch (id) {
											case 0: dir = { 0, -dy, 0 }; break;
											case 1: 
												dir = glm::vec3 { 
													(window->GetCamera()->dXYZ().x * dy) - (window->GetCamera()->dXYZ().z * dx), 0, 0 };
												break;
											case 2: 
												dir = { 0,0,
													-(window->GetCamera()->dXYZ().x * dx) - (window->GetCamera()->dXYZ().z * dy) };
												break;
											default: break;
										}
										break;
									}
									case SpaRcle::Engine::SREngine::ToolMode::Rotate:
										break;
									case SpaRcle::Engine::SREngine::ToolMode::Scale:
										break;
									default: break;
									}

									//dir *= 6.f;
									dir *= dist / 2.5f;
									

									Arrows->transform.Move(dir);
									SelectedGameObject->Move(dir);
								}
							}

							this->mouse_pos = mouse;
						}
						else
						{
							DisableTools();
						}
					}

					then = now;
				}
				//!========================================================
				/*
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
				*/
				//if (Input::FixedGetKeyDown(KeyCode::C)) {
				//	this->graph->GetRender()->Clear();
				//}
				
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
		void SREngine::SetToolMode(ToolMode tool) {
			switch (tool)
			{
			case SpaRcle::Engine::SREngine::ToolMode::None:
				Rings->SetActive(false);
				Arrows->SetActive(false);
				break;
			case SpaRcle::Engine::SREngine::ToolMode::Locate:
				Rings->SetActive(false);
				Arrows->SetActive(true);
				break;
			case SpaRcle::Engine::SREngine::ToolMode::Rotate:
				Rings->SetActive(true);
				Arrows->SetActive(false);
				break;
			case SpaRcle::Engine::SREngine::ToolMode::Scale:
				break;
			default:
				break;
			}
		}
	}
}