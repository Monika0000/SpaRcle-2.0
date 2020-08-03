#include "pch.h"
#include "UIButton.h"

namespace SpaRcle {
	namespace Graphics {
		void UIButton::Draw(vec2b mouse_left, vec2d mouse_pos) {
			float x_pos_correct = XPosCorrect();

			{glColor4f(0.2, 0.2, 0.2, 0.8f);
			glRectf(
				x_pos_correct, y_pos,
				x_pos_correct + x_size, y_pos + y_size
			);
			glBegin(GL_LINE_LOOP);
			glColor3f(0.f, 0.f, 0.f);
			glVertex2f(x_size + x_pos_correct, y_pos);
			glVertex2f(x_pos_correct, y_pos);
			glVertex2f(x_pos_correct, y_size + y_pos);
			glVertex2f(x_size + x_pos_correct, y_size + y_pos);
			glEnd(); }
		}
	}
}