#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		enum class KeyboardLayout { EN, RU, UNKNOWN };

		enum class KeyCode {
			MouseLeft = 1, MouseRight = 2, MouseMiddle = 4, Tab = 9, Enter = 13, LShift = 16, Ctrl = 17, Alt = 18,
			Esc = 27, Space = 32, LeftArrow = 37, UpArrow = 38, RightArrow = 39, DownArrow = 40, A = 65, B = 66, C = 67, D = 68,
			E = 69, F = 70, I = 73, L = 76, M = 77, O = 79, P = 80, Q = 81, S = 83, R = 82, T = 84, U = 85, W = 87, Y = 89,
			Tilde = 192
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
			static bool FixedGetKeyDown(KeyCode key) {
				bool b = GetKeyDown(key);
				GetKeyUp(key);
				return b;
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

