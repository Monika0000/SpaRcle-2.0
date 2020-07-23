#pragma once
#include "Texture.h"
#include "Resource.h"
#include <glm/glm.hpp>

namespace SpaRcle {
	namespace Graphics {
		struct color { float r, g, b, a; };

		class MaterialManager;

		class Material {
			friend class Model;
			friend class MaterialManager;
		private:
			bool isGenerate = false;
			void Generate() {
				if (diffuse)    if (!diffuse->isGenerate)      diffuse->Generate();
				if (normal)     if (!normal->isGenerate)       normal->Generate();
				if (specular)   if (!specular->isGenerate)     specular->Generate();
				if (glossiness) if (!glossiness->isGenerate)   glossiness->Generate();

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

				this->normal     = nullptr;
				this->specular   = nullptr;
				this->glossiness = nullptr;
			};
			Material(Texture* diffuse, Texture* normal) : diffuse(diffuse), normal(normal), isGenerate(false) { 

			};
			Material(
				Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness, 
				glm::vec4 Color = { 1, 1, 1, 1 }, bool use_light = true)
				:
				diffuse(diffuse), normal(normal), specular(specular), glossiness(glossiness), 
				isGenerate(false), Color(Color), use_light(use_light)
			{ 

			};
			~Material() {
				diffuse    = nullptr;
				normal     = nullptr;
				specular   = nullptr;
				glossiness = nullptr;
			};
		public:
			glm::vec4 Color     = { 1, 1, 1, 1 };
			bool use_light		= true;
		public:
			Texture* diffuse    = nullptr;
			Texture* normal     = nullptr;
			Texture* specular   = nullptr;
			Texture* glossiness = nullptr;
		};

		class MaterialManager : public IResourceManager {
		private:
			std::map<std::string, Material*> Materials = std::map<std::string, Material*>();
		public:
			Material* LoadMaterial(const char* file);
			bool SaveMaterial(const char* file, Material* mat) { return false; }
			MaterialManager(Debug* debug, SRGraphics* graph) : IResourceManager(debug, graph) {

			};
			bool Close() override {
				return false;
			};
		};
	}
}