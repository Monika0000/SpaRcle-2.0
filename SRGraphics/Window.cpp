#include "pch.h"
#include "Window.h"
#include <SRHelper.h>
#include "WindowEvents.h"
//#include <GL\freeglut_std.h>
#include <GL/glut.h>
#include "Camera.h"
#include "UI.h"
#include <glm\ext\matrix_clip_space.hpp>

namespace SpaRcle {
	namespace Graphics {
		Window* Window::global = nullptr;
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

		/*
		
		������ / ������ x 100
		
		*/

		void Position(GLFWwindow* window, int x, int y) {
			Window* win = Window::Get();
			win->SetXPos(x);
			win->SetYPos(y);
			glfwSetWindowPos(window, x, y);
		}
		void Resize(GLFWwindow* window, int width, int height) {
			Window* win = Window::Get();

			int x_size = win->GetXSize();
			int y_size = win->GetYSize();

			glfwSetWindowSize(window, x_size, y_size);

			float ratio = 1.0 * x_size / y_size;
			glMatrixMode(GL_PROJECTION);// ���������� ������� ��������
			glLoadIdentity();// Reset �������
			glViewport(0, 0, x_size, y_size);// ���������� ���� ���������
			gluPerspective(45, ratio, 0.1, 1000);// ���������� ���������� �����������.
			glMatrixMode(GL_MODELVIEW);// ��������� � ������

			win->projective = glm::perspective(glm::radians(45.f), ratio, 0.1f, 1000.0f);

			/*
			if (height == 0)
				height = 1;

			width = (height + 34) * (16.f / 9.f);
			
			glfwSetWindowSize(window, width, height);

			float ratio = 1.0 * width / height;
			glMatrixMode(GL_PROJECTION);// ���������� ������� ��������
			glLoadIdentity();// Reset �������
			glViewport(0, 0, width, height);// ���������� ���� ���������
			gluPerspective(45, ratio, 0.1, 1000);// ���������� ���������� �����������.
			glMatrixMode(GL_MODELVIEW);// ��������� � ������

			std::cout << width << " " << height << std::endl;

			Window* win = Window::Get();
			win->SetXSize(width);
			win->SetYSize(height);
			*/
		 	if(win->GetIsRun()) win->Draw();
		}

		Vector2d* Window::GetMousePosition() {
			Vector2d* vec = new Vector2d{ 0, 0 };
			if(window)
				glfwGetCursorPos(window, &vec->x, &vec->y);
			//vec->Normalize();
			vec->x = vec->x / this->format->size_x;
			vec->y = vec->y / this->format->size_y;
			//if(vec->x < 0.5)
			return vec;
		}

		Window::Window(Debug* debug, Camera* camera, const char* name, WindowFormat* window_format, bool isMouseLock, bool vsync) {
			if (global) {
				debug->Error("Window already create!");
				EventsManager::PushEvent(EventsManager::Events::Error);
				Sleep(1000);
				return;
			}
			else {
				this->isMouseLock = isMouseLock;
				this->vsync = vsync;

				this->screen_size = GraphUtils::GetDesktopResolution();
				this->debug = debug;
				this->global = this;

				this->camera = camera;

				this->x_pos = screen_size->x / 2;
				this->y_pos = screen_size->y / 2;

				//this->font = new Font();
				//this->cursor = GetCursor();

				//this->x_size = screen_format.x;
				//this->y_size = screen_format.y;

				this->format = window_format;

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

		bool Window::Create(int argcp, char** argv) {
			debug->Graph("Creating window...");

			if (String::Contains(name, ' ')) {
				debug->Error("Window name contains empty symbol (space)! \n\t\tWindow name : \"" + std::string(name) + "\"");
				return false;
			}

			this->argcp = argcp;
			this->argv  = argv;

			fps = new UIString("FPS : " + std::to_string(GraphUtils::GetFPS()), 0.5f, 0.25f, new color { 0.f, 1.f, 0.1f, 0.7f });
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

			while (!this->isInitWindow) { Sleep(1); /* wait oppened winodw...*/ }

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

				window = glfwCreateWindow(format->size_x, format->size_y, name, nullptr, nullptr);
				if (!window) {
					fprintf(stderr, "Failed to open GLFW window\n");
					glfwTerminate();
					return false;
				}
				glfwMakeContextCurrent(window);

				glfwSetWindowPos(window, 
					screen_size->x / 2 - format->size_x / 2,
					screen_size->y / 2 - format->size_y / 2);
				GraphUtils::CheckSystemErrors("Init glfw : ");

				GLFWimage icons[1];
				unsigned char* pxs = SOIL_load_image((Utils::GetPathToExe() + "../../Resources/icon.png").c_str(), &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
				if (pxs) {
					icons[0].pixels = pxs;
					glfwSetWindowIcon(window, 1, icons);
					SOIL_free_image_data(icons[0].pixels);
				} else debug->Error("Failed loading ico image! Continue...");

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
			glewExperimental = TRUE;
			GLenum err = glewInit();
			if (err != GLEW_OK) {
				debug->Error("glewInit is failure!");
				GraphUtils::CheckSystemErrors("Init glew : ");
				return false;
			}

			isInitGlew = true;

			return true;
		}
		bool Window::InitParametrs() {
			debug->Graph("Initializing parametrs...");
			glEnable(GL_BLEND); // ������������ ������
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_COLOR_MATERIAL);

			glEnable(GL_MULTISAMPLE);

			//glEnable(GL_COLOR_SUM);  https://stackoverflow.com/questions/8265636/how-to-get-specular-color-in-opengl
			//glEnable(GL_FOG); // �����

			///\%info ��������� �������, ����� ���������� �� "�������� ����������" �������� ���������
			glDepthFunc(GL_LEQUAL); // GL_GEQUAL - is not work
			glDepthRange(0.0, 1.0);
			glEnable(GL_DEPTH_TEST);
			///!glClearDepth(1.f);
			glEnable(GL_CULL_FACE); // ��������� ������

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // ������������� ������� ���������� �����������
			//glShadeModel(GL_SMOOTH);    // ��������� ������� ���������

			if(isMouseLock)
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

			glfwSwapInterval(vsync); // v-sync
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
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // ��� ����� ������ �� ����� �������� (������� ������)

			shader->Use();
			camera->Move();

			glPushMatrix(); // ���������� �������
				render->DrawAllObjects();
			glPopMatrix();

			render->DrawAllUI();

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
			//hWnd = FindWindow(NULL, String::CharsToWchars(name));
			if (!hWnd) {
				debug->Error("Failed find window : window hWnd is nullptr! Win name : "+std::string(name));
				Sleep(5000);
				return false;
			}
			hDC = GetDC(hWnd);

			Resize(window, format->size_x, format->size_y);
			Position(window, 
				screen_size->x / 2 - format->size_x / 2,
				screen_size->y / 2 - format->size_y / 2);

			if (!render->Init()) {
				debug->Error("Failed initializing of render!");
				return false;
			}
			else {
				this->shader = render->GetShader();
				this->camera->SetShader(shader);
			}

			isInitWindow = true;
			isRun = true;
			while(isRun && !glfwWindowShouldClose(window)) {
				this->PollEvents();

				this->fps->SetString("FPS : " + std::to_string(GraphUtils::GetFPS()));

				this->Draw();
			} 

			debug->Info("Window has been completed work! isRun = " + std::to_string(isRun));

			return true;
		}
		bool Window::Close() {
			debug->Graph("Close window...");

			isRun = false;
			if (task.joinable()) task.join();

			return true;
		}
	}
}