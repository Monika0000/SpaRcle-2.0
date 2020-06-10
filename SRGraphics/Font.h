#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Material.h"
#include <cstddef>
#include <GL\glew.h>
#include <gl\gl.h>    // ������������ ���� ��� ���������� OpenGL32
#include <gl\glu.h>   // ������������ ���� ��� ���������� GLu32
#include <gl\glaux.h> // ������������ ���� ��� ���������� GLaux
#include <math.h>     // ������������ ���� ��� �������������� ���������� ( ����� )
#include <Debug.h>

namespace SpaRcle {
	namespace Graphics {
		class Font{
			GLuint   base;		  // ���� ������ ����������� ��� �����
			GLfloat  cnt1;		  // ������ ������� ��� ������������ � ������������ ������
			GLfloat  cnt2;		  // ������ ������� ��� ������������ � ������������ ������
			HDC      hDC;  // ��������� �������� ���������� GD
		public:
			Font() { 
				base = NULL;
				cnt1 = NULL;
				cnt2 = NULL;
				hDC = NULL;
			};
			~Font() { Kill(); };
		public:
			GLvoid Build(Helper::Debug*debug) {  // ���������� ������ ���������� ������
				debug->Info("Building font...");

				HFONT  font;            // ������������� �����

				base = glGenLists(96);  // ������� ����� ��� 96 �������� ( ����� )
				font = CreateFont(
					-24,        // ������ ����� ( ����� )
					0,        // ������ �����
					0,        // ���� ���������
					0,        // ���� �������
					FW_BOLD,      // ������ ������
					FALSE,        // ������
					FALSE,        // �������������
					FALSE,        // ��������������
					ANSI_CHARSET,      // ������������� ������ ��������
					OUT_TT_PRECIS,      // �������� ������
					CLIP_DEFAULT_PRECIS,    // �������� ���������
					ANTIALIASED_QUALITY,    // �������� ������
					FF_DONTCARE | DEFAULT_PITCH,  // ��������� � ���
					L"Courier New");      // ��� ������
				SelectObject(hDC, font);        // ������� �����, ��������� ���� ( ����� )
				wglUseFontBitmaps(hDC, 32, 96, base); // ��������� 96 �������� ������� � ������� ( ����� )
			}
			GLvoid Kill(GLvoid) {       // �������� ������
				glDeleteLists(base, 96);        // �������� ���� 96 ������� ����������� ( ����� )
			}
			GLvoid glPrint(const char* fmt, ...) {       // �������� ������� ������� GL
				char    text[256];      // ����� ��� ����� ������
				va_list    ap;          // ��������� �� ������ ����������

				if (fmt == NULL)     // ���� ��� ������
					return;            // ������ �� ������

				va_start(ap, fmt);           // ������ ������ ����������
					vsprintf(text, fmt, ap); // � ��������������� �������� � �������� ����
				va_end(ap);                  // ��������� ���������� � ������

				glPushAttrib(GL_LIST_BIT);      // ����������� ���� ������ ����������� ( ����� )
				glListBase(base - 32);          // ������ ���� ������� � 32 ( ����� )
				glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);// ����� �������� �����������(�����)
				glPopAttrib(); // ������� ����� ������ ����������� ( ����� )
			};
		};
	}
}
