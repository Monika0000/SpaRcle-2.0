#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
#include <cstddef>
#include <GL\glew.h>
#include <gl\gl.h>    // Заголовочный файл для библиотеки OpenGL32
#include <gl\glu.h>   // Заголовочный файл для библиотеки GLu32
#include <gl\glaux.h> // Заголовочный файл для библиотеки GLaux
#include <math.h>     // Заголовочный файл для математической библиотеки ( НОВОЕ )
#include <Debug.h>

namespace SpaRcle {
	namespace Graphics {
		class Font{
			GLuint   base;		  // База списка отображения для фонта
			GLfloat  cnt1;		  // Первый счетчик для передвижения и закрашивания текста
			GLfloat  cnt2;		  // Второй счетчик для передвижения и закрашивания текста
			HDC      hDC;  // Приватный контекст устройства GD
		public:
			Font() { 
				base = NULL;
				cnt1 = NULL;
				cnt2 = NULL;
				hDC = NULL;
			};
			~Font() { Kill(); };
		public:
			GLvoid Build(Helper::Debug*debug) {  // Построение нашего растрового шрифта
				debug->Info("Building font...");

				HFONT  font;            // Идентификатор фонта

				base = glGenLists(96);  // Выделим место для 96 символов ( НОВОЕ )
				font = CreateFont(
					-24,        // Высота фонта ( НОВОЕ )
					0,        // Ширина фонта
					0,        // Угол отношения
					0,        // Угол наклона
					FW_BOLD,      // Ширина шрифта
					FALSE,        // Курсив
					FALSE,        // Подчеркивание
					FALSE,        // Перечеркивание
					ANSI_CHARSET,      // Идентификатор набора символов
					OUT_TT_PRECIS,      // Точность вывода
					CLIP_DEFAULT_PRECIS,    // Точность отсечения
					ANTIALIASED_QUALITY,    // Качество вывода
					FF_DONTCARE | DEFAULT_PITCH,  // Семейство и шаг
					L"Courier New");      // Имя шрифта
				SelectObject(hDC, font);        // Выбрать шрифт, созданный нами ( НОВОЕ )
				wglUseFontBitmaps(hDC, 32, 96, base); // Построить 96 символов начиная с пробела ( НОВОЕ )
			}
			GLvoid Kill(GLvoid) {       // Удаление шрифта
				glDeleteLists(base, 96);        // Удаление всех 96 списков отображения ( НОВОЕ )
			}
			GLvoid glPrint(const char* fmt, ...) {       // Заказная функция «Печати» GL
				char    text[256];      // Место для нашей строки
				va_list    ap;          // Указатель на список аргументов

				if (fmt == NULL)     // Если нет текста
					return;            // Ничего не делать

				va_start(ap, fmt);           // Разбор строки переменных
					vsprintf(text, fmt, ap); // И конвертирование символов в реальные коды
				va_end(ap);                  // Результат помещается в строку

				glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения ( НОВОЕ )
				glListBase(base - 32);          // Задать базу символа в 32 ( НОВОЕ )
				glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);// Текст списками отображения(НОВОЕ)
				glPopAttrib(); // Возврат битов списка отображения ( НОВОЕ )
			};
		};
	}
}
