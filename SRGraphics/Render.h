#pragma once
#include <vector>
#include <string>
#include <SRHelper.h>
#include "Model.h"
//#include "UIString.h"
//#include "UIWindow.h"
#include "Texture.h"
#include "Shader.h"
#include "RayTracing.h"
#include "Terrain.h"
#include "FbxLoader.h"
#include "Material.h"

namespace SpaRcle {
	namespace Graphics {
		class SRGraphics;

		class Render {
		public:
			inline static const GLuint defaultFBO = 0;
			inline static const GLuint silhouetteFBO = 1;
		public:
			Render(Debug* debug);
			~Render() { }
		private:
			bool EditorMode = false;
		private:
			bool isCreate = false;
			bool isInit = false;
			bool isRun = false;
			bool useOldSlowRender = false;
		public:
			bool Create(Camera* camera, SRGraphics* graph);
			bool Init();
			bool Run();
			// [Call only into window context]
			void Close();
		private: //! ====== [Resources sector] ======
			//?=====================================
			std::vector<Model*> models		  = std::vector<Model*>();
			std::vector<Mesh*>  aiming_meshes = std::vector<Mesh*> ();
			//std::vector<UI*>    _ui_objects	  = std::vector<UI*>   ();

			Terrain* terrain			= nullptr;

			size_t count_models			= 0;
			size_t count_aiming_meshes	= 0;
			Material* def_mat			= nullptr;
			Skybox* skybox				= nullptr;
			RayTracing* raytracing		= nullptr;
			//?=====================================
		private:
			bool fog = false;
			//bool clear;
			//bool render;
			GLuint fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };	 // Хранит три типа тумана
			GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };	// Цвет тумана
			GLuint FBO = 0; //Frame  buffer
			GLuint RBO = 0; //Render buffer
			GLuint quadVAO = 0, quadVBO = 0;
			GLuint ScreenTexture = 0;
		public:
			void DrawSelectorObjects();
			void DrawAimingObjects();

			void DrawAllObjects();
			//void DrawAllUI();

			void SetSkybox(Skybox* skybox) { this->skybox = skybox; }

			//bool RemoveModel(Model* model);
			void AddModel(Model* model);
			void AddAimingMesh(Mesh* mesh); 
			bool RemoveAimingMesh(Mesh* mesh);
			//void AddUI(UI* ui);

			Mesh* GetAimingMesh();
			Model* GetSelectedModel();

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

			void Resize(int w, int h) {
				if (!FBO) {
					glGenFramebuffers(1, &FBO);
					debug->Graph("Render::Resize() : frame buffer object has been created. Index : " + std::to_string(FBO));
				}

				if (!ScreenTexture) {
					glGenTextures(1, &ScreenTexture);
					debug->Graph("Render::Resize() : screen texture has been created. Index : " + std::to_string(ScreenTexture));
				}
				glBindTexture(GL_TEXTURE_2D, ScreenTexture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glBindTexture(GL_TEXTURE_2D, 0);
				
				if (ScreenTexture && FBO) {
					glBindFramebuffer(GL_FRAMEBUFFER, FBO);
					// присоедиение текстуры к объекту текущего кадрового буфера
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ScreenTexture, 0);
				}
				else {
					debug->Error("Render::Resize() : screen texture or FBO is not created!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					return;
				}

				if (!RBO) {
					glGenRenderbuffers(1, &RBO);
					debug->Graph("Render::Resize() : render buffer object has been created. Index : " + std::to_string(RBO));
				}

				glBindRenderbuffer(GL_RENDERBUFFER, RBO);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);

				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
				
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
					debug->Error("Render::Resize() : Framebuffer is not complete!\n\tWidth = "+
						std::to_string(w) + "\n\tHeight = " + std::to_string(h) + "\n\tScreenTexture = " + std::to_string(ScreenTexture) +
						"\n\tFBO = " + std::to_string(FBO) + "\n\tRBO = " + std::to_string(RBO));

					EventsManager::PushEvent(EventsManager::Events::Error);
				}

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			Model* GetModel(size_t index) { return this->models[index]; }
			Material* GetDefMat() {
				if (!this->def_mat) {
					debug->Error("Default material is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->def_mat;
			}
			Shader* GetGeometryShader() {
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
			size_t GetCountModels() { return this->count_models; }
			RayTracing* GetRayTracing() {
				if (!this->raytracing) {
					debug->Error("Render::GetRayTracing() : raytracing is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->raytracing;
			}

			SRGraphics* GetGraphicsEngine() {
				if (!this->graph) {
					debug->Error("Render::GetGraphicsEngine() : graph is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->graph;
			}
			FbxLoader* GetFbxLoader() {
				if (!this->fbxLoader) {
					debug->Error("Render::GetFbxLoader() : fbxLoader is nullptr!");
					Sleep(1000);
					return nullptr;
				}
				else return this->fbxLoader;
			}
		private:
			SRGraphics* graph			= nullptr;
			Window* win					= nullptr;
			Camera* camera				= nullptr;

			Shader* shader				= nullptr;
			Shader* skyboxShader		= nullptr;
			Shader* selectorShader		= nullptr;
			Shader* Stencil				= nullptr;
			Shader* PostProcessing		= nullptr;

			Debug* debug		        = nullptr;

			TextureManager*  texManager	= nullptr;
			ModelManager*    modManager	= nullptr;
			MaterialManager* matManager = nullptr;
			FbxLoader*       fbxLoader  = nullptr;
		};
	}
}

