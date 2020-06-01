#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		enum class KeyboardLayout { EN, RU, UNKNOWN };

		enum class KeyCode {
			MouseLeft = 1, MouseRight = 2, MouseMiddle = 4, Tab = 9, Enter = 13, Esc = 27, 
			E = 69, I = 73, M = 77, O = 79, P = 80, Q = 81, R = 82, T = 84, U = 85, W = 87, Y = 89
		};

		class Input {
		private:
			static bool* pressed_keys;
		public:
			static bool GetKeyUp(KeyCode key) {
				bool b = GetKey(key);

				if (!pressed_keys[int(key)]) {
					//if (b) pressed_keys[int(key)] = true;
					return false;
				}
				else if (!b) pressed_keys[int(key)] = false;

				return !b;

				/*
				if (pressed_keys[size_t(key)] && !b) {
					pressed_keys[size_t(key)] = false;
					return true;
				}
				else { 
					if (b) pressed_keys[size_t(key)] = true;
					return false;
				}*/
			}
			static bool GetKeyDown(KeyCode key) {
				bool b = GetKey(key);

				if (pressed_keys[int(key)]) {
					//if (!b) pressed_keys[int(key)] = false;
					return false;
				}
				else if(b) pressed_keys[int(key)] = true;

				return b;

				/*
				if (!pressed_keys[size_t(key)] && b) {
					pressed_keys[size_t(key)] = true;
					return true;
				}
				else { 
					if(!b) pressed_keys[size_t(key)] = false;
					return false; 
				}*/
			}
			static bool GetKey(KeyCode key);
			static std::vector<int> GetPressKeyIndexes();
			static void PrintPressIndexes();

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

