#include "pch.h"
#include "Window.h"
#include <SRHelper.h>

namespace SpaRcle {
	namespace Graphics {
		Window* Window::global = nullptr;

		void reshape(GLsizei width, GLsizei height) {
			Window::Get()->Resize(width, height);
		}

		static WNDPROC pOrigProc = NULL;
		LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
				case WM_CLOSE: {
					if (MessageBox(hwnd, L"Do You Want To Exit?", L"Exit?", MB_YESNO) == IDYES) {
						DestroyWindow(hwnd);
						EventsManager::PushEvent(EventsManager::Events::Exit);
					} else return 0;
				}
				default:
					break;
			}

			return CallWindowProc(pOrigProc, hwnd, msg, wparam, lparam);
			//return DefWindowProc(hwnd, msg, wparam, lparam);
		}

		bool Window::InitGlut(int argcp, char** argv) {
			this->argcp = argcp;
			this->argv  = argv;

			debug->Graph("Initializing glut...");

			glutInit(&argcp, argv);

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			glutInitWindowSize((int)x_size, (int)y_size);
			glutInitWindowPosition(
				screen_size->x / 2 - x_size / 2,
				screen_size->y / 2 - y_size / 2);

			isInitGlut = true;

			return true;
		}
		bool Window::InitGlew() {
			debug->Graph("Initializing glew...");

			task = std::thread([this]() {
				handle = glutCreateWindow(name);

				hwnd = FindWindowA(NULL, name); // находим окно
				pOrigProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);

				// Отключаем кнопку "развернуть", остальные остальное
				//SetWindowLong(m_window, GWL_STYLE, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
				// Назначаем функцию обработки windows сообщений
				//SetWindowLong(hwnd, GWLP_WNDPROC, (LONG)WindowProc);
				//SetWindowLongPtr(m_window, GWLP_WNDPROC, (LONG_PTR)&WindowProc);

				if (!DisplayFunc) {
					debug->Error("Display func is nullptr!");
					return false;
				} else 
					glutDisplayFunc(DisplayFunc);
				
				glutReshapeFunc(reshape);

				if (glewInit()) {
					debug->Error("Failed initializing glew!");
					return false;
				}

				InitDisplay();

				glutMainLoop();
			});

			isInitGlew = true;

			return true;
		}
	}
}