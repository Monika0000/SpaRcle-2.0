#include "pch.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Debug.h"

namespace SpaRcle {
	namespace Helper {
		bool Input::GetKey(KeyCode key) {
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
	}
}