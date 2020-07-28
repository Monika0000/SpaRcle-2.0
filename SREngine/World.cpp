#include "pch.h"
#include "World.h"

namespace SpaRcle {
	namespace Engine {
		bool World::Rename(GameObject* object, std::string name) {
			return false;
		}
		bool World::Rename(std::string oldName, std::string newName) {
			return false;
		}

		GameObject* World::Instantiate(std::string name, Model* model) {
			auto find = this->gameObjects.find(name);
			if (find != gameObjects.end()) {
				debug->Error("World::Instantiate() : object \"" + name + "\" already exists!");
				Sleep(1000);
				return nullptr; 
			}

			debug->Log("World::Instantiate() create new game object \""+name+"\"");

			//GameObject* gameObject = new GameObject()

			return nullptr;
		}

		bool World::Destroy(std::string name) {
			return false;
		}
		bool World::Destroy(GameObject* object) {
			return false;
		}
	}
}