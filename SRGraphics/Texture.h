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
			unsigned char header[54]; // ������ BMP ���� ���������� � 54�������� ���������
			unsigned int dataPos;	  // ������� � ����� ��� ���� ������ ����������
			unsigned int width, height;
			unsigned int imageSize;   // = ������*������*3
			// ���� RGB ������
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