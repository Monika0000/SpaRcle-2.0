#pragma once
#include "UIWindow.h"

namespace SpaRcle {
	namespace Graphics {
		class UIList : public UIWindow {
		public:
			UIList(std::string name, float x_pos, float y_pos, Window* win, float x_size, float y_size, bool CanMove = true)  
				: UIWindow(name, x_pos, y_pos, win, x_size, y_size, CanMove)
			{

			};

			void DrawElements() override {

			}
		};
	}
}