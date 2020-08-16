#include "pch.h"
#include "Window.h"
#include <SRHelper.h>
#include "WindowEvents.h"
//#include <GL\freeglut_std.h>
#include <GL/glut.h>
#include "Camera.h"
//#include "UI.h"
#include <glm\ext\matrix_clip_space.hpp>
#include "SRGraphics.h"
#include <CommCtrl.h>
#include <WinUser.h>
#include <Debug.h>

#pragma comment(lib, "COMCTL32.LIB") // For toolBar

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
		
		второе / первое x 100
		
		*/

		void Position(GLFWwindow* window, int x, int y) {
			Window* win = Window::Get();
			win->SetXPos(x);
			win->SetYPos(y);
			glfwSetWindowPos(window, x, y);
			//if(win->GetIsRun()) win->Draw();  // Re-draw
		}
		void Resize(GLFWwindow* window, int width, int height) {
			Window* win = Window::Get();

			int x_size = win->GetXSize();
			int y_size = win->GetYSize();

			glfwSetWindowSize(window, x_size, y_size);

			//float ratio = 1.0 * x_size / y_size;
			float ratio = 16.0 / 9.0;
			glMatrixMode(GL_PROJECTION);// используем матрицу проекции
			glLoadIdentity();// Reset матрицы
			glViewport(0, 0, x_size, y_size);// определяем окно просмотра
			gluPerspective(45, ratio, 0.1, 8000);// установить корректную перспективу.
			glMatrixMode(GL_MODELVIEW);// вернуться к модели

			win->projective = glm::perspective(glm::radians(45.f), ratio, 0.1f, 8000.0f);

			if (win->GetRender()) win->GetRender()->Resize(width, height);

			/*
			if (height == 0)
				height = 1;

			width = (height + 34) * (16.f / 9.f);
			
			glfwSetWindowSize(window, width, height);

			float ratio = 1.0 * width / height;
			glMatrixMode(GL_PROJECTION);// используем матрицу проекции
			glLoadIdentity();// Reset матрицы
			glViewport(0, 0, width, height);// определяем окно просмотра
			gluPerspective(45, ratio, 0.1, 1000);// установить корректную перспективу.
			glMatrixMode(GL_MODELVIEW);// вернуться к модели

			std::cout << width << " " << height << std::endl;

			Window* win = Window::Get();
			win->SetXSize(width);
			win->SetYSize(height);
			*/

		 	//if(win->GetIsRun()) win->Draw(); // Re-draw

			if(win->GetEditorMode()) win->CreateToolBar(); // Re-Create
		}

		vec2d Window::GetMousePos() {
			vec2d pos = { 0, 0 };
			
			if (window)
				glfwGetCursorPos(window, &pos.x, &pos.y);
			pos.x /= this->format->size_x;
			pos.y /= this->format->size_y;
			return pos;
		}
		void Window::SetMousePos(float x, float y) {
			if (window)
				glfwSetCursorPos(window, x, y);
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

		Window::Window(Debug* debug, Camera* camera, const char* name, Screen* window_minimize,
			Screen* window_maximize, bool isMouseLock, bool vsync)
		{
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

				this->format = window_minimize;
				this->maximize = window_maximize;
				this->minimize = window_minimize;

				this->name = name;
				this->hWnd = NULL;

				isInitGlut = false;
				isInitDisplay = false;
				isInitGlew = false;
			}
		}
		bool Window::CreateToolBar() {
			if (!EditorMode) return false;/*
			//debug->Info("Wondow : creating tool bar...");
			HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE); //GWL_HINSTANCE

			if (hWndToolBar) {
				DestroyWindow(hWndToolBar);
				hWndToolBar = nullptr;
			}

			TBBUTTON tbb[] = {
					 {33, 181,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
					 { 1, 182,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
					 { 2, 183,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
					 { 0,   0,                0, TBSTYLE_SEP,    0, 0},
					 { 3, 184,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
					 { 4, 185,                0, TBSTYLE_BUTTON, 0, 0},
					 { 5, 186,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
					 { 0,   0,                0, TBSTYLE_SEP,    0, 0},
					 { 6, 187,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
			};

			//hWndToolBar = CreateWindowEx(0x80, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_FLAT | WS_BORDER, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
			hWndToolBar = CreateToolbarEx(hWnd, WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE,
				180,                 // идентификатор органа Toolbar     IDT_TOOLBAR
				7,                   // количество пиктограмм
				HINST_COMMCTRL,      //  hInstance,           // идентификатор приложения
				IDB_STD_SMALL_COLOR, // IDB_BITMAP,          // идентификатор битового изображения кнопок   IDB_STD_SMALL_COLOR, // 
				(LPCTBBUTTON)&tbb,   // адрес описания кнопок
				9,                   // количество кнопок
				0, 0,                // ширина и высота кнопок
				16, 16,              // ширина и высота пиктограмм
				sizeof(TBBUTTON));   // размер структуры в байтах
			if (hWndToolBar == NULL)
				return false;

			//SendMessage(hWndToolBar, TB_SETBITMAPSIZE, 0, MAKELONG(0, 10));
			//SendMessage(hWndToolBar, TB_SETBUTTONSIZE, 0, MAKELONG(0, 10));
			//SendMessage(hWndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
			//SendMessage(hWndToolBar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

			//SendMessage(hWndToolBar, TB_AUTOSIZE, 0, 0);
			ShowWindow(hWndToolBar, TRUE);
			*/
			return true;
		}
		void Window::PollEvents() {
			MSG msg;			// события окна	
			// просматриваем все поступившие события
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
				case WindowEvents::ALT_F4: {
					debug->System("Alt+F4 has been pressed.");
					EventsManager::PushEvent(EventsManager::Events::Exit);
					glfwTerminate();
					break;
				}
				case WindowEvents::MouseIdle: {
					if (EditorMode) if (!this->isMouseLock) this->AimMesh();
					break;
				}
				case WindowEvents::Maximize: {
					bool lock = MouseLock();
					if(lock) this->MouseLock(false);
					Sleep(50);
					if (format == maximize) {
						debug->Log("Window event : minimize window.");
						format = minimize;
					}
					else {
						format = maximize;
						debug->Log("Window event : maximize window.");
					}
					Resize(window, format->size_x, format->size_y);
					glfwSetWindowPos(window,
						screen_size->x / 2 - format->size_x / 2,
						screen_size->y / 2 - format->size_y / 2);
					camera->SetCursorPosition(screen_size->x / 2, screen_size->y / 2);
					Sleep(50);
					if (lock) this->MouseLock(true);
					break;
				}
				case WindowEvents::LeftClick: {
					if (EditorMode) if (!MouseLock()) if(!AimedMesh) this->SelectObject();
					break;
				}
				default:
					DispatchMessage(&msg);
					break;
				}
				
				//TranslateMessage(&msg);
			}
		}

		bool Window::Create(int argcp, char** argv, std::string resources_folder) {
			debug->Graph("Creating window...");

			this->colorBuffer = new ColorBuffer();

			this->resources_folder = resources_folder;

			if (String::Contains(name, ' ')) {
				debug->Error("Window name contains empty symbol (space)! \n\t\tWindow name : \"" + std::string(name) + "\"");
				return false;
			}

			this->argcp  = argcp;
			this->argv   = argv;

			this->canvas = new Canvas(this);
			
			this->fps    = new GUIText(canvas);
			this->fps->SetColor(0,1,0,1);
			this->canvas->AddGUIText(fps);

			//fps = new UIString(this, "FPS : " + std::to_string(GraphUtils::GetFPS()), 0.5f, 0.25f, new color { 0.f, 1.f, 0.1f, 0.7f });
			//render->AddUI(fps);

			return true;
		}
		bool Window::Init() {
			this->EditorMode = render->GetGraphicsEngine()->EditorMode;

			bool error = false;

			task = std::thread([this, &error]() {
				if (!InitGlfw()) {
					debug->Error("Window::Init() : Failed initializing glfw!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					error = true;
					return false;
				}
				
				if (!InitGlew()) {
					debug->Error("Window::Init() : Failed initializing glew!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					error = true;
					return false;
				}

				if (!InitGlut(argcp, argv)) {
					debug->Error("Window::Init() : Failed initializing glut!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					error = true;
					return false;
				}

				InitParametrs();

				//MouseLock(isMouseLock);

				//camera->Init(isMouseLock, window);
				camera->Init(isMouseLock, this);

				if (!InitWindow()) {
					debug->Error("Window::Init() : Failed initializing window!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					error = true;
					return false;
				}
			});

			while (!this->isInitWindow) { Sleep(1); if (error) return false; /* wait oppened window...*/ }

			return true;
		}

		bool Window::InitGlfw() {
			debug->Graph("Initializing glfw...");
			if (glfwInit()) {
				glfwWindowHint(GLFW_SAMPLES, 4); // 4x сглаживание
				//glfwWindowHint(GLFW_SAMPLES, 16); // 16x сглаживание

				/* Дальнейшие функции являются причиной некорректной работы, а именно, отсутствием рендера */
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // нам нужен OpenGL 3.3
				//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //нам не нужен старый OpenGL
				// Откроем окно и создадим контекст

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
				unsigned char* pxs = SOIL_load_image((resources_folder+"\\icon.png").c_str(), &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
				if (pxs) {
					icons[0].pixels = pxs;
					glfwSetWindowIcon(window, 1, icons);
					SOIL_free_image_data(icons[0].pixels);
				} else debug->Error("Failed loading ico image! Continue...\n\t" + (resources_folder + "\\icon.png"));

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
			glEnable(GL_BLEND); // Прозрачность стекла
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_COLOR_MATERIAL);

			glEnable(GL_MULTISAMPLE);

			//!==============================================[LIGHTING]================================================
			glEnable(GL_LIGHTING); // здесь включается расчет освещения 
			glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // делаем так, чтобы освещались обе стороны полигона 
			glEnable(GL_NORMALIZE); //делам нормали одинаковой величины во избежание артефактов
			//!==============================================[LIGHTING]================================================

			//glEnable(GL_COLOR_SUM);  https://stackoverflow.com/questions/8265636/how-to-get-specular-color-in-opengl
			//glEnable(GL_FOG); // Туман

			///\%info ПРОВЕРЯЕМ ГЛУБИНУ, ЧТОБЫ ИЗБАВИТЬСЯ ОТ "ЭФФЕКТИА ПЕРЕКРЫТИЯ" ДАЛЬНИМИ ОБЪЕКТАМИ
			glDepthFunc(GL_LEQUAL); // GL_GEQUAL - is not work
			glDepthRange(0.0, 1.0);
			glEnable(GL_DEPTH_TEST);
			///!glClearDepth(1.f);
			glEnable(GL_CULL_FACE); // Отсечение граней

			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Действительно хорошие вычисления перспективы
			//glShadeModel(GL_SMOOTH);    // Разрешить плавное затенение

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

		void Window::SelectObject() {
			Model* select = render->GetSelectedModel();

			if (!select) {
				if (SelectedModel) SelectedModel->isSelect = false;
				SelectedModel = nullptr;
			}
			else {
				if (SelectedModel) SelectedModel->isSelect = false;
				SelectedModel = select; 
				if (SelectedModel) SelectedModel->isSelect = true;
			}
		}
		void Window::AimMesh() {
			AimedMesh = render->GetAimingMesh();
			//if(AimedMesh) std::cout << AimedMesh << std::endl;
		}

		void Window::Draw() {
			//if (EditorMode) if (!MouseLock() && Input::GetKeyDown(KeyCode::MouseLeft)) SelectObject();

			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)

			//shader->Use();
			if (SelectedModel) camera->MoveStencil();
			//if (SelectedModel) camera->MoveSelector();

			camera->Move();

			//glPushMatrix(); // Сохранение матрици
				render->DrawAllObjects();
			//render->DrawSelectorObjects();
			//glPopMatrix();

			//render->DrawAllUI();

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

			if (EditorMode)
				if (!CreateToolBar()) {
					debug->Error("Window:InitWindow() : failed create tool bar!");
					return false;
				}

			Resize(window, format->size_x, format->size_y);
			Position(window, 
				screen_size->x / 2 - format->size_x / 2,
				screen_size->y / 2 - format->size_y / 2);

			if (!render->Init()) {
				debug->Error("Failed initializing of render!");
				return false;
			}
			else {
				this->canvas->Init();

				this->shader = render->GetGeometryShader();
				//this->camera->AddShader(shader);
			}

			isInitWindow = true;
			isRun = true;
			while(isRun && !glfwWindowShouldClose(window)) {
				this->PollEvents();

				this->fps->SetString("FPS : " + std::to_string(GraphUtils::GetFPS()));

				this->Draw();

				//!===================================================

				this->canvas->PoolEvents();

				this->canvas->Draw();

				//!===================================================

				glfwSwapBuffers(window);
			} 

			debug->Info("Window has been completed work! isRun = " + std::to_string(isRun));

			this->render->Close();
			delete this->canvas;

			return true;
		}
		bool Window::Close() {
			debug->Graph("Close window...");

			isRun = false;
			if (task.joinable()) task.join();

			delete this->format;
			delete this->colorBuffer;

			return true;
		}
	}
}