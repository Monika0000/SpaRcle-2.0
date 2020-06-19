#include "pch.h"
#include "UIWindow.h"
#include "Window.h"

namespace SpaRcle {
	namespace Graphics {
		void UIWindow::Draw() {
			static float x_pos = 0.f;
			static float y_pos = 0.f;
			static float x_size = 1.5f;
			static float y_size = 1.5f;

			static float mouse_x = 0.f;
			static float mouse_y = 0.f;

			Vector2d* vec = win->GetMousePosition();

			float x = (x_pos + win->format->x_side_magic_number) / win->format->x_side_magic_number / 2.f;
			float y = -(y_pos - (win->format->y_side_magic_number - (y_size - 1.f))) / 2.5f; // -2.49f
			
			//(y_pos - 1.21f) / -2.49f; - if x == 1
			//(y_pos - 0.21f) / -2.49f; - if x == 2

			//min = 0.71 //(y_pos - 0.71)
			//min = -1.78
			// -2.49		
				//1.f - (y_pos + win->format->y_side_magic_number) / win->format->y_side_magic_number / 2.f - 0.01333 * y_size;// -0.202 - 0.011442f;
				 // 1.f - (y_pos + win->format->y_side_magic_number) / win->format->y_side_magic_number / 2.f;

			/* Y-MOUSE
				y_size = 1 => y = 0.415
				y_size = 2 => y = 0.815
			*/

			//std::cout << "y = " << y << "; vec_y = " << vec->y << "\t" << "x = " << x << "; vec_x = " << vec->x << std::endl;
			//std::cout << "vec_y = " << vec->y << " " << << std::endl;

			//std::cout << x_pos << " " << vec->x << std::endl;
			if (vec->x > x && vec->x < x + win->format->x_mouse_magic_number * x_size
				&& vec->y > y && vec->y < y + win->format->y_mouse_magic_number * y_size + 0.03) {
					if (Input::GetKeyDown(KeyCode::MouseLeft))
						isMove = true;
			}

			if (isMove) {
				Vector2d* position = win->GetMousePosition();
				float _x_ = mouse_x - position->x;
				float _y_ = mouse_y - position->y;
				delete position;
				//std::cout << _x_ << std::endl;
				x_pos -= _x_ * 5.f;
				y_pos += _y_ * 2.5f;
			}

			if (Input::GetKeyUp(KeyCode::MouseLeft))
				isMove = false;

			mouse_x = vec->x;
			mouse_y = vec->y;
			delete vec;

			if (Input::GetKey(KeyCode::LeftArrow))		 x_pos -= 0.01f;
			else if (Input::GetKey(KeyCode::RightArrow)) x_pos += 0.01f;

			if (Input::GetKey(KeyCode::UpArrow))		 y_pos += 0.01f;
			else if (Input::GetKey(KeyCode::DownArrow))  y_pos -= 0.01f;

			{glColor4f(0.2, 0.2, 0.2, 0.8f);
				glRectf(
					x_pos,		    y_pos,
					x_pos + x_size, y_pos + y_size
				);
			glBegin(GL_LINE_LOOP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2f(x_size + x_pos, y_pos);
				glVertex2f(x_pos,		   y_pos);
				glVertex2f(x_pos,		   y_size + y_pos);
				glVertex2f(x_size + x_pos, y_size + y_pos);
			glEnd();}

			//!--------------------------------------------------

			{glColor4f(0.3f, 0.0f, 0.3f, 0.9f);
				glRectf(
					x_pos,			y_pos + y_size,
					x_pos + x_size, y_pos + y_size + 0.03f // Семщение вверх
				);
			glBegin(GL_LINE_LOOP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2f(x_size + x_pos,  y_pos + y_size);
				glVertex2f(x_pos,		    y_pos + y_size);
				glVertex2f(x_pos,		    y_pos + y_size + 0.03f);
				glVertex2f(x_size + x_pos,  y_pos + y_size + 0.03f);
			glEnd();}

			name->Draw();
		}
	}
}