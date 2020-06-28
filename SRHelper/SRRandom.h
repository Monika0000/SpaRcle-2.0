#pragma once
#include <ctime>
#include <cstdlib>

namespace SpaRcle {
	namespace Helper {
		class Random {
		public:
			static bool Bool(bool absolute = false) {
				if(absolute) srand(time(0));
				return rand() % 2;
			}
		};
	}
}