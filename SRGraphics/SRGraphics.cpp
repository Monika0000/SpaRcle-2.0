// SRGraphics.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "SRGraphics.h"
#include <functional>

namespace SpaRcle {
	namespace Graphics {
		SRGraphics* SRGraphics::global = nullptr;

		void DisplayFunc() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Очищается буфер кадра и буфер глубины
			glPushMatrix();                                      // Запоминается матрица модели

			float size = 2.5f;

			//glPointSize(1.0f);
			glBegin(GL_QUADS);
				glColor3f(0.5f, 0.0f, 0.0f);
				glVertex2f(0, 0);
				glVertex2f(size, 0);
				glVertex2f(size, size);
				glVertex2f(0, size);
			glEnd();

			glColor3f(0.0f, 0.0f, 1.0f);                         // Задается текущий цвет примитивов
			glutWireCube(2.0f);                                  // Рисуется проволочный куб со стороной 2

			//glPopMatrix();
			glutSwapBuffers();
		}
		bool SRGraphics::Init() {
			debug->Graph("Initializing graphics engine...");
			this->win = new Window(debug);

			if (!this->win->InitGlut(argcp, argv)) {
				debug->Error("Failed initializing glut!");
				return false;
			}

			this->win->SetDisplayFunc(DisplayFunc);

			if (!this->win->InitGlew()) {
				debug->Error("Failed initializing glew!");
				return false;
			}

			return true;
		}
	}
}
