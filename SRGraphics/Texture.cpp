#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Texture.h"
#include <Debug.h>
#include "Shader.h"
#include "SRString.h"
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		TextureManager::TextureManager(Debug* debug, SRGraphics* graph) : IResourceManager(debug, graph) {
			if (debug) {
				this->debug->Graph("Texture manager has been created!");
			}
			else Debug::InternalError("TextureManager : debug is nullptr!");
		}
		bool TextureManager::Close() {
			return 1;
		}

		Image* TextureManager::LoadBMP(const char* path) {
			int width = 0;
			int height = 0;
			int channels = 0;

			unsigned char* image = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);
			Image* bmp = new Image();
			bmp->alpha = false;
			bmp->data = image;
			bmp->type = Image::Type::BMP;
			bmp->height = height;
			bmp->width = width;
			bmp->channels = channels;
			bmp->imageSize = width * height;

			/*
			FILE* file = nullptr;
			fopen_s(&file, path, "rb");

			if (!file) {
				debug->Error("LoadBMP() : Image could not be opened!\n\tPath : "+ std::string(path));
				Sleep(1000);
				return nullptr;
			}

			unsigned char header[54]; // каждый BMP файл начинается с 54байтного заголовка
			unsigned int dataPos;	  // Позиция в файле где сами данные начинаются

			if (fread(header, 1, 54, file) != 54) { // У нас проблемы, если не смогли прочитать 54 байта
				debug->Error("LoadBMP() : Not a correct BMP file!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}

			if (header[0] != 'B' || header[1] != 'M') {
				debug->Error("LoadBMP() : Not a correct BMP file!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}

			// Читаем int из массива байтов
			dataPos = *(int*)&(header[0x0A]);
			bmp->imageSize = *(int*)&(header[0x22]);
			bmp->width = *(int*)&(header[0x12]);
			bmp->height = *(int*)&(header[0x16]);
			bmp->type = Image::Type::BMP;
			bmp->channels = 3;

			if (bmp->imageSize == 0) bmp->imageSize = bmp->width * bmp->height * 3; // 3 : Один байт на каждую Red, Green, Blue компоненты
			if (dataPos == 0)		 dataPos = 54; // Тут заканчивается заголовок, и по идее, должны начаться данные

			bmp->data = new unsigned char[bmp->imageSize]; // Создаем буфер

			fread(bmp->data, 1, bmp->imageSize, file); // Читаем данные из файла в буфер
			fclose(file);					 //Теперь все данные в памяти, и можно закрыть файл*/

			return bmp;
		}
		Image* TextureManager::LoadTIFF(const char* path) {
			int width = 0;
			int height = 0;
			int channels = 0;

			unsigned char* image = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);

			if (!image)
				debug->Error("TextureManager::LoadTIFF() : " + std::string(SOIL_last_result()) + "\n\tPath : " + std::string(path));

			Image* png = new Image();
			png->alpha = true;
			png->data = image;
			png->type = Image::Type::TIFF;
			png->height = height;
			png->width = width;
			png->channels = channels;
			png->imageSize = width * height;

			return png;
		}
		Image* TextureManager::LoadPNG(const char* path) {
			int width = 0;
			int height = 0;
			int channels = 0;
			 
			unsigned char* image = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);

			if(!image)
				debug->Error("TextureManager::LoadPNG() : " + std::string(SOIL_last_result()) + "\n\tPath : " + std::string(path));

			Image* png = new Image();
			png->alpha = true;
			png->data = image;
			png->type = Image::Type::PNG;
			png->height = height;
			png->width = width;
			png->channels = channels;
			png->imageSize = width * height;

			return png;
		}
		Image* TextureManager::LoadTGA(const char* path) {
			/*
			HANDLE hFile = CreateFile(String::CharsToLPWSTR(path), FILE_READ_DATA, FILE_SHARE_READ, 0,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

			if (hFile == INVALID_HANDLE_VALUE) {
				debug->Error("LoadTGA() : INVALID_HANDLE_VALUE!\n\tPath : " + std::string(path));
				return nullptr;
			}

			DWORD dwBytesRead = 0;
			TgaHeader header = { 0 };

			// Read in the TGA file header.
			ReadFile(hFile, &header, sizeof(header), &dwBytesRead, 0);

			// Skip over the TGA file's ID field.
			if (header.idLength > 0)
				SetFilePointer(hFile, header.idLength, 0, FILE_CURRENT);

			// Check for compatible color depth.
			if (!(header.pixelDepth == 32 || header.pixelDepth == 24 || header.pixelDepth == 8))
			{
				CloseHandle(hFile);
				debug->Error("LoadTGA() : Incorrect depth!\n\tPath : " + std::string(path));
				return nullptr;
			}

			// Only support uncompressed true color and grayscale images.
			if (!(header.imageType == 0x02 || header.imageType == 0x01))
			{
				CloseHandle(hFile);
				debug->Error("LoadTGA() : Incorrect type!\n\tPath : " + std::string(path));
				return nullptr;
			}

			// Read the TGA file into a temporary buffer.

			DWORD dwPitch = header.width * (header.pixelDepth / 8);
			DWORD dwBufferSize = dwPitch * header.height;
			std::vector<BYTE> buffer(dwBufferSize);

			// Load the pixel data from the TGA file. Flip image if it's not top down.
			if ((header.imageDescriptor & 0x30) == 0x20)
			{
				// TGA image is stored top down in file.
				ReadFile(hFile, &buffer[0], dwBufferSize, &dwBytesRead, 0);
			}
			else
			{
				// TGA image is stored bottom up in file. Need to flip it.

				BYTE* pRow = 0;

				for (int i = 0; i < header.height; ++i)
				{
					pRow = &buffer[(header.height - 1 - i) * dwPitch];
					ReadFile(hFile, pRow, dwPitch, &dwBytesRead, 0);
				}
			}

			CloseHandle(hFile);

			//if (!create(header.width, header.height))
			//	return false;

			//setPixels(&buffer[0], header.width, header.height, header.pixelDepth / 8);*/
			return nullptr;
		}
		Image* TextureManager::LoadJPG(const char* path) {
			int width = 0;
			int height = 0;
			int channels = 0;

			unsigned char* image = SOIL_load_image(path, &width, &height, &channels, SOIL_LOAD_AUTO);
			Image* jpg = new Image();
			jpg->alpha = false;
			jpg->data = image;
			jpg->type = Image::Type::JPG;
			jpg->height = height;
			jpg->width = width;
			jpg->channels = channels;
			jpg->imageSize = width * height;

			return jpg;
		}
		Image* TextureManager::LoadImg(const char* file, bool log) {
			if(log) debug->Log("Loading image : \"" + std::string(file)+"\"");

			Image* image = nullptr;
			std::string extension = Helper::String::BackReadToChar(file, '.');
			if (extension == "bmp")
				image = LoadBMP(file);
			else if (extension == "png")
				image = LoadPNG(file);
			else if (extension == "tga")
				image = LoadTGA(file);
			else if (extension == "jpg")
				image = LoadJPG(file);
			else if (extension == "tif" || extension == "tiff")
				image = LoadTIFF(file);
			else {
				debug->Error("TextureManager::LoadImage() : Unknown image format!\n\tPath : " + std::string(file) + "\n\tExtension : " + extension);
				Sleep(1000);
				return nullptr;
			}
			if (!image || !image->data) {
				if(!image)
					debug->Error("TextureManager::LoadImage() : Failed loading image!\n\tPath : " + std::string(file)
						+ "\n\tImage : " + std::to_string((size_t)image) + "\n\tExtension : "+ extension);
				else
					debug->Error("TextureManager::LoadImage() : Failed loading image!\n\tPath : " + std::string(file)
						+ "\n\tImage : " + std::to_string((size_t)image) + "\n\tData : " 
						+ std::to_string((size_t)image->data) + "\n\tExtension : " + extension);

				Sleep(1000);
				return nullptr;
			}
			return image;
		}

		Skybox* TextureManager::LoadSkybox(const char* file_base, Image::Type format) {
			static const std::string files[6] { "_right", "_left", "_top", "_bottom", "_front", "_back" };
			
			debug->Log("Loading skybox : " + graph->GetResourcesFolder() + "\\" + std::string(file_base) + "\\skybox");

			Skybox* skybox = new Skybox();	

			for (unsigned int i = 0; i < 6; i++){
				skybox->sides[i] = LoadImg((graph->GetResourcesFolder() + "\\" + std::string(file_base) + "\\skybox" + files[i] + Image::TypeToStr(format)).c_str());
			}

			return skybox;
		}
		Texture* TextureManager::LoadTexture(const char* file, bool log, Texture::Type type_texture, Texture::Filter filter) {
			std::string path = graph->GetResourcesFolder() + "\\Textures\\" + std::string(file);

			//path = String::ReplaceAll(path, "\\\\", "\\");
			//path = String::ReplaceAll(path, "/", "\\");
			path = String::MakePath(path);

			auto find = Textures.find(path);
			if (find != Textures.end())
				return find->second;

			Image* image = this->LoadImg(path.c_str(), log);

			if (!image) {
				debug->Error("TextureManager : Failed loading texture!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}
			if (!image->data) {
				debug->Error("TextureManager : Texture data is nullptr!\n\tPath : " + std::string(path));
				Sleep(1000);
				return nullptr;
			}
			/*
			SOIL_load_OGL_texture(
				file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			texture_number++; // The counter of the current texture is increased
			*/

			Texture* texture = new Texture();


			//?=====================================

			texture->id = 0;
			texture->path = file;
			texture->image = image;
			texture->type = type_texture;
			texture->filter = filter;
			texture->Alpha = image->alpha;

			Textures.insert(std::make_pair(path, texture));

			//?=====================================

			//delete bmp;
			return texture;
		}

		void Skybox::Draw(Shader* skybox_shader) {
			if (!isGenerated) Generate();
			else {
				glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
				skybox_shader->Use();
				// ... задание видовой и проекционной матриц
				glBindVertexArray(VAO);
				glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemap);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glDepthFunc(GL_LESS); // set depth function back to default
			}
		}
	}
}