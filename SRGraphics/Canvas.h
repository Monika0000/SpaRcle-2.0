#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "GUIBase.h"
#include "GUIText.h"
#include "GUIObject.h"
#include "GUIList.h"
#include "GUIButton.h"

namespace SpaRcle {
	namespace Helper {
		class Debug;
	}
	namespace Graphics {
		using namespace Helper;

		class Window;
		class Shader;
		class ColorBuffer;
		namespace GUI {
			class Canvas {
			private:
				std::vector<GUIText*>	m_texts		= std::vector<GUIText*>();
				std::vector<GUIObject*> m_objects	= std::vector<GUIObject*>();
				std::vector<GUIList*>   m_lists		= std::vector<GUIList*>();
				std::vector<GUIButton*> m_buttons	= std::vector<GUIButton*>();
			private:
				size_t t							= 0;
				Window* window						= nullptr;
				Debug* debug						= nullptr;
				ColorBuffer* cBuff					= nullptr;
				bool isInit							= false;
				bool isRelease						= false;
				Shader* shader						= nullptr;
			public:
				float size_up						= 1;
				float size_down						= 1;
				float size_left						= 1;
				float size_right					= 1;
			public:
				Canvas(Window* window);
				~Canvas();
				// [Call only from window init in glfw context!]
				bool Init(); 
				bool Release();
			public:
				Shader* GetShader() { return this->shader; }
				Texture* LoadTexture(std::string name);
				void UseShader();
				bool GetEditorMode();

				bool AddGUIText		(GUIText* text)		{ this->m_texts.push_back(text); return true;		};
				bool AddGUIObject	(GUIObject* obj)	{ this->m_objects.push_back(obj); return true;		};
				bool AddGUIList		(GUIList* list)		{ this->m_lists.push_back(list); return true;		};
				bool AddGUIButton	(GUIButton* bttn)	{ this->m_buttons.push_back(bttn); return true;		};
			public:
				bool PoolEvents();
				bool Draw();
				template <typename T> void DrawGUI(std::vector<T> gui) {
					for (t = 0; t < gui.size(); t++) {
						if (gui[t]->isDestroy) {
							delete gui[t];
							gui.erase(gui.begin() + t);
							break;
						}
						else gui[t]->Draw();
					}
				}
			};
		}
	}
}

