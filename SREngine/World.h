#pragma once
#include <Debug.h>
#include <SRGraphics.h>
#include "GameObject.h"

namespace SpaRcle {
	namespace Engine {
		using namespace Graphics;
		using namespace Helper;

		class SREngine;

		class World {
		public:
			std::map<std::string, GameObject*> gameObjects = std::map<std::string, GameObject*>();
		public:
			Debug*     debug = nullptr;
			Render*   render = nullptr;
			SREngine* engine = nullptr;
		private:
			std::string MakeCopyName(std::string name);
		private:
			GameObject* Arrows = nullptr;
		public:
			World(Debug* debug, SREngine* engine, GameObject* Arrows);
			~World() {

			}
		public:
			void RegisterGameObject(GameObject* game);

			GameObject* Find(std::string name) {
				auto find = gameObjects.find(name);
				if (find == gameObjects.end())
					return nullptr;
				else return find->second;
			}
			GameObject* Find(Model* model) {
				for (std::map<std::string, GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
					if (it->second->model == model)
						return it->second;
				}
				return nullptr;
			}

			bool Rename(GameObject* object, std::string name);
			bool Rename(std::string oldName, std::string newName);

			GameObject* Instantiate(std::string name, Model* model);
			GameObject* Instantiate(std::string name);

			bool Destroy(std::string name);
			bool Destroy(GameObject* object);
		};
	}
}

