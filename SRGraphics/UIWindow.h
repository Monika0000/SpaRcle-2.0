#pragma once
#include "UI.h"
#include "UIString.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Window;
		class UIWindow : public UI {
		private:
			UIString* name = nullptr;
			Window* win = nullptr;
			bool isMove = false;
			bool CanMove = true;
			Vector2d* mouse_pos = nullptr;
		public:
			void Draw(bool mouse_left_down, bool mouse_left_up) override;
			virtual void DrawElements() {  };
		public:
			UIWindow(
				std::string name,
				float x_pos, float y_pos, Window* win,
				float x_size = 1.f, float y_size = 1.f, bool CanMove = true);
			~UIWindow() {
				if (this->name) delete this->name;
				win = NULL;
			}
		};
	}
}

