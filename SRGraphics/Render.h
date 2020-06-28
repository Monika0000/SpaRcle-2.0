#pragma once
#include <vector>
#include <string>
#include <SRHelper.h>
#include "Model.h"
#include "UIString.h"
#include "UIWindow.h"
#include "Texture.h"

namespace SpaRcle {
	namespace Graphics {
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
			bool Create();
			bool Init();
			bool Run();
			void Close();
		private: //! ====== [Meshes sector] ======
			//?=====================================
			std::vector<Mesh*> meshes;
			size_t count_meshes;
			//?=====================================
		private:
			bool clear;
			bool render;
			GLuint fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };	 // Хранит три типа тумана
			GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };	// Цвет тумана
		public:
			void DrawAllObjects();
			void DrawAllUI();

			void AddModel(Mesh* model);
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

			TextureManager* GetTextureManager() {
				if (!this->texManager) {
					debug->Error("Texture manager is nullptr!");
					Sleep(1000);
					return nullptr;
				} else return this->texManager;
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
			bool fog;
		private:
			Debug* debug;
			TextureManager* texManager;
		private:
			std::vector<UI*> _ui_objects;
		};
	}
}

