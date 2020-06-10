#include "pch.h"
#include "Window.h"
#include <SRHelper.h>
#include "WindowEvents.h"
//#include <GL\freeglut_std.h>
#include <GL/glut.h>
#include "Camera.h"
#include "UI.h"

namespace SpaRcle {
	namespace Graphics {
		Window* Window::global = nullptr;

		//void character_callback(GLFWwindow* window, unsigned int codepoint)
		//{
		//	std::cout << (char)codepoint;
		//}
		//void reshape(GLsizei width, GLsizei height) { 
			//Window::Get()->Resize(width, height); 
		//}
		//void windowSizeCallback(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }
		/*
		static WNDPROC pOrigProc = NULL;
		LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			switch (msg) {
				case WM_SIZE: {
					Vector2* size = GraphUtils::GetWindowSize(hwnd);
					//Vector2* pos  = GraphUtils::GetWindowPos(hwnd);

					//size->y = 300;

					size->x = size->y * (16.f / 9.f);

					SetWindowPos(hwnd, 0, 0, 0, size->x, size->y, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

					//if(Input::GetKey(KeyCode::I)) 
					Window::Get()->Resize(size->x, size->y);

					delete size;
					//delete pos;
					break;
				}
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
		*/

		void Resize(GLFWwindow* window, int width, int height) {
			//By defualt rearranges OpenGL viewport to the current framebuffer size.
			std::cout << width << " " << height << std::endl;
			glViewport(0, 0, width, height);
		}
		void Window::PollEvents() {
			MSG msg;			// события окна	
			// просматриваем все поступившие события
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				//std::cout << msg.message << " " << msg.wParam << std::endl;

				switch (WindowEvents::GetEvent(msg.message, msg.wParam)) {
				case WindowEvents::Close: {
					if (MessageBox(hwnd, L"Do You Want To Exit?", L"Exit?", MB_YESNO) == IDYES) {
						//DestroyWindow(hwnd);
						EventsManager::PushEvent(EventsManager::Events::Exit);
						glfwTerminate();
					}
					else {
						debug->Log("You can't close this window.");
					}
					break;
				}
				default:
					DispatchMessage(&msg);
					break;
				}
				
				//TranslateMessage(&msg);
			}
		}

		bool Window::Init() {
			task = std::thread([this]() {
				if (!InitGlfw()) {
					debug->Error("Failed initializing glfw!");
					return false;
				}
				
				if (!InitGlew()) {
					debug->Error("Failed initializing glew!");
					return false;
				}

				if (!InitGlut(argcp, argv)) {
					debug->Error("Failed initializing glut!");
					return false;
				}

				InitParametrs();

				camera->Init();

				if (!InitWindow()) {
					debug->Error("Failed initializing window!");
					return false;
				}
			});
			return true;
		}

		bool Window::InitGlfw() {
			debug->Graph("Initializing glfw...");
			if (glfwInit()) {
				glfwWindowHint(GLFW_SAMPLES, 4); // 4x сглаживание

				/* Дальнейшие функции являются причиной некорректной работы, а именно, отсутствием рендера */
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // нам нужен OpenGL 3.3
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //нам не нужен старый OpenGL
				// Откроем окно и создадим контекст

				window = glfwCreateWindow(x_size, y_size, name, nullptr, nullptr);
				if (!window) {
					fprintf(stderr, "Failed to open GLFW window\n");
					glfwTerminate();
					return false;
				}
				glfwMakeContextCurrent(window);

				glfwSetWindowPos(window, 
					screen_size->x / 2 - x_size / 2, 
					screen_size->y / 2 - y_size / 2);

				return true;
			}
			else
				return false;
		};
		bool Window::InitGlew() {
			debug->Graph("Initializing glew...");

			/*
			task = std::thread([this]() {
				if (!RegisterWindowClass()) {
					debug->Error("Failed Initializing glew!");
					return false;
				}

				int handle = glutCreateWindow(name);
				hwnd = FindWindowA(NULL, name); // находим окно
				pOrigProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);

				// Отключаем кнопку "развернуть", остальные остальное
				//SetWindowLong(m_window, GWL_STYLE, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
				// Назначаем функцию обработки windows сообщений
				//SetWindowLong(hwnd, GWLP_WNDPROC, (LONG)WindowProc);
				//SetWindowLongPtr(m_window, GWLP_WNDPROC, (LONG_PTR)&WindowProc);

				if (!hwnd) {
					debug->Error("Call to CreateWindow failed!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					return false;
				}

				if (!DisplayFunc) {
					debug->Error("Display func is nullptr!");
					return false;
				}
				else glutDisplayFunc(DisplayFunc);

				glutReshapeFunc(reshape);

				if (glewInit()) {
					debug->Error("Failed initializing glew!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					return false;
				}

				InitDisplay();
				glutMainLoop();
			});
			*/

			// Инициализируем GLEW
			//glewExperimental = TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				debug->Error("glewInit is failure!");
				return false;
			}
			//glfwSwapInterval(1);
			//glfwSetWindowSizeCallback(window, windowSizeCallback);
			//glfwShowWindow(window);

