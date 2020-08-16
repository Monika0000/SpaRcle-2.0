#pragma once
#include "Vector3.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphics {
		//enum ScreenFormat {
		//	Unknown, _16x9
		//};

		class Screen {
		public:
			const float Aspect() const { return (float)size_x / (float)size_y; }

			const unsigned short size_x;
			const unsigned short size_y;

			//const float x_left_side_pos_magic_number;
			//const float y_side_magic_number;

			//const float x_mouse_magic_number;
			//const float y_mouse_magic_number;

			Screen(unsigned short size_x, unsigned short size_y//,
				//float x_left_side_pos_magic_number//, float y_side_magic_number,
				//float x_mouse_magic_number, float y_mouse_magic_number
			)
				: size_x(size_x), size_y(size_y)//,
				//x_left_side_pos_magic_number(x_left_side_pos_magic_number)//, y_side_magic_number(y_side_magic_number),
				//x_mouse_magic_number(x_mouse_magic_number), y_mouse_magic_number(y_mouse_magic_number)
			{

			}
		};

		class ScreenFormats {
		public:
			class _720_576 : public Screen {
			public:
				//WindowMinimize() : WindowFormat(1127, 600, 
				_720_576() : Screen(720, 576//,
					//1.55374f //2.34//, 1.21f,
					//0.214f, 0.4f
				) {

				}
			};
			class _1600_900 : public Screen {
			public:
				_1600_900() : Screen(1600, 900//,
				//	2.20625f //2.20 //, 1.21f, //TODO:TODO y
					//0.232f, 0.4f //TODO:TODO y
				) { };
			};
			class _800_450 : public Screen {
			public:
				_800_450() : Screen(800, 450//,
					//2.20625f //2.20 //, 1.21f, //TODO:TODO y
					//0.232f, 0.4f //TODO:TODO y
				) {};
			};
			class _1366_768 : public Screen {
			public:
				_1366_768() : Screen(1366, 768//,
					//2.20625f //2.20 //, 1.21f, //TODO:TODO y
					//0.232f, 0.4f //TODO:TODO y
				) {};
			};
			class _1280_720 : public Screen {
			public:
				_1280_720() : Screen(1280, 720//,
					//2.20625f //2.20 //, 1.21f, //TODO:TODO y
					//0.232f, 0.4f //TODO:TODO y
				) {};
			};
		};
	}
}