#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#pragma comment(lib, "glfw.lib")
#pragma comment(lib, "glfw3.lib")
//#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew64.lib")
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

namespace SpaRcle {
	namespace Graphics {

		class Camera;
		using namespace SpaRcle::Helper;
		class Window {
			friend class SRGraphics;
		private:
			bool isRun = false;
		private:
			unsigned short x_size;
			unsigned short y_size;
			const char* name;
			GLFWwindow* window;
			Camera* camera;
			Render* render;
			Font* font;
		private:
			char** argv;
			int argcp;
		public:
			void SetCamera(Camera* camera) { this->camera = camera; }
			void SetRender(Render* render) { this->render = render; }
			Window(Debug* debug, Camera* camera = NULL, const char*name = "SpaRcle Engine", unsigned short w = 400, unsigned short h = 300) {
				if (global) {
					debug->Error("Window already create!");
					return;
				}
				else {
					this->screen_size = GraphUtils::GetDesktopResolution();
					this->debug = debug;
					this->global = this;

					this->camera = camera;

					this->font = new Font();

					this->x_size = w;
					this->y_size = h;

					this->name = name;
					this->hwnd = NULL;

					isInitGlut = false;
					isInitDisplay = false;
					isInitGlew = false;
				}
			}
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
			Vector2* screen_size;
			std::thread task;

			HWND hwnd;
			//int handle;
		public:
			static Window* Get() {
				if (global) return global;
				else {
					Debug::InternalError("Window is not create!");
					return nullptr;
				}
			}
			bool Close();
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