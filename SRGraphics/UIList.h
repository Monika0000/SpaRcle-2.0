#pragma once
#include "UIWindow.h"

namespace SpaRcle {
	namespace Graphics {
		class UIList : public UIWindow {
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

			};

			void DrawElements() override {

			}
		};
	}
}