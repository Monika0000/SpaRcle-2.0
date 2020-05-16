#pragma once
#include <Windows.h>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		enum class KeyCode {
			Esc = 27, //, Shift, Enter, Space, W
		};

		class Input {
		public:
			static bool GetKey(KeyCode key);
			static std::vector<int> GetPressKeyIndexes();
		};
	}
}

