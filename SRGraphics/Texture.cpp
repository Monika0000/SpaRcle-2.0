#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Texture.h"
#include <Debug.h>

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

			return bmp;
		}
		GLuint TextureManager::LoadTexture(const char* file) {
			/*
			SOIL_load_OGL_texture(
				file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			texture_number++; // The counter of the current texture is increased
			*/


			return 0; // Returns the current texture OpenGL ID
		}
	}
}