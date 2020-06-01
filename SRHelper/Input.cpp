#include "pch.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Debug.h"

namespace SpaRcle {
	namespace Helper {
        bool* Input::pressed_keys = nullptr;
		bool Input::GetKey(KeyCode key) {
            if (!pressed_keys) {
                pressed_keys = new bool[256];
                for (size_t t = 0; t < 256; t++)
                    pressed_keys[t] = false;
            }
			//BYTE arr[256];
			BYTE* arr = new BYTE[256];
            bool result = false;

            memset(arr, 0, sizeof(256));
            GetKeyState(0);
            if (GetKeyboardState(arr)) {
                int temp = (int)arr[(int)key];
                temp >>= 7;
                result = (bool)temp;
            }
            else
                Debug::InternalError("Input::GetKey() : unknown error!");

            delete[] arr;

			return result;
		}
        std::vector<int> Input::GetPressKeyIndexes() {
            std::vector<int> r = std::vector<int>();

            int temp;
            BYTE* arr = new BYTE[256];

            memset(arr, 0, sizeof(256));
            GetKeyState(0);
            if (GetKeyboardState(arr)) {
                for (int i = 0; i < 256; i++) {
                    temp = (int)arr[i];
                    temp >>= 7;

                    if ((bool)temp) r.push_back(i);
                }
            }
            else
                Debug::InternalError("Input::GetPressKeyIndexes() : unknown error!");

            delete[] arr;

            return r;
        }
		void Input::PrintPressIndexes(){
            std::vector<int> indexes = GetPressKeyIndexes();
            if (indexes.size() > 0)
            {
                std::cout << "Pressed keys : ";
                for (int i : indexes)
                    std::cout << i << " ";
                std::cout << std::endl;
            }
            indexes.clear();
		}
	}
}