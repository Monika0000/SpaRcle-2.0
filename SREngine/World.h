#pragma once
#include <Debug.h>
#include <SRGraphics.h>
#include "GameObject.h"

namespace SpaRcle {
	namespace Engine {
		using namespace Graphics;
		using namespace Helper;

		class World {
		public:
			std::map<std::string, GameObject*> gameObjects = std::map<std::string, GameObject*>();
		public:
			Debug* debug;
			Render* render;
		private:
			GameObject* Arrows = nullptr;
		public:
			World(Debug*debug, Render* render, GameObject* Arrows) : debug(debug), render(render), Arrows(Arrows) {

			}
			~World() {

			}
		public:
			bool Rename(GameObject* object, std::string name);
			bool Rename(std::string oldName, std::string newName);

			GameObject* Instantiate(std::string name, Model* model);

			bool Destroy(std::string name);
			bool Destroy(GameObject* object);
		};
	}
}
