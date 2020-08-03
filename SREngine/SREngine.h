#pragma once
#include <SRHelper.h>
#include <SRGraphics.h>
#include "World.h"
#include <UIList.h>
#include "Script.h"
#include "Compiler.h"
#include <UIButton.h>

namespace SpaRcle {
	using namespace Graphics;
	namespace Engine {
		using namespace Scripting;
		class SREngine {
			enum class ToolMode {
				None, Locate, Rotate, Scale
			}; // Locate, Rotate, 
			enum class PrefabLoadingState {
				None, Materials, Models, Scripts
			};
			const float ToolSpeed = 0.005f;
		private:
			bool isCreate = false;
			bool isInit   = false;
			bool isRun    = false;
		private:
			GameObject* Arrows = nullptr;
			GameObject* Rings  = nullptr;

			UIList* Hierarchy  = nullptr;

			bool toolsEnabled  = false;
			ToolMode tool	   = ToolMode::Locate;

			vec2d mouse_pos    = { 0, 0 };

			Model* TempSelectedModel	   = nullptr;
			GameObject* SelectedGameObject = nullptr;
		private:
			Debug* debug       = nullptr;
			SRGraphics* graph  = nullptr;
			Window* window     = nullptr;
			World* world       = nullptr;
			Compiler* compiler = nullptr;
		public:
			bool Create(SRGraphics* graph, Window* win, Render* render, Camera* camera);
			bool Init();
			bool Run();
			bool Close();
		public:
			void DisableTools() {
				Arrows->SetActive(false);
				Rings->SetActive(false);
			}
			World* CreateWorld(std::string name) {
				World* world = new World(debug, graph->GetRender(), Arrows);

				return world;
			}
			void SetToolMode(ToolMode tool);
			void SetWorld(World* world) { this->world = world; }
			World* LoadWorld(const std::string& name) {
				if (isCreate) {
					World* world = new World(debug, graph->GetRender(), Arrows);


					return world;
				}
				else {
					debug->Error("LoadWorld() : Loading world possible only creating engine! Name : " + name);
					Sleep(1000);
					return nullptr;
				}
			}
			World* GetCurrentWorld() {
				if (world) return world;	
				else {
					debug->Error("World is nullptr!");
					Sleep(1000);
					return nullptr;
				}
			}
			Compiler* GetCompiler() {
				if (compiler) return compiler;
				else {
					debug->Error("SREngine::GetCompiler() : compiler is nullptr!");
					Sleep(1000);
					return nullptr;
				}
			}
			std::string GetResourcesFolder() {
				if (graph) return graph->GetResourcesFolder();
				else {
					debug->Error("SREngine::GetResourcesFolder() : graph is nullptr!");
					Sleep(1000);
					return "";
				}
			}
			Debug* GetDebug() const noexcept { return debug; };
			Render* GetRender() { 
				if (!graph) {
					debug->Error("SREngine::GetRender() : graph is nullptr!");
					Sleep(2000);
					return nullptr;
				}
				return graph->GetRender(); 
			};
			//?=========================================================
			GameObject* LoadPrefab(const std::string name, bool active = true, glm::vec3 pos = {0,0,0}) {
				if (!world) {
					debug->Error("LoadPrefab : world is nullptr!");
					Sleep(1000);
					return nullptr;
				}

				if (isCreate) {
					std::string path = this->graph->GetResourcesFolder() + "\\Prefabs\\" + name + ".prefab";
					path = String::MakePath(path);

					debug->Log("Loading prefab : " + path);

					std::ifstream is(path);
					if (is.is_open()) {
						GameObject* gameObject = new GameObject(this);
						
						PrefabLoadingState state = PrefabLoadingState::None;

						std::vector<Material*> mats = std::vector<Material*>();

						std::string line = "", arg = "";
						while (!is.eof()) { std::getline(is, line);
							line = String::ReplaceAll(line, "\t", "");
							line = String::ReplaceAll(line, " ", "");

							arg = String::Remove(line, ':');

							if (arg == "Name") gameObject->name = line;
							else if (arg == "Model") {
								state = SREngine::PrefabLoadingState::Models;

								//std::cout << mats.size() << std::endl;
								Model* model = this->graph->GetRender()->GetModelManager()->LoadModelFromObj(line.c_str(), mats, pos);
								if (!model) {
									debug->Error("Failed loading prefab : " + path + "\n\tReason : Model is nullptr! Model : " + line);
									Sleep(1000);
									is.close();
									return nullptr;
								}
								//std::cout << model << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;
								//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
								model->SetPosition(pos);
								gameObject->SetModel(model);
							}
							else if (arg == "Materials") { state = SREngine::PrefabLoadingState::Materials; continue; }

							switch (state) {
								case SREngine::PrefabLoadingState::Materials:{
									Material* material = this->graph->GetRender()->GetMaterialManager()->LoadMaterial(arg.c_str());
									if (!material) {
										mats.push_back(graph->GetRender()->GetDefMat());
										//debug->Error("Failed loading prefab : " + path + "\n\tReason : Material is nullptr! Material : " + arg);
										//Sleep(1000);
										//is.close();
										//return nullptr;
									} else mats.push_back(material);
									break;
								}
								case SREngine::PrefabLoadingState::Models: {
									if (arg == "CanSelect")
										if (line == "false") if (gameObject->model) gameObject->model->CanSelect = false;
										//std::cout << line << std::endl;
									break;
								}
								default:
									break;
							}
						}

						is.close();

						world->RegisterGameObject(gameObject);
						return gameObject;
					} else {
						debug->Error("Failed loading prefab : " + path);
						Sleep(5000);
						is.close();
						return nullptr;
					}
				}
				else {
					debug->Error("LoadPrefab() : Loading prefab possible only creating engine! Name : " + name);
					Sleep(1000);
					return nullptr;
				}
			}
		public:
			SREngine(Debug* debug);
			~SREngine();
		};
	}
}