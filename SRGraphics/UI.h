#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstddef>
#include <GL\glew.h>
#include <gl\gl.h>    // ������������ ���� ��� ���������� OpenGL32
#include <gl\glu.h>   // ������������ ���� ��� ���������� GLu32
#include <gl\glaux.h> // ������������ ���� ��� ���������� GLaux
#include <math.h>     // ������������ ���� ��� �������������� ���������� ( ����� )
#include <Debug.h>

#include "Vectors.h"
#include <Vector3.h>
#include <SRString.h>
#include "Input.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class UI {
		protected:
			Vector2f* pos;
			Vector2f* size;
		public:
			virtual void Draw() = 0;
		public:
			UI(
				float x_pos, float y_pos,
				float x_size, float y_size) 
			{
				pos  = new Vector2f { x_pos, y_pos };
				size = new Vector2f{ x_size, y_size };
			}

			~UI() {
				delete pos;
				delete size;
			}
		};
	}
}