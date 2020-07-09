#pragma once
#include <vector>
#include <string>
#include <SRHelper.h>
#include "Model.h"
#include "UIString.h"
#include "UIWindow.h"
#include "Texture.h"
#include "Shader.h"
#include "RayTracing.h"

namespace SpaRcle {
	namespace Graphics {
		class SRGraphics;

		class Render {
		public:
			Render(Debug* debug);
			~Render() { }
		private:
			bool isCreate = false;
			bool isInit = false;
			bool isRun = false;
			bool useOldSlowRender = false;
		public:
			bool Create(Camera* camera, SRGraphics* graph);
			bool Init();
			bool Run();
			void Close();
		private: //! ====== [Resources sector] ======
			//?=====================================
			std::vector<Model*> models = std::vector<Model*>();
			std::vector<Model*> deleteModels = std::vector<Model*>();

			size_t count_models;
			Material* def_mat = nullptr;
			Skybox* skybox = nullptr;
			RayTracing* raytracing = nullptr;
			//?=====================================
		private:
			bool fog;
			bool clear;
			bool render;
			GLuint fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };	 // Хранит три типа тумана
			GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };	// Цвет тумана
		public:
			void DrawAllObjects();
			void DrawAllUI();

			void SetSkybox(Skybox* skybox) { this->skybox = skybox; }

			//bool RemoveModel(Model* model);
			void AddModel(Model* model);
			void AddUI(UI* ui);

			void InitFog() {
				//! ========== FOG ==========
				glEnable(GL_FOG);										// Включает туман (GL_FOG)
				glFogi(GL_FOG_MODE, fogMode[2]);					// Выбираем тип тумана
				glFogfv(GL_FOG_COLOR, fogColor);					 // Устанавливаем цвет тумана
				glFogf(GL_FOG_DENSITY, 0.35f);						 // Насколько густым будет туман
				glHint(GL_FOG_HINT, GL_DONT_CARE);					// Вспомогательная установка тумана
				glFogf(GL_FOG_START, 10.0f);							 // Глубина, с которой начинается туман
				glFogf(GL_FOG_END, 50.0f);							// Глубина, где туман заканчивается.
				//! ========== FOG ==========
			}
			void SetFog(bool val) { this->fog = val; }
			bool GetFog() { return this->fog; }

			Material* GetDefMat() {
				if (!this->def_mat) {
					debug->Error("Default material is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->def_mat;
			}
			Shader* GetShader() {
				if (!this->shader) {
					debug->Error("Shader is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->shader;
			}
			ModelManager* GetModelManager() {
				if (!this->modManager) {
					debug->Error("Model manager is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->modManager;
			}
			TextureManager* GetTextureManager() {
				if (!this->texManager) {
					debug->Error("Texture manager is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->texManager;
			}
			MaterialManager* GetMaterialManager() {
				if (!this->matManager) {
					debug->Error("Material manager is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->matManager;
			}

			void Clear() {
			ret: if (render) goto ret;
				clear = true;
				//for (Object3D* obj : this->_3d_objects)
				//	if (obj) delete obj;
				//_3d_objects.clear();
				clear = false;
			}
		private:
			SRGraphics* graph = nullptr;
			Camera* camera = nullptr;
			Shader* shader = nullptr;
			Shader* skyboxShader = nullptr;
			Debug* debug = nullptr;

			TextureManager* texManager = nullptr;
			ModelManager* modManager = nullptr;
			MaterialManager* matManager = nullptr;
		private:
			std::vector<UI*> _ui_objects;
		};
	}
}

