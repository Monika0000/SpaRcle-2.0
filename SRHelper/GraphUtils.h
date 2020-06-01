#pragma once
#include <iostream>
#include <Windows.h>

namespace SpaRcle {
    struct Vector2 {
        int x, y;
    };

	namespace Graphics {
        class GraphUtils {
        public:
            static Vector2* GetDesktopResolution() {
                Vector2* size = new Vector2();

                RECT desktop;
                // Get a handle to the desktop window
                const HWND hDesktop = GetDesktopWindow();
                // Get the size of screen to the variable desktop
                GetWindowRect(hDesktop, &desktop);
                // The top left corner will have coordinates (0,0)
                // and the bottom right corner will have coordinates
                // (horizontal, vertical)
                size->x = desktop.right;
                size->y = desktop.bottom;

                return size;
            }
        };
	}
}