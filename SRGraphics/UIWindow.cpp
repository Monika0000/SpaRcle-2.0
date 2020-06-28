#include "pch.h"
#include "UIWindow.h"
#include "Window.h"

namespace SpaRcle {
	namespace Graphics {
		const float win_name_pos[2] = { 0, 0 };
		const float up_size = 0.045f;

		UIWindow::UIWindow(
			std::string name,
			float x_pos, float y_pos,
			Window* win,
			float x_size, float y_size) : UI(x_pos, y_pos, x_size, y_size) {
			this->isMove = false;

			this->name = new UIString(name,
				x_pos + 0.015f,
				y_pos + y_size + up_size / 4.f,  // + win_name_pos[1]
				new color{ 1.f, 1.f, 1.f, 1.f },
				0.25f
			);

			this->win = win;
			this->mouse_pos = win->GetMousePosition();
		};

		void UIWindow::Draw() {
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

			if (!win->MouseLock()) {
				x_mouse = mouse_pos->x;
				y_mouse = mouse_pos->y;
				delete mouse_pos;
				mouse_pos = win->GetMousePosition();

				const float x = (x_pos + win->format->x_side_magic_number) / win->format->x_side_magic_number / 2.f;
				const float y = -(y_pos - (win->format->y_side_magic_number - (y_size - 1.f)) + up_size) / 2.4f; // -2.49f

				bool click = false;
				if (Input::GetKeyDown(KeyCode::MouseLeft))
					click = true;

				if(click)
					if (mouse_pos->x > x&& mouse_pos->x < (double)(x + win->format->x_mouse_magic_number * x_size)
						&& mouse_pos->y > y && mouse_pos->y < (double)(y + win->format->y_mouse_magic_number * y_size + up_size / 2.f)
						) {
						isMove = true;
					}

				if (isMove) {
					x_pos -= (x_mouse - mouse_pos->x) * 5.f;
					y_pos += (y_mouse - mouse_pos->y) * 2.5f;

					name->SetPosition(x_pos + 0.015f, y_pos + y_size + up_size / 4.f);
				}

				if (Input::GetKeyUp(KeyCode::MouseLeft))
					isMove = false;
			}

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

			{glColor4f(0.3f, 0.6f, 0.3f, 0.9f);
				glRectf(
					x_pos,			y_pos + y_size,
					x_pos + x_size, y_pos + y_size + up_size // Семщение вверх
				);
			glBegin(GL_LINE_LOOP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2f(x_size + x_pos,  y_pos + y_size);
				glVertex2f(x_pos,		    y_pos + y_size);
				glVertex2f(x_pos,		    y_pos + y_size + up_size);
				glVertex2f(x_size + x_pos,  y_pos + y_size + up_size);
			glEnd();}

			name->Draw();
		}
	}
}