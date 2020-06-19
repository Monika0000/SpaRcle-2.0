#pragma once
#include "UI.h"
#include "UIString.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Window;
		class UIWindow : public UI {
		private:
			UIString* name;
			Window* win;
			bool isMove;
		public:
			void Draw() override;
		public:
			UIWindow(
				std::string name,
				float x_pos, float y_pos, Window* win, 
				float x_size = 1.f, float y_size = 1.f) : UI(x_pos, y_pos, x_size, y_size)
			{
				this->isMove = false;
				this->name = new UIString(name, 0.5, 0.5);
				this->win = win;
			};
			~UIWindow() {
				if (this->name) delete this->name;
				win = NULL;
			}
		};
	}
}

