#include "pch.h"
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	namespace Graphics {
		Material* MaterialManager::LoadMaterial(const char* path) {
			std::string file = graph->GetResourcesFolder() + "\\Materials\\" + std::string(path) + ".mat";

			file = String::ReplaceAll(file, "\\\\", "\\");
			file = String::ReplaceAll(file, "/", "\\");

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

			float r, g, b, a; r = g = b = a = 1;

			bool use_light = true;

			//, Texture::Type::Diffuse, Texture::Filter::NEAREST_MIPMAP_LINEAR

			while (fscanf(pFile, "%s", buffer) != EOF) {
				switch (buffer[0]) {
				case '#': {
					switch (buffer[1]) {
					case 'c': {
						char buf[50];
						fgets(buf, sizeof buf, pFile);

						std::string str = buf; 
						auto colors = String::FixedSplit(str.substr(1), " ", 4);
						r = std::stof(colors[0]);
						g = std::stof(colors[1]);
						b = std::stof(colors[2]);
						a = std::stof(colors[3]);

						break;
					}
					case 'u': {
						if (std::string(buffer).substr(1) == "use_light") {
							fscanf(pFile, "%s", buffer);
							if (std::string(buffer) == "false") use_light = false; else use_light = true;
						} else 
							fscanf(pFile, "%s", buffer);
						break;
					}
					case 'd': {
						fscanf(pFile, "%s", buffer);
						diffuse = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, false, 
							Texture::Type::Diffuse, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 'n': {
						fscanf(pFile, "%s", buffer);
						normal = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, false, 
							Texture::Type::Normal, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 's': {
						fscanf(pFile, "%s", buffer);
						specular = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, false, 
							Texture::Type::Specular, Texture::Filter::NEAREST_MIPMAP_LINEAR);
						break;
					}
					case 'g': {
						fscanf(pFile, "%s", buffer);
						glossiness = graph->GetRender()->GetTextureManager()->LoadTexture(buffer, false, 
							Texture::Type::Glossiness, Texture::Filter::NEAREST_MIPMAP_LINEAR);
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
			Material* mat = new Material(diffuse, normal, specular, glossiness, { r, g, b, a }, use_light);
			//std::cout << r << " " << g << " " << b << " " << a << "\n";
			//std::cout << use_light << "\n";

			Materials.insert(std::make_pair(file, mat));
			fclose(pFile);
			return mat;
		}
	}
}
