#pragma once
#include "UI.h"

namespace SpaRcle {
	namespace Graphics {
		class UIButton : public UI {
			UIButton(float x_pos, float y_pos, float x_size, float y_size) : UI(x_pos, y_pos, x_size, y_size) {

			}

			void Draw(vec2b mouse_left, vec2d mouse_pos) override {

			}
		};
	}
}