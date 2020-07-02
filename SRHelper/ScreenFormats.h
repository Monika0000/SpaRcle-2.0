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
			const float Aspect() const { return (float)size_x / (float)size_y; }

			const unsigned short size_x;
			const unsigned short size_y;

			const float x_side_magic_number;
			const float y_side_magic_number;

			const float x_mouse_magic_number;
			const float y_mouse_magic_number;

			WindowFormat(unsigned short size_x, unsigned short size_y, 
				float x_side_magic_number, float y_side_magic_number,
				float x_mouse_magic_number, float y_mouse_magic_number
			) 
				: size_x(size_x), size_y(size_y),
				x_side_magic_number(x_side_magic_number), y_side_magic_number(y_side_magic_number),
				x_mouse_magic_number(x_mouse_magic_number), y_mouse_magic_number(y_mouse_magic_number)
			{

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