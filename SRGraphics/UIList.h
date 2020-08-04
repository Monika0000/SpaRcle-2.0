#pragma once
#include "UIWindow.h"
#include <map>

namespace SpaRcle {
	namespace Graphics {
		template <typename T>
		class UIList : public UIWindow {
			enum class Type { none, map, vector };
		public:
			void SetList(std::vector<T>& list) { 
				this->List = &list; type = Type::vector;
			}
			void SetList(std::map<std::string, T>& list) { 
				this->Map = &list; type = Type::map;
			}
		public:
			void SetEvent_GetName(std::string(*fn)(T)) { get_name = fn; }
			//void EventLeftClick()
		private:
			std::string(*get_name)(T)	   = nullptr;
		private:
			//std::vector<UIString*> strings = std::vector<UIString*>();
			UIString* line				   = nullptr;
			Type type					   = Type::none;
			std::vector<T>* List		   = nullptr;
			std::map<std::string, T>* Map  = nullptr;
		public:
			UIList(
				Window* win, 
				std::string name,
				float x_pos, float y_pos, 
				float x_size, float y_size, 
				bool CanMove = true
			)  
				: UIWindow(win, name, x_pos, y_pos, x_size, y_size, CanMove)
			{
				this->line = new UIString(win, "[empty]", 1, 1, nullptr, 0.3);
			};
		public:
			void DrawElements(vec2b mouse_left, vec2d mouse_pos) override {
				switch (type) {
				case Type::map: {
					if (!Map) return;
					for (size_t t = 0; t < Map->size(); t++) {
						line->SetPosition(this->XPosCorrect() + 0.01, y_pos + y_size - 0.051 * (t + 1));
						//line->SetString(get_name(((*Map).begin() + t)->second));
						line->SetString(get_name(std::next(Map->begin(), t)->second));
						line->Draw({}, {});
					}
					break;
				}
				case Type::vector:
					//TODO:
					break;
				default: break;
				}
			};
		};
	}
}