#pragma once
#include <iostream>
#include <Windows.h>
#include "ScreenFormats.h"
#include "SRString.h"

namespace SpaRcle {
	namespace Graphics {
        class GraphUtils {
        public:
            static vec3f TransliteColor(unsigned int r, unsigned int g, unsigned int b) {
                vec3f color = { r / 255.f, g / 255.f, b / 255.f };
                return color;
            }
            static float* TransliteFloatColor(unsigned int r, unsigned int g, unsigned int b) {
                float color[3] { r / 255.f, g / 255.f, b / 255.f };
                return color;
            }
            static Vector2i* GetDesktopResolution() {
                Vector2i* size = new Vector2i();

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
            static Vector2i* GetWindowSize(HWND hwnd) {
                Vector2i* size = new Vector2i();
                RECT rect;
                if (GetWindowRect(hwnd, &rect)) {
                    size->x = rect.right - rect.left;
                    size->y = rect.bottom - rect.top;
                }
                return size;
            }
            static Vector2i* GetWindowPos(HWND hwnd) {
                Vector2i* pos = new Vector2i();
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
            static HWND FindWindowFromName(const char* name) {
                //return FindWindow(NULL, L"SpaRcle");
               // LPCWSTR str = String::CharsToLPWSTR(name);
                //return FindWindow(NULL, String::CharsToWchars(name));
                return FindWindowW(NULL, String::CharsToLPWSTR(name));
            }
            static void CheckSystemErrors(const char* from = "") {
                DWORD err = GetLastError();
                switch (err) {
                    case 0:
                        break;
                    case 6:
                        Debug::SysGraphError(std::string(from) + "The handle is invalid.");
                        break;
                    case 127:
                        Debug::SysGraphError(std::string(from) + "The specified procedure could not be found.");
                        break;
                    case 1813:
                        Debug::SysGraphError(std::string(from) + "The specified resource type cannot be found in the image file.");
                        break;
                    default:
                        Debug::SysGraphError(std::string(from) + "Unknown code system error : " + std::to_string(err));
                        break;
                }
                return;
            }
            static void SetCursor(bool visible, DWORD size = 0) {
                if (size == 0) {
                    size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
                }
                CONSOLE_CURSOR_INFO lpCursor;
                lpCursor.bVisible = visible;
                lpCursor.dwSize = size;
                SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
            }
        };
	}
}