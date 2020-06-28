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
			Vector2d* mouse_pos;
		public:
			void Draw() override;
		public:
			UIWindow(
				std::string name,
				float x_pos, float y_pos, Window* win,
				float x_size = 1.f, float y_size = 1.f);
			~UIWindow() {
				if (this->name) delete this->name;
				win = NULL;
			}
		};
	}
}

