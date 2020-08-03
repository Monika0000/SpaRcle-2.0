#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstddef>
#include <GL\glew.h>
#include <gl\gl.h>    // Заголовочный файл для библиотеки OpenGL32
#include <gl\glu.h>   // Заголовочный файл для библиотеки GLu32
#include <gl\glaux.h> // Заголовочный файл для библиотеки GLaux
#include <math.h>     // Заголовочный файл для математической библиотеки ( НОВОЕ )
#include <Debug.h>

#include "Vectors.h"
#include <Vector3.h>
#include <SRString.h>
#include "Input.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Window;
		class UI {
		protected:
			double x_mouse;
			double y_mouse;

			float x_pos;
			float y_pos;

			float x_size;
			float y_size;

			Window* win = nullptr;
			//Vector2f* pos;
			//Vector2f* size;
		public:
			virtual void Draw(vec2b mouse_left, vec2d mouse_pos) = 0;
		public:
			float XPosCorrect() const;
		public:
			UI( Window* win,
				float x_pos, float y_pos,
				float x_size, float y_size) 
			{
				this->x_pos = x_pos;
				this->y_pos = y_pos;

				this->x_size = x_size;
				this->y_size = y_size;

				this->x_mouse = 0.f;
				this->y_mouse = 0.f;

				this->win = win;

				//pos  = new Vector2f { x_pos, y_pos };
				//size = new Vector2f{ x_size, y_size };
			}

			~UI() {
				//delete pos;
				//delete size;
			}
		};
	}
}