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
			enum class Type {
				BMP, PNG, JPG, TIFF
			};
		public:
			unsigned int width, height;
			unsigned int imageSize;   // = ширина*высота*3
			// Сами RGB данные
			Type type;

			unsigned char* data;
			~Image() {
				free(data);
			}
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
			friend class Material;
			enum class Type {
				Diffuse, Normal, Specular, Roughness
			};
			enum class Filter {
				NEAREST = GL_NEAREST, LINEAR = GL_LINEAR, NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST, 
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
			};
		private:
			bool isGenerate = false;
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

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLuint)filter);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLuint)filter);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);

				glGenerateMipmap(GL_TEXTURE_2D);

				//glBindTexture(GL_TEXTURE_2D, 0);

				//std::cout << "New texture has been generated; id = " << textureID << std::endl;

				delete image;

				this->id = textureID;

				isGenerate = true;
			}
		public:
			Texture(Filter filter = Filter::NEAREST) : filter(filter), id(0), path(""), image(nullptr), type(Type::Diffuse), isGenerate(false) {
	
			}
			~Texture() {
				path.clear();
				id = 0;
			}
		public:
			GLuint id;
			Type type;
			Filter filter;
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
			Texture* LoadTexture(const char* file, Texture::Type type_texture = Texture::Type::Diffuse, Texture::Filter filter = Texture::Filter::NEAREST);
		};

		class Material {
			friend class Model;
		private:
			bool isGenerate = false;
			void Generate() {
				if (diffuse)  if (!diffuse->isGenerate)  diffuse->Generate();
				if (normal)   if (!normal->isGenerate)   normal->Generate();
				if (specular) if (!specular->isGenerate) specular->Generate();
				isGenerate = true;
			}
		public:
			Material(Texture* diffuse) : diffuse(diffuse), isGenerate(false) { };
			Material(Texture* diffuse, Texture* normal) : diffuse(diffuse), normal(normal), isGenerate(false) { };
			~Material() { 
				diffuse = nullptr;
				normal = nullptr;
				specular = nullptr;
			};
		public:
			Texture* diffuse  = nullptr;
			Texture* normal	  = nullptr;
			Texture* specular = nullptr;
		};
	}
}