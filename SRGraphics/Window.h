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
#include "ColorBuffer.h"

namespace SpaRcle {
	namespace Graphics {
		class Camera;
		using namespace SpaRcle::Helper;
		class Window {
			friend class SRGraphics;
			friend class UI;
		private:
			bool EditorMode = false;
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

			std::string resources_folder = "";
			//Font* font;
			//HFONT font;
			//HCURSOR cursor;
		private:
			char** argv;
			int argcp;
		public:
			glm::mat4 projective;

			WindowFormat* format;
			WindowFormat* minimize;
			WindowFormat* maximize;
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
			vec2d GetMousePos();
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

			Camera* GetCamera() { return camera; };
			Render* GetRender() { return render; };
			HWND GetHWND() {
				if (hWnd) return hWnd;
				else {
					Debug::InternalError("Window::GetHWND() : window is not create!");
					return nullptr;
				}
			}

			Mesh*  GetAimedMesh()	  { return AimedMesh; }
			Model* GetSelectedModel() { return SelectedModel; }
		public:
			Window(
				Debug* debug, Camera* camera = NULL, 
				const char*name = "SpaRcle Engine", 
				WindowFormat* window_minimize = new Screen_720_576(), WindowFormat* window_maximize = new Screen_1600_900(),
				bool isMouseLock = true, bool vsync = true
			);
			~Window() { Close(); }
		private:
			bool isInitGlut;
			bool isInitGlew;
			bool isInitDisplay;
		private:
			void SetProjectionMatrix(GLvoid) {
				glMatrixMode(GL_PROJECTION);            // �������� ����� ������������� � �������� ��������
				//gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
				glLoadIdentity();                       // ������� ������� (��������) ������������ �� ���������
				//glFrustum(-1, 1, -1, 1, 3, 10);         // ��������������� ������������� ��������
			}
			void SetModelviewMatrix(GLvoid) {
				glMatrixMode(GL_MODELVIEW);             // �������� ����� ������������� � �������� ������
				glLoadIdentity();                       // ������� ������� (������) ������������ �� ���������
				
				glTranslatef(0.0, 0.0, -8.0);           // ������� ��������� ����������� �� 8 ������ ������ �����
				
				return; 
				
				glRotatef(30.0, 1.0, 0.0, 0.0);         // � �������������� �� 30 �������� ������ ��� x,
				glRotatef(70.0, 0.0, 1.0, 0.0);         // � ����� �� 70 �������� ������ ��� y
			}
			void PollEvents();
		private:
			void SelectObject();
			void AimMesh();
		private:
			static Window* global;

			Model* SelectedModel	 = nullptr;
			Mesh* AimedMesh		     = nullptr;

			Debug* debug			 = nullptr;
			Vector2i* screen_size	 = nullptr;
			std::thread task;

			HWND hWnd;
			HDC hDC;
			//int handle;
		private:
			//!======== UI ======== 
			UIString* fps = nullptr;
			//!======== UI ======== 
		public:
			ColorBuffer* colorBuffer = nullptr;
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
			bool Create(int argcp, char** argv, std::string resources_folder);
			bool Init();
			/*
			void Resize(GLsizei width, GLsizei height) {
				//glutReshapeWindow(800, 600);
				//glutPostRedisplay(); // This call may or may not be necessary

				if (height == 0) height = 1;
				float ratio = 1.0 * width / height;

				// ���������� ������� ��������
				SetProjectionMatrix();

				// ���������� ���� ���������
				glViewport(0, 0, width, height);

				// ���������� ���������� �����������.
				gluPerspective(45, ratio, 1, 1000);

				// ��������� � ������
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