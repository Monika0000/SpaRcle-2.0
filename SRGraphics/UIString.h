#pragma once
#include "UI.h"
#include <GL\freeglut_std.h>
#include "Material.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		struct UIString : public UI {
		private:
			char* text;
			unsigned short* t_len;
			unsigned short i;
			color* _color;
		public:
			void SetString(std::string str) {
				if (text) delete[] this->text;
				this->text = String::CopyStringToCharPointer(str.c_str());
				*t_len = strlen(text);
			}
			void Draw() override {
				glColor4f(
					_color->r,
					_color->g,
					_color->b,
					_color->a);

				glRasterPos3f(
					pos->x,
					pos->y,
					size->x);

				for (i = 0; i < *t_len; i++) {
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
				}
			}
		public:
			UIString(
				std::string str, 
				float x_pos, float y_pos, color* _color = NULL,
				float size = 1.f) : UI(x_pos, y_pos, size, size)
			{
				if (!_color)
					this->_color = new color{ 255.f, 255.f, 255.f, 255.f };
				else
					this->_color = _color;
				this->i = 0;
				this->text = String::CopyStringToCharPointer(str.c_str());
				this->t_len = new unsigned short();
				*this->t_len = strlen(text);
			}
			~UIString() {
				if (t_len)  delete   this->t_len;
				if (text)   delete[] this->text;
				if (_color) delete   this->_color;
			}
		};
	}
}
/*
static void RenderString3D(const char* string, Vector3 pos = { 0.f, 0.f, 0.f }, Vector3 size = { 1, 1, 1 },
	void* font = NULL, color const& rgb = color{ 255.f, 255.f, 0.f, 0 });

static GLvoid glPrint(const char* fmt, ...) {                   // Custom GL "Print" Routine
	glTranslatef(0, 0, -.002);
	glColor3f(255, 0, 0);
	glRasterPos2f(1 / 10000, 1 / 10000);

	char        text[256];                              // Holds Our String
	va_list     ap;                                     // Pointer To List Of Arguments
	va_start(ap, fmt);                                  // Parses The String For Variables
	vsprintf(text, fmt, ap);                        // And Converts Symbols To Actual Numbers
	va_end(ap);                                         // Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);                          // Pushes The Display List Bits
	//glListBase(base - 32);                              // Sets The Base Character to 32
	glListBase(32);                              // Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text
	glPopAttrib();                                      // Pops The Display List Bits
};
*/
