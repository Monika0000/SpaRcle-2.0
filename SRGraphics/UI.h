#pragma once
#include "Font.h"
#include <Vector3.h>
#include "Vectors.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		struct UI {
		public:
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
		};
	}
}