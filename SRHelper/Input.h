#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		enum class KeyboardLayout { EN, RU, UNKNOWN };

		enum class KeyCode {
			Esc = 27, //, Shift, Enter, Space, W
		};

		class Input {
		public:
			static bool GetKey(KeyCode key);
			static std::vector<int> GetPressKeyIndexes();

			inline static KeyboardLayout GetLayout() {
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				DWORD id = GetThreadId(hStdOut);

				switch (LOWORD(GetKeyboardLayout(id))) {
					case 0x409: return KeyboardLayout::EN;
					case 0x419: return KeyboardLayout::RU;
					default: return KeyboardLayout::UNKNOWN;
				}
			}
		};
	}
}

