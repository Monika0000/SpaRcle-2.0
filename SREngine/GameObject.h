#pragma once
#include <Vectors.h>
#include <Interfaces.h>
#include <string>
#include <Model.h>

namespace SpaRcle {
	namespace Engine {
		using namespace Helper;
		using namespace Graphics;

		class GameObject;

		class Transform : public IComponent {
		private:
			GameObject* gameObject;
		public:
			Transform(GameObject* gameObject) {
				this->gameObject = gameObject;
				this->position  = { 0, 0, 0 };
				this->rotation  = { 0, 0, 0 };
				this->scale     = { 1, 1, 1 };
			}
			~Transform() {

			}
		public:
			void SetPosition(glm::vec3 val);
			void SetRotation(glm::vec3 val);
			void SetScale   (glm::vec3 val);

			void Rotate(glm::vec3 val);
			//void Move(glm::vec3 dir) {  };
		public:
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
		};

		class GameObject {
			friend class SREngine;
		private:
			GameObject(Render* render, std::string name = "New game object") : transform(this) {
				this->render    = render;
				this->name		= name;
				//this->transform = Transform(this);
				this->model		= nullptr;
			};
			~GameObject() {  };
		private:
			Render* render = nullptr;
			bool enabled = true;
		public:
			std::string name;
			Transform   transform;	
			Model*		model;
		public:
			void SetModel(Model* model);
			void SetActive(bool enabled);

			template <typename T> T GetComponent() {

			}
		};
	}
}

