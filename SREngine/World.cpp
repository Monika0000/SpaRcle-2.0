#include "pch.h"
#include "World.h"
#include "SREngine.h"
#include <Model.h>

namespace SpaRcle {
	namespace Engine {
		std::string World::MakeCopyName(std::string name)
		{
			return name + " (Copy)";
		}
		World::World(Debug* debug, SREngine* engine, GameObject* Arrows) : debug(debug), engine(engine), Arrows(Arrows) {
			this->render = engine->GetRender();
		}
		void World::RegisterGameObject(GameObject* game) {
			ret:
			auto find = this->gameObjects.find(game->name);
			if (find == gameObjects.end())
				gameObjects.insert(std::make_pair(game->name, game));
			else {
				game->name += " (Copy)";
				goto ret;
			}
		}
		bool World::Rename(GameObject* object, std::string name) {
			return false;
		}
		bool World::Rename(std::string oldName, std::string newName) {
			return false;
		}

		GameObject* World::Instantiate(std::string name, Model* model) {
		ret:
			auto find = this->gameObjects.find(name);
			if (find != gameObjects.end()) {
				name = MakeCopyName(name);
				goto ret;
			}

			debug->Log("World::Instantiate() create new game object \""+name+"\", Model is " + std::to_string((size_t)model));

			GameObject * gm = new GameObject(engine, name);

			gameObjects.insert(std::make_pair(name, gm));
			gm->SetModel(model);

			return gm;
		}
		GameObject* World::Instantiate(std::string name) {
			ret:
			auto find = this->gameObjects.find(name);
			if (find != gameObjects.end()) {
				name = MakeCopyName(name);
				goto ret;
			}

			debug->Log("World::Instantiate() create new game object \"" + name + "\"");

			GameObject* gm = new GameObject(engine, name);

			gameObjects.insert(std::make_pair(name, gm));

			return gm;
		}

		bool World::Destroy(std::string name) {
			return false;
		}
		bool World::Destroy(GameObject* object) {
			debug->Log("World : destroy " + object->name);

			if (object->model)
				object->model->Destroy();

			this->gameObjects.erase(object->name);

			delete object;
			object = nullptr;

			return true;
		}
	}
}