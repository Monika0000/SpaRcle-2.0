#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <iostream>
//#include <GL\glew.h>

//#include <GL\glut.h>
//#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#pragma comment(lib, "SOIL.lib")

namespace SpaRcle {
	namespace Helper {
		class Debug;
	}

	using namespace Helper;

	namespace Graphics {
		struct Texture {
		public:
			Texture(const unsigned long long number) : number(number) {

			}
			const unsigned long long number;
		};


		class TextureManager {
		private:
			Debug* debug;
			static unsigned long long texture_number;
		public:
			TextureManager(Debug* debug);
			void Close();
		public:
			static unsigned long long LoadTexture(const char* file);
		};
	}
}