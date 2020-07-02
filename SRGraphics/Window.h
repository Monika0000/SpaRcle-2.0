#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#pragma comment(lib, "glfw.lib")
#pragma comment(lib, "glfw3.lib")
//#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
//#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "SOIL.lib")

#include <iostream>
//#include <GL/glfw.h>
//#include <GL/glut.h> // include this only after glew.h
//#include <GL/freeglut.h> // include this only after glew.h
#include <string>
#include <thread>
#include <SRHelper.h>
#include <GraphUtils.h>
#include "Render.h"
#include "ScreenFormats.h"

namespace SpaRcle {
	namespace Graphics {
		class Camera;
		using namespace SpaRcle::Helper;
		class Window {
			friend class SRGraphics;
			friend class UI;
		private:
			bool isInitWindow = false;
			bool isRun = false;
			bool isMouseLock = true;
			bool vsync = true;
		private:
			int x_pos; 
			int y_pos;

			const char* name;
			GLFWwindow* window;
			Camera* camera;
			Render* render;
			Shader* shader;
			//Font* font;
			//HFONT font;
			//HCURSOR cursor;
		private:
			char** argv;
			int argcp;
		public:
			glm::mat4 projective;
			WindowFormat* format;
		public:
			const int GetXSize() const { return format->size_x; }
			const int GetYSize() const { return format->size_y; }
			const void SetXPos(const int x_pos) { this->x_pos = x_pos; }
			const void SetYPos(const int y_pos) { this->y_pos = y_pos; }
			//void SetXSize(int x_size) { this->x_size = x_size; }
			//void SetYSize(int y_size) { this->y_size = y_size; }
		public:
			bool GetIsRun() const { return isRun; };
			Vector2d* GetMousePosition();
			void MouseLock(const bool val) {
				if(val)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				isMouseLock = val; 
			};
			const bool MouseLock() const { return isMouseLock; };
			void SetCamera(Camera* camera) { this->camera = camera; };
			void SetRender(Render* render) { this->render = render; };
			HWND GetHWND() {
				if (hWnd) return hWnd;
				else {
					Debug::InternalError("Window::GetHWND() : window is not create!");
					return nullptr;
				}
			}
			Window(
				Debug* debug, Camera* camera = NULL, 
				const char*name = "SpaRcle Engine", 
				WindowFormat* window_format = new WindowMinimize(),
				bool isMouseLock = true, bool vsync = true
			);
			~Window() { Close(); }
		private:
			bool isInitGlut;
			bool isInitGlew;
			bool isInitDisplay;
		private:
			void SetProjectionMatrix(GLvoid) {
				glMatrixMode(GL_PROJECTION);            // Действия будут производиться с матрицей проекции
				//gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
				glLoadIdentity();                       // Текущая матрица (проекции) сбрасывается на единичную
				//glFrustum(-1, 1, -1, 1, 3, 10);         // Устанавливается перспективная проекция
			}
			void SetModelviewMatrix(GLvoid) {
				glMatrixMode(GL_MODELVIEW);             // Действия будут производиться с матрицей модели
				glLoadIdentity();                       // Текущая матрица (модели) сбрасывается на единичную
				
				glTranslatef(0.0, 0.0, -8.0);           // Система координат переносится на 8 единиц вглубь сцены
				
				return; 
				
				glRotatef(30.0, 1.0, 0.0, 0.0);         // и поворачивается на 30 градусов вокруг оси x,
				glRotatef(70.0, 0.0, 1.0, 0.0);         // а затем на 70 градусов вокруг оси y
			}
			void PollEvents();
		private:
			static Window* global;
			Debug* debug;
			Vector2i* screen_size;
			std::thread task;

			HWND hWnd;
			HDC hDC;
			//int handle;
		private:
			//!======== UI ======== 
			UIString* fps;
			//!======== UI ======== 
		public:
			void Draw();
			static Window* Get() {
				if (global) return global;
				else {
					Debug::InternalError("Window::Get() : window is not create!");
					return nullptr;
				}
			}
			bool Close();
			bool Create(int argcp, char** argv);
			bool Init();
			/*
			void Resize(GLsizei width, GLsizei height) {
				//glutReshapeWindow(800, 600);
				//glutPostRedisplay(); // This call may or may not be necessary

				if (height == 0) height = 1;
				float ratio = 1.0 * width / height;

				// используем матрицу проекции
				SetProjectionMatrix();

				// определяем окно просмотра
				glViewport(0, 0, width, height);

				// установить корректную перспективу.
				gluPerspective(45, ratio, 1, 1000);

				// вернуться к модели
				SetModelviewMatrix();
			}*/
		private:
			//bool RegisterWindowClass();
			bool InitGlfw();
			bool InitGlut(int argcp, char** argv);
			bool InitGlew();
			bool InitParametrs();

			bool InitWindow();
		};
	}
}