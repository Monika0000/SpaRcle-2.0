#include "pch.h"
#include "UIWindow.h"
#include "Window.h"

namespace SpaRcle {
	namespace Graphics {
		const float win_name_pos[2] = { 0, 0 };
		const float up_size = 0.045f;

		UIWindow::UIWindow(
			Window* win,
			std::string name,
			float x_pos, float y_pos,
			float x_size, float y_size, bool CanMove) : UI(win, x_pos, y_pos, x_size, y_size), CanMove(CanMove) {
			this->isMove = false;

			this->name = new UIString(
				win, name,
				x_pos + 0.015f,
				y_pos + y_size + up_size / 4.f,  // + win_name_pos[1]
				new color{ 1.f, 1.f, 1.f, 1.f },
				0.25f
			);

			//this->win = win;
			//this->mouse_pos = win->GetMousePosition();
		};

		void UIWindow::Draw(vec2b mouse_left, vec2d mouse_pos) {
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

			float x_pos_correct = XPosCorrect();//x_pos * win->format->x_left_side_pos_magic_number / 2.20625f;

			if (CanMove) if (!win->MouseLock()) {

				//delete mouse_pos;
				//mouse_pos = win->GetMousePosition();

				//std::cout << "mouse_y = " << mouse_pos.y << "; mouse_x = " << mouse_pos.x << std::endl;

				/* MATH X_LEFT_SIDE_MAGIC_NUMBER */ //std::cout << "mouse_x = " << mouse_pos->x << "; win_x = " << (this->x_pos + 2.20625f) / (2.20625f * 2.f) << std::endl;
				/* MATH X_LEFT_SIDE_MAGIC_NUMBER */ //std::cout << "mouse_x = " << mouse_pos->x << "; win_x = " << this->x_pos << std::endl;
				//!std::cout << "mouse_y = " << mouse_pos->y << "; win_y = " << (2.485431f - (this->y_pos + 0.788201f)) / 2.485431f << std::endl;
				//const float y_up = (2.485431f - (this->y_pos + 0.788201f)) / 2.485431f;//-(y_pos - (win->format->y_side_magic_number - (y_size - 1.f)) + up_size) / 2.4f; // -2.49f

				x_left = (x_pos_correct + win->format->x_left_side_pos_magic_number) / (win->format->x_left_side_pos_magic_number * 2.f);//(x_pos + win->format->x_side_magic_number) / win->format->x_side_magic_number / 2.f;
				y_up = -((this->y_pos - (2.197257f - y_size)) / 2.48549f);//-(y_pos - (win->format->y_side_magic_number - (y_size - 1.f)) + up_size) / 2.4f; // -2.49f
				x_right = (x_pos_correct + x_size + win->format->x_left_side_pos_magic_number) / (win->format->x_left_side_pos_magic_number * 2.f);
				y_down = -((this->y_pos - (2.197257f + up_size)) / 2.48549f);;
				//const float y_down = (2.485431f - (((this->y_pos - y_size - up_size) + 0.788201f))) / 2.485431f;
				
				//std::cout << mouse_pos->x << " == " << x_left << "; " << mouse_pos->y << " == " << y << std::endl;
				//std::cout << mouse_pos->y << " == " << y_down << std::endl;
				//std::cout << mouse_pos->x << " == " << x_right << "; " << mouse_pos->y << " == " << y_down << std::endl;

				//bool click = false;
				//if (Input::GetKeyDown(KeyCode::MouseLeft))
				//	click = true;

				if(mouse_left.x)
					//if (mouse_pos->x > x&& mouse_pos->x < (double)(x + win->format->x_mouse_magic_number * x_size)
						//&& mouse_pos->y > y && mouse_pos->y < (double)(y + win->format->y_mouse_magic_number * y_size + up_size / 2.f)
					if (mouse_pos.x > x_left && mouse_pos.x < x_right 
						&& mouse_pos.y > y_up && mouse_pos.y < y_down
					)
					{
						isMove = true;
					}

				if (isMove) {
					x_pos -= (x_mouse - mouse_pos.x) * 5.f;
					y_pos += (y_mouse - mouse_pos.y) * 2.5f;

					//name->SetPosition(x_pos_correct + 0.015f, y_pos + y_size + up_size / 4.f);
				}
				
				if (mouse_left.y)
					isMove = false;
				//if (Input::GetKeyUp(KeyCode::MouseLeft))
				//	isMove = false;
				//if (Input::FixedGetKeyDown(KeyCode::DownArrow))
				//	y_pos -= 0.001f;
				//if (Input::FixedGetKeyDown(KeyCode::UpArrow))
				//	y_pos += 0.001f;
				x_mouse = mouse_pos.x;
				y_mouse = mouse_pos.y;
			}

			name->SetPosition(x_pos_correct + 0.015f, y_pos + y_size + up_size / 4.f);

			{glColor4f(0.2, 0.2, 0.2, 0.8f);
				glRectf(
					x_pos_correct,		    y_pos,
					x_pos_correct + x_size, y_pos + y_size
				);
			glBegin(GL_LINE_LOOP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2f(x_size + x_pos_correct, y_pos);
				glVertex2f(x_pos_correct,		   y_pos);
				glVertex2f(x_pos_correct,		   y_size + y_pos);
				glVertex2f(x_size + x_pos_correct, y_size + y_pos);
			glEnd();}

			//!--------------------------------------------------

			{glColor4f(0.3f, 0.6f, 0.3f, 0.9f);
				glRectf(
					x_pos_correct,			y_pos + y_size,
					x_pos_correct + x_size, y_pos + y_size + up_size // Семщение вверх
				);
			glBegin(GL_LINE_LOOP);
				glColor3f(0.f, 0.f, 0.f);
				glVertex2f(x_size + x_pos_correct,  y_pos + y_size);
				glVertex2f(x_pos_correct,		    y_pos + y_size);
				glVertex2f(x_pos_correct,		    y_pos + y_size + up_size);
				glVertex2f(x_size + x_pos_correct,  y_pos + y_size + up_size);
			glEnd();}

			name->Draw(mouse_left, mouse_pos);

			DrawElements(mouse_left, mouse_pos);
		}
		void UIWindow::DrawElements(vec2b mouse_left, vec2d mouse_pos)
		{
		}
	}
}