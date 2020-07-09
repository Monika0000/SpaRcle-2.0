#include "pch.h"
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	namespace Graphics {
		Material* MaterialManager::LoadMaterial(const char* path) {
			std::string file = graph->GetResourcesFolder() + "\\" + std::string(path);

			auto find = Materials.find(file);
			if (find != Materials.end())
				return find->second;

			debug->Log("Loading material : " + std::string(file));

			FILE* pFile = fopen(file.c_str(), "r");
			if (!pFile) {
				debug->Error("LoadMaterial() : Failed loading material!\n\tPath : " + std::string(file));
				Sleep(1000);
				return nullptr;
			}

			char buffer[256] = { 0 };

			Texture* diffuse    = nullptr;
			Texture* normal     = nullptr;
			Texture* specular   = nullptr;
			Texture* glossiness = nullptr;

			//, Texture::Type::Diffuse, Texture::Filter::NEAREST_MIPMAP_LINEAR

			while (fscanf(pFile, "%s", buffer) != EOF) {
				switch (buffer[0]) {
				case '#': {
					switch (buffer[1]) {
					case 'd': {
						fscanf(pFile, "%s", buffer);
						diffuse = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, Texture::Type::Diffuse, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 'n': {
						fscanf(pFile, "%s", buffer);
						normal = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, Texture::Type::Normal, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 's': {
						fscanf(pFile, "%s", buffer);
						specular = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, Texture::Type::Specular, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 'g': {
						fscanf(pFile, "%s", buffer);
						glossiness = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, Texture::Type::Glossiness, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					default:
						fgets(buffer, sizeof(buffer), pFile);
						break;
					}
				}
				default:
					fgets(buffer, sizeof(buffer), pFile);
					break;
				}
			}

			Material* mat = new Material(diffuse, normal, specular, glossiness);

			Materials.insert(std::make_pair(file, mat));
			fclose(pFile);
			return mat;
		}
	}
}
