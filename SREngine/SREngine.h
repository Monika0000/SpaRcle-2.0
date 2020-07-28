#pragma once
#include <SRHelper.h>
#include <SRGraphics.h>
#include "World.h"
#include <UIList.h>
#include "Script.h"
#include "Compiler.h"

namespace SpaRcle {
	using namespace Graphics;
	namespace Engine {
		using namespace Scripting;
		class SREngine {
			enum class PrefabLoadingState {
				None, Materials, Models, Scripts
			};
		private:
			bool isCreate = false;
			bool isInit   = false;
			bool isRun    = false;
		private:
			GameObject* Arrows = nullptr;
			GameObject* Rings  = nullptr;

			UIList* Hierarchy  = nullptr;
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
			//?=========================================================
			GameObject* LoadPrefab(const std::string name, bool active = true) {
				if (isCreate) {
					std::string path = this->graph->GetResourcesFolder() + "//Prefabs//" + name + ".prefab";
					path = String::MakePath(path);

					debug->Log("Loading prefab : " + path);

					std::ifstream is(path);
					if (is.is_open()) {
						GameObject* gameObject = new GameObject(graph->GetRender());
						
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
								Model* model = this->graph->GetRender()->GetModelManager()->LoadModelFromObj(line.c_str(), mats);
								if (!model) {
									debug->Error("Failed loading prefab : " + path + "\n\tReason : Model is nullptr! Model : " + line);
									Sleep(1000);
									is.close();
									return nullptr;
								}
								
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

						return gameObject;
					} else {
						debug->Error("Failed loading prefab : " + path);
						Sleep(1000);
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