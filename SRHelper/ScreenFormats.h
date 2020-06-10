#pragma once
#include "Vector3.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphisc {
		enum ScreenFormat {
			Unknown, _16x9
		};

		class Screen {
		private:
			Screen() {};
			~Screen() {};
		public:
			static ScreenFormat GetScreenFormat(Vector2* screen_size) {
				if (screen_size->x == 1600 && screen_size->y == 900) {
					return _16x9;
				}
				else return ScreenFormat::Unknown;
			}
		};
	}
}