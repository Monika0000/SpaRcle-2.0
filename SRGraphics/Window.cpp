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

		void Position(GLFWwindow* window, int x, int y) {
			Window* win = Window::Get();
			win->SetXPos(x);
			win->SetYPos(y);
			glfwSetWindowPos(window, x, y);
		}
		void Resize(GLFWwindow* window, int width, int height) {
			if (height == 0)
				height = 1;
			float ratio = 1.0 * width / height;
			glMatrixMode(GL_PROJECTION);// ���������� ������� ��������
			glLoadIdentity();// Reset �������
			glViewport(0, 0, width, height);// ���������� ���� ���������
			gluPerspective(45, ratio, 0.1, 1000);// ���������� ���������� �����������.
			glMatrixMode(GL_MODELVIEW);// ��������� � ������

			Window* win = Window::Get();
			win->SetXSize(width);
			win->SetYSize(height);
			
			win->Draw();
		}

		Window::Window(Debug* debug, Camera* camera, const char* name, unsigned short w, unsigned short h) {
			if (global) {
				debug->Error("Window already create!");
				return;
			}
			else {
				this->screen_size = GraphUtils::GetDesktopResolution();
				this->debug = debug;
				this->global = this;

				this->camera = camera;

				this->x_pos = screen_size->x / 2;
				this->y_pos = screen_size->y / 2;

				//this->font = new Font();
				this->cursor = GetCursor();

				this->x_size = w;
				this->y_size = h;

				this->name = name;
				this->hWnd = NULL;

				isInitGlut = false;
				isInitDisplay = false;
				isInitGlew = false;
			}
		}
		void Window::PollEvents() {
			MSG msg;			// ������� ����	
			// ������������� ��� ����������� �������
			while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				//std::cout << msg.message << " " << msg.wParam << std::endl;

				switch (WindowEvents::GetEvent(msg.message, msg.wParam)) {
				case WindowEvents::Close: {
					if (MessageBox(NULL, L"Do You Want To Exit?", L"Exit?", MB_YESNO) == IDYES) {
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

		bool Window::Create() {
			debug->Info("Creating window...");
			font = CreateFont(
				18, 0, 0, 0, 300,
				false, false, false,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
				L"Arial");

			fps = new UI("FPS : " + std::to_string(GraphUtils::GetFPS()), 0.5f, 0.25f);
			render->AddUI(fps);

			return true;
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

				camera->Init(isMouseLock);

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
				glfwWindowHint(GLFW_SAMPLES, 4); // 4x �����������

				/* ���������� ������� �������� �������� ������������ ������, � ������, ����������� ������� */
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ��� ����� OpenGL 3.3
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //��� �� ����� ������ OpenGL
				// ������� ���� � �������� ��������

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
				GraphUtils::CheckSystemErrors("Init glfw : ");

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
				hwnd = FindWindowA(NULL, name); // ������� ����
				pOrigProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);

				// ��������� ������ "����������", ��������� ���������
				//SetWindowLong(m_window, GWL_STYLE, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
				// ��������� ������� ��������� windows ���������
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

			// �������������� GLEW
			//glewExperimental = TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				debug->Error("glewInit is failure!");
				GraphUtils::CheckSystemErrors("Init glew : ");
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
			glEnable(GL_BLEND); // ������������ ������
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_COLOR_SUM);
			//glEnable(GL_FOG); // �����

			///\%info ��������� �������, ����� ���������� �� "�������� ����������" �������� ���������
			glDepthFunc(GL_LEQUAL); // GL_GEQUAL - is not work
			glDepthRange(0.0, 1.0);
			glEnable(GL_DEPTH_TEST);
			///!glClearDepth(1.f);
			glEnable(GL_CULL_FACE); // ��������� ������

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // ������������� ������� ���������� �����������
			//glShadeModel(GL_SMOOTH);    // ��������� ������� ���������

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			//font->Build(debug);

			return true;
		}
		bool Window::InitGlut(int argcp, char** argv) {
			this->argcp = argcp;
			this->argv  = argv;

			debug->Graph("Initializing glut...");

			/*
			typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int interval);
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
			if (wglSwapIntervalEXT)
				wglSwapIntervalEXT(1);
			*/

			glfwSwapInterval(true); // v-sync
			glfwSetFramebufferSizeCallback(window, Resize);
			glfwSetWindowPosCallback(window, Position);
			glfwShowWindow(window);
				
			glutInit(&argcp, argv); 
			//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
			//glutInitWindowSize((int)x_size, (int)y_size);
			//glutInitWindowPosition(
			//	screen_size->x / 2 - x_size / 2,
			//	screen_size->y / 2 - y_size / 2);

			if(false)
				GraphUtils::CheckSystemErrors("Init glut : ");

			isInitGlut = true;
			return true;
		}

		void Window::Draw() {
			///glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // ��� ����� ������ �� ����� �������� (������� ������)

			//if (Input::FixedGetKeyDown(KeyCode::P))
			//	camera->ResetCameraPos();

			glPushMatrix(); // ���������� �������
				render->DrawAllObjects();
			glPopMatrix();
			//glMatrixMode(GL_MODELVIEW); glLoadIdentity();

			glFlush();

			render->DrawAllUI();

			camera->Move();

			glfwSwapBuffers(window);
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

			hWnd = GraphUtils::FindWindowFromName(name);
			if (!hWnd) {
				debug->Error("Failed find window : window hWnd is nullptr!");
				return false;
			}
			hDC = GetDC(hWnd);

			Resize(window, x_size, y_size);
			Position(window, 
				screen_size->x / 2 - x_size / 2,
				screen_size->y / 2 - y_size / 2);

			isRun = true;
			while(isRun && !glfwWindowShouldClose(window)) {
				this->PollEvents();

				this->fps->SetString("FPS : " + std::to_string(GraphUtils::GetFPS()));

				this->Draw();

				//GraphUtils::CheckSystemErrors("Draw : ");
			} 

			debug->Info("Window has been completed work!");

			return true;
		}
		bool Window::Close() {
			debug->Graph("Close window...");

			isRun = false;
			if (task.joinable()) task.join();

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