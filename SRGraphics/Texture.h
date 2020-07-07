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
#include <Debug.h>
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
				BMP, PNG, JPG, TIFF, TGA, UNKNOWN
			};
		public:
			unsigned int width = 0, height = 0, channels = 0;
			unsigned int imageSize = 0;   // = ширина*высота*3
			// Сами RGB данные
			Type type = Type::UNKNOWN;
			bool alpha = false;

			unsigned char* data = nullptr;
			~Image() {
				free(data);
			}
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
				GLuint textureID = SOIL_create_OGL_texture(image->data, image->width, image->height, image->channels, 0,
					SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS);
				glBindTexture(GL_TEXTURE_2D, textureID);


				GLuint texParam = GL_CLAMP_TO_BORDER; // GL_REPEAT, GL_CLAMP_TO_BORDER
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texParam);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texParam);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLuint)filter);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLuint)filter);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				/*
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

				switch (image->type) {
				case Image::Type::BMP: {
					glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);
					glGenerateMipmap(GL_TEXTURE_2D);
					break;
				}
				case Image::Type::PNG: {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
					glGenerateMipmap(GL_TEXTURE_2D);
					break;
				}
				case Image::Type::TGA: {
					gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->width, image->height, 
						GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->data);
					break;
				}
				default:
					break;
				}
				//!if(Alpha)
				//!	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
				//!else
				//!	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->width, image->height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->data);

				//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->width, image->height,
				//	GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->data);

				//!glGenerateMipmap(GL_TEXTURE_2D);
				*/

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
			bool Alpha = false;
			GLuint id;
			Type type;
			Filter filter;
			std::string path;
			Image* image;
		};
		class TextureManager {
			// TGA file header structure. This *must* be byte aligned.
			struct TgaHeader
			{
				BYTE idLength;
				BYTE colormapType;
				BYTE imageType;
				WORD firstEntryIndex;
				WORD colormapLength;
				BYTE colormapEntrySize;
				WORD xOrigin;
				WORD yOrigin;
				WORD width;
				WORD height;
				BYTE pixelDepth;
				BYTE imageDescriptor;
			};
		private:
			std::map<std::string, Texture*> Textures;
		private:
			Debug* debug;
		public:
			TextureManager(Debug* debug);
			void Close();
		public:
			Image* LoadBMP(const char* path);
			Image* LoadPNG(const char* path);
			Image* LoadTGA(const char* path);

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
			Material(Texture* diffuse) : isGenerate(false) {
				if (!diffuse) {
					Debug::InternalWarning("new Material(Texture* diffuse) : diffuse is nullptr!");
					this->diffuse = nullptr;
				}
				else
					this->diffuse = diffuse;
				this->normal = nullptr;
				this->specular = nullptr;
			};
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