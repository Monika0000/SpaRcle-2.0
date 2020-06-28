#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <iostream>
#include <GL\glew.h>
#include <map>
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
			GLuint id;
			std::string type;
			std::string path;
		};

		struct BMP {
			unsigned char header[54]; // каждый BMP файл начинается с 54байтного заголовка
			unsigned int dataPos;	  // Позиция в файле где сами данные начинаются
			unsigned int width, height;
			unsigned int imageSize;   // = ширина*высота*3
			// Сами RGB данные
			unsigned char* data;
		};

		class TextureManager {
		private:
			std::map<std::string, BMP*> BMP_Images;
		private:
			Debug* debug;
		public:
			TextureManager(Debug* debug);
			void Close();
		public:
			BMP* LoadBMP(const char* path);
			GLuint LoadTexture(const char* file);
		};
	}
}