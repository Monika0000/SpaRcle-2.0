#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		enum class KeyboardLayout { EN, RU, UNKNOWN };

		enum class KeyCode {
			Esc = 27, E = 69, I = 73, O = 79, P = 80, Q = 81, R = 82, T = 84, U = 85, W = 87, Y = 89
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

