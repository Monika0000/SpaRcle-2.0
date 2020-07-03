#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Texture.h"
#include <Debug.h>
#include "Shader.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		TextureManager::TextureManager(Debug* debug) {
			if (debug) { 
				this->debug = debug; 
				this->debug->Graph("Texture manager has been created!");
			}
			else Debug::InternalError("TextureManager : debug is nullptr!");
		}
		void TextureManager::Close() {

		}

		BMP* TextureManager::LoadBMP(const char* path) {
			BMP* bmp = new BMP();

			FILE* file = nullptr; 
			fopen_s(&file, path, "rb");

			if (!file) { 
				debug->Error("LoadBMP() : Image could not be opened!\n\tPath : "+ std::string(path)); 
				Sleep(1000);
				return nullptr; 
			}

			if (fread(bmp->header, 1, 54, file) != 54) { // У нас проблемы, если не смогли прочитать 54 байта
				debug->Error("LoadBMP() : Not a correct BMP file!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}

			if (bmp->header[0] != 'B' || bmp->header[1] != 'M') {
				debug->Error("LoadBMP() : Not a correct BMP file!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}

			// Читаем int из массива байтов
			bmp->dataPos = *(int*)&(bmp->header[0x0A]);
			bmp->imageSize = *(int*)&(bmp->header[0x22]);
			bmp->width = *(int*)&(bmp->header[0x12]);
			bmp->height = *(int*)&(bmp->header[0x16]);
			bmp->type = Image::Type::BMP;

			if (bmp->imageSize == 0) bmp->imageSize = bmp->width * bmp->height * 3; // 3 : Один байт на каждую Red, Green, Blue компоненты
			if (bmp->dataPos == 0)	 bmp->dataPos = 54; // Тут заканчивается заголовок, и по идее, должны начаться данные

			bmp->data = new unsigned char[bmp->imageSize]; // Создаем буфер

			fread(bmp->data, 1, bmp->imageSize, file); // Читаем данные из файла в буфер
			fclose(file);					 //Теперь все данные в памяти, и можно закрыть файл

			return bmp;
		}
		Texture* TextureManager::LoadTexture(const char* file, Texture::Type type_texture, Texture::Filter filter) {
			auto find = Textures.find(file);
			if (find != Textures.end())
				return find->second;

			/*
			SOIL_load_OGL_texture(
				file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			texture_number++; // The counter of the current texture is increased
			*/

			Texture* texture = new Texture();
			BMP* bmp = LoadBMP(file);
			if (!bmp) {
				debug->Error("Failed loading texture!");
				Sleep(1000);
				return nullptr;
			}

			//?=====================================

			// Создаем одну OpenGL текстуру

			/*
			// Биндим текстуру, и теперь все функции по работе с текстурами будут работать с этой
			glBindTexture(GL_TEXTURE_2D, textureID);
			// Отправляем картинку в OpenGL текстуру
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->width, bmp->height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			*/

			texture->id = 0;
			texture->path = file;
			texture->image = bmp;
			texture->type = type_texture;
			texture->filter = filter;

			Textures.insert(std::make_pair(file, texture));

			//?=====================================

			//delete bmp;
			return texture; 
		}
	}
}