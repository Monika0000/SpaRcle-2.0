#pragma once
#include <vector>
#include <string>
#include <SRHelper.h>
#include "Object3D.h"
#include "UIString.h"
#include "UIWindow.h"
#include "Texture.h"

namespace SpaRcle {
	namespace Graphics {
		class Render {
		public:
			Render(Debug* debug);
			~Render() { Close(); }
		public:
			void Create() {
				this->texManager = new TextureManager(debug);
			}
			void Close() {
				Clear();
				for (UI* ui : this->_ui_objects)
					if (ui) delete ui;
				_ui_objects.clear();
			}
		private:
			bool clear;
			bool render;
			GLuint fogMode[3] = { GL_EXP, GL_EXP2, GL_LINEAR };	 // ������ ��� ���� ������
			GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };	// ���� ������
		public:
			void DrawAllObjects();
			void DrawAllUI();

			void AddObject3D(Object3D* obj);
			void AddUI(UI* ui);

			void InitFog() {
				//! ========== FOG ==========
				glEnable(GL_FOG);										// �������� ����� (GL_FOG)
				glFogi(GL_FOG_MODE, fogMode[2]);					// �������� ��� ������
				glFogfv(GL_FOG_COLOR, fogColor);					 // ������������� ���� ������
				glFogf(GL_FOG_DENSITY, 0.35f);						 // ��������� ������ ����� �����
				glHint(GL_FOG_HINT, GL_DONT_CARE);					// ��������������� ��������� ������
				glFogf(GL_FOG_START, 10.0f);							 // �������, � ������� ���������� �����
				glFogf(GL_FOG_END, 50.0f);							// �������, ��� ����� �������������.
				//! ========== FOG ==========
			}
			void SetFog(bool val) { this->fog = val; }
			bool GetFog() { return this->fog; }

			void Clear() {
			ret: if (render) goto ret;
				clear = true;
				for (Object3D* obj : this->_3d_objects)
					if (obj) delete obj;
				_3d_objects.clear();
				clear = false;
			}
		private:
			bool fog;
		private:
			Debug* debug;
			TextureManager* texManager;
		private:
			std::vector<Object3D*> _3d_objects;
			std::vector<UI*> _ui_objects;
		};
	}
}

