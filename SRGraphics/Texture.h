#pragma once
#define GLEW_STATIC
#define NOMINMAX

//#pragma comment(lib,"SOIL.lib")

#include "Resource.h"

namespace SpaRcle {
	namespace Helper {
		class Debug;
	}

	using namespace Helper;

	namespace Graphics {
		class Shader;
		class Model;
		class Mesh;
		class TextureManager;
		class Camera;
		class SRGraphics;

		struct Image {
			enum class Type {
				BMP, PNG, JPG, TIFF, TGA, UNKNOWN
			};
		public:
			static const std::string TypeToStr(Type type) noexcept {
				switch (type){
				case Image::Type::BMP:
					return ".bmp";
				case Image::Type::PNG:
					return ".png";
				case Image::Type::JPG:
					return ".jpg";
				case Image::Type::TIFF:
					return ".tiff";
				case Image::Type::TGA:
					return ".tga";
				case Image::Type::UNKNOWN:
					return ".unknown";
				default:
					return ".default";
				}
			}
		public:
			unsigned int width = 0, height = 0, channels = 0;
			unsigned int imageSize = 0;   // = ширина*высота*3
			// Сами RGB данные
			Type type = Type::UNKNOWN;
			bool alpha = false;

			unsigned char* data = nullptr;
			~Image() {
				width = 0;
				height = 0;
				channels = 0;
				type = Type::UNKNOWN;
				SOIL_free_image_data(data);
				//free(data);
			}
		};

		struct Texture {
			friend class Model;
			friend class Material;
			enum class Type {
				Diffuse, Normal, Specular, Roughness, Glossiness
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

		class Skybox {
			friend class TextureManager;
			const float skyboxVertices[36 * 3] = {
				// positions          
				-10.0f,  10.0f, -10.0f,
				-10.0f, -10.0f, -10.0f,
				 10.0f, -10.0f, -10.0f,
				 10.0f, -10.0f, -10.0f,
				 10.0f,  10.0f, -10.0f,
				-10.0f,  10.0f, -10.0f,

				-10.0f, -10.0f,  10.0f,
				-10.0f, -10.0f, -10.0f,
				-10.0f,  10.0f, -10.0f,
				-10.0f,  10.0f, -10.0f,
				-10.0f,  10.0f,  10.0f,
				-10.0f, -10.0f,  10.0f,

				 10.0f, -10.0f, -10.0f,
				 10.0f, -10.0f,  10.0f,
				 10.0f,  10.0f,  10.0f,
				 10.0f,  10.0f,  10.0f,
				 10.0f,  10.0f, -10.0f,
				 10.0f, -10.0f, -10.0f,

				-10.0f, -10.0f,  10.0f,
				-10.0f,  10.0f,  10.0f,
				 10.0f,  10.0f,  10.0f,
				 10.0f,  10.0f,  10.0f,
				 10.0f, -10.0f,  10.0f,
				-10.0f, -10.0f,  10.0f,

				-10.0f,  10.0f, -10.0f,
				 10.0f,  10.0f, -10.0f,
				 10.0f,  10.0f,  10.0f,
				 10.0f,  10.0f,  10.0f,
				-10.0f,  10.0f,  10.0f,
				-10.0f,  10.0f, -10.0f,

				-10.0f, -10.0f, -10.0f,
				-10.0f, -10.0f,  10.0f,
				 10.0f, -10.0f, -10.0f,
				 10.0f, -10.0f, -10.0f,
				-10.0f, -10.0f,  10.0f,
				 10.0f, -10.0f,  10.0f
			};
		private:
			void Generate() {
				glGenTextures(1, &cubemap);
				glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
				//glDeleteTextures(1, &cubemap);

				for (unsigned int i = 0; i < 6; i++) {
					if (!sides[i]) {
						glDeleteTextures(1, &cubemap);
						return;
					}

					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0, GL_RGB, sides[i]->width, sides[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, sides[i]->data
					);
				}
				for (unsigned int i = 0; i < 6; i++) delete sides[i];

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				
				//?/////////////////////////////////////////////////////////////////////////////////

				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);

				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

				glBindVertexArray(0);

				isGenerated = true;
			}
		private:
			GLuint VAO = 0, VBO = 0;
			Image* sides[6] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
			GLuint cubemap = 0;
			bool isGenerated = false;
		public:
			Skybox() { };
			void Draw(Shader* skybox_shader);
		};

		class TextureManager : public IResourceManager {
			/*
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
			*/
		private:
			std::map<std::string, Texture*> Textures = std::map<std::string, Texture*>();
		public:
			TextureManager(Debug* debug, SRGraphics* graph);
			bool Close() override;
		public:
			Image* LoadBMP(const char* path);
			Image* LoadPNG(const char* path);
			Image* LoadTGA(const char* path);
			Image* LoadJPG(const char* path);

			Image* LoadImage(const char* file, bool log = true);
			Skybox* LoadSkybox(const char* file_base, Image::Type format);
			Texture* LoadTexture(const char* file,
				Texture::Type type_texture = Texture::Type::Diffuse, Texture::Filter filter = Texture::Filter::NEAREST) 
			{
				return LoadTexture(file, true, type_texture, filter);
			}
			Texture* LoadTexture(const char* file, bool log, Texture::Type type_texture = Texture::Type::Diffuse, Texture::Filter filter = Texture::Filter::NEAREST);
		};
	}
}