			isInitGlew = true;

			return true;
		}
		bool Window::InitParametrs() {
			debug->Graph("Initializing parametrs...");
			glEnable(GL_BLEND); // Прозрачность стекла
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_COLOR_SUM);
			glEnable(GL_FOG); // Туман

			///\%info ПРОВЕРЯЕМ ГЛУБИНУ, ЧТОБЫ ИЗБАВИТЬСЯ ОТ "ЭФФЕКТИА ПЕРЕКРЫТИЯ" ДАЛЬНИМИ ОБЪЕКТАМИ
			glDepthFunc(GL_LEQUAL); // GL_GEQUAL - is not work
			glDepthRange(0.0, 1.0);
			glEnable(GL_DEPTH_TEST);
			//glClearDepth(1.f);
			glEnable(GL_CULL_FACE); // Отсечение граней

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Действительно хорошие вычисления перспективы
			glShadeModel(GL_SMOOTH);    // Разрешить плавное затенение

			font->Build(debug);

			return true;
		}
		bool Window::InitGlut(int argcp, char** argv) {
			this->argcp = argcp;
			this->argv  = argv;

			debug->Graph("Initializing glut...");

			glfwSwapInterval(1);
			glfwSetFramebufferSizeCallback(window, Resize);
			glfwShowWindow(window);

			glutInit(&argcp, argv); 
			//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			//glutInitWindowSize((int)x_size, (int)y_size);
			//glutInitWindowPosition(
			//	screen_size->x / 2 - x_size / 2,
			//	screen_size->y / 2 - y_size / 2);



			isInitGlut = true;

			return true;
		}
		bool Window::InitWindow() {
			debug->Graph("Initializing window...");

			if (!render) {
				debug->Error("Render is nullptr!");
				return false;
			}
			if (!camera) {
				debug->Error("Camera is nullptr!");
				return false;
			}

			isRun = true;
			//glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

			//glfwSetCharCallback(window, character_callback);
			while(isRun && !glfwWindowShouldClose(window)) {
				this->PollEvents();
				//std::cout << GraphUtils::GetFPS() << std::endl;

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)
					
				glPushMatrix(); // Сохранение матрици
					//glBegin(GL_TRIANGLES);
					//	glColor3f(0.0, 1.0, 0.0);
					//	glVertex3f(0.0f, 1.0f, 0.0f);
					//	glVertex3f(1.0f, -1.0f, 0.0f);
					//	glVertex3f(-1.0f, -1.0f, 0.0f);
					//glEnd();
					render->DrawAllObjects();

					glColor3f(1.0f, 255.0f, 1.0f);
					glRasterPos2f(1, 1);
					UI::glPrint("Active OpenGL Text With NeHe - %7.2f");

					//UI::RenderString3D("Example");
				glPopMatrix();

				glFlush();
				

				camera->Move();

				glfwSwapBuffers(window);
			} 

			debug->Info("Window has been completed work!");

			return true;
		}
		bool Window::Close() {
			debug->Graph("Close window...");

			isRun = false;
			if (task.joinable()) task.join();

			delete font;

			return true;
		}
		
		/*
		bool Window::RegisterWindowClass() {
			debug->Graph("Register window class...");
			
			WNDCLASSEXW wnd;

			wnd.cbSize = sizeof(WNDCLASSEXW);
			//wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = WindowProc;
			wnd.cbClsExtra = 0;
			wnd.cbWndExtra = 0;
			wnd.hInstance = 0;
			wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			wnd.hIconSm = wnd.hIcon;
			wnd.hCursor = LoadCursor(0, IDC_ARROW);
			wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wnd.lpszMenuName = NULL;
			wnd.lpszClassName = String::CharsToLPWSTR(name);
			wnd.cbSize = sizeof(WNDCLASSEX);

			if (!RegisterClassEx(&wnd)) {
				debug->Error("Failed register window class!");
				EventsManager::PushEvent(EventsManager::Events::Error);
				return false;
			}

			return true;
		}*/
	}
}