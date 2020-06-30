#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <iostream>
#include <GL\glew.h>
#include <map>
//#include <GL\glut.h>
//#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <GL\glaux.h>

#pragma comment(lib, "SOIL.lib")

namespace SpaRcle {
	namespace Helper {
		class Debug;
	}

	using namespace Helper;

	namespace Graphics {
		class Shader;
		class Model;
		
		struct Image {
		public:
			unsigned int width, height;
			unsigned int imageSize;   // = ширина*высота*3
			// Сами RGB данные
			unsigned char* data;
		};
		struct BMP : public Image {
		public:
			BMP() { };
			~BMP() { 
				//delete[] header;
				//delete[] data;
			};
		public:
			unsigned char header[54]; // каждый BMP файл начинается с 54байтного заголовка
			unsigned int dataPos;	  // Позиция в файле где сами данные начинаются
		};
		struct Texture {
			friend class Model;
			enum class Type {
				BMP, PNG, JPG, TIFF
			};
		private:
			bool isGenerate;
			void Generate() {
				GLuint textureID;
				glGenTextures(1, &textureID);

				// Биндим текстуру, и теперь все функции по работе с текстурами будут работать с этой
				glBindTexture(GL_TEXTURE_2D, textureID);

				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				// Отправляем картинку в OpenGL текстуру
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);

				GLuint texParam = GL_CLAMP_TO_BORDER; // GL_REPEAT, GL_CLAMP_TO_BORDER
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);

				glGenerateMipmap(GL_TEXTURE_2D);

				//glBindTexture(GL_TEXTURE_2D, 0);

				//std::cout << "New texture has been generated; id = " << textureID << std::endl;
				
				this->id = textureID;	

				isGenerate = true;
			}
		public:
			GLuint id;
			Type type;
			std::string path;
			Image* image;
		};

		class TextureManager {
		private:
			std::map<std::string, Texture*> Textures;
		private:
			Debug* debug;
		public:
			TextureManager(Debug* debug);
			void Close();
		public:
			BMP* LoadBMP(const char* path);
			Texture* LoadTexture(const char* file);
		};
	}
}