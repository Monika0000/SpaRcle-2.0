#pragma once
#include "Vector3.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphics {
		//enum ScreenFormat {
		//	Unknown, _16x9
		//};

		class WindowFormat {
		public:
			unsigned short size_x;
			unsigned short size_y;

			float x_side_magic_number;
			float y_side_magic_number;

			float x_mouse_magic_number;
			float y_mouse_magic_number;

			WindowFormat(unsigned short size_x, unsigned short size_y, 
				float x_side_magic_number, float y_side_magic_number,
				float x_mouse_magic_number, float y_mouse_magic_number
			) {
				this->size_x = size_x;
				this->size_y = size_y;

				this->x_side_magic_number = x_side_magic_number;
				this->y_side_magic_number = y_side_magic_number;

				this->x_mouse_magic_number = x_mouse_magic_number;
				this->y_mouse_magic_number = y_mouse_magic_number;
			}
		};

		class WindowMinimize : public WindowFormat {
		public:
			WindowMinimize() : WindowFormat(1127, 600, 
				2.34, 1.21f,
				0.214f, 0.4f
			) {

			}
		};

	}
}