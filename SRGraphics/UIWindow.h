#pragma once
#include "UI.h"
#include "UIString.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Window;
		class UIWindow : public UI {
		protected:
			float x_left = 0;
			float y_up = 0;
			float x_right = 0;
			float y_down = 0;
		private:
			UIString* name = nullptr;
			bool isMove = false;
			bool CanMove = true;
			//Vector2d* mouse_pos = nullptr;
		public:
			void Draw(vec2b mouse_left, vec2d mouse_pos) override;
			virtual void DrawElements(vec2b mouse_left, vec2d mouse_pos);
		public:
			UIWindow(
				Window* win,
				std::string name,
				float x_pos, float y_pos, 
				float x_size = 1.f, float y_size = 1.f, bool CanMove = true);
			~UIWindow() {
				if (this->name) delete this->name;
				//win = NULL;
			}
		};
	}
}

