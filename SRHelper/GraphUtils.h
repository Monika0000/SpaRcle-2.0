#pragma once
#include <iostream>
#include <Windows.h>
#include "ScreenFormats.h"

namespace SpaRcle {
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
            static Vector2* GetWindowSize(HWND hwnd) {
                Vector2* size = new Vector2();
                RECT rect;
                if (GetWindowRect(hwnd, &rect)) {
                    size->x = rect.right - rect.left;
                    size->y = rect.bottom - rect.top;
                }
                return size;
            }
            static Vector2* GetWindowPos(HWND hwnd) {
                Vector2* pos = new Vector2();
                RECT rect = { NULL };
                if (GetWindowRect(hwnd, &rect)) {
                    pos->x = rect.left;
                    pos->y = rect.top;
                }
                return pos;
            }
            static HINSTANCE GetHINSTANCE(HWND hwnd) {
                return (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);
            }
            static HINSTANCE GetHINSTANCE() {
                return (HINSTANCE)GetWindowLong(GetConsoleWindow(), GWLP_HINSTANCE);
            }
            static HWND GetHWND() { return GetConsoleWindow(); }
            static int GetFPS() {
                static int start = GetTickCount64();
                static int frames = 0;
                static int fps = 0;

                int timer = GetTickCount64() - start;
                frames++;

                if ((timer) >= 1000)
                {
                    fps = frames;
                    frames = 0;
                    timer = 0;
                    start = GetTickCount64();
                }
                return fps;
            }
        };
	}
}