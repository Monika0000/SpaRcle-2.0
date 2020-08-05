#pragma once
#include <Vectors.h>
#include <Interfaces.h>
#include <string>
#include <Model.h>
#include <Debug.h>
//#include <Light.h>

namespace SpaRcle {
	namespace Graphics {
		class Light;
		class PointLight;
	}
	namespace Engine {
		using namespace Helper;
		using namespace Graphics;

		class GameObject;
		class SREngine;
		class World;

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

			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void SetScale(float x, float y, float z);

			void Rotate(glm::vec3 val);
			void Rotate(float x, float y, float z);
			void Move(glm::vec3 dir);
			void Move(float x, float y, float z);
		public:
			glm::vec3 position = { 0,0,0 };
			glm::vec3 rotation = { 0,0,0 };
			glm::vec3 scale    = { 0,0,0 };
		};

		class GameObject {
			friend class SREngine;
			friend class World;
		private:
			GameObject(SREngine* engine, std::string name = "New game object");
			~GameObject() {  };
		private:
			GameObject* Parent = nullptr;
			std::vector<GameObject*> Childs;

			SREngine* engine = nullptr;
			Debug*	debug	 = nullptr;
			Render* render   = nullptr;
			bool enabled     = true;
			bool canAiming   = false;
		public:
			std::string name;
			Transform   transform;	
			Model*		model = nullptr;
		private:
			Light*		light = nullptr;
		public:
			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void SetScale(float x, float y, float z);

			void Move(float x, float y, float z);
			void Move(glm::vec3 dir);

			void Rotate(float x, float y, float z);
		public:
			void SetAimingEnabled(bool val);
			void SetModel(Model* model);
			void SetActive(bool enabled);

			template <typename T> T GetComponent();
			template <typename T> void AddComponent(T component);
		};

		template<typename T> inline T GameObject::GetComponent() {
			if (std::is_same<T, Model*>::value) {
				if (model) return (T)model;
				else {
					debug->Error("GameObject::GetComponent<Model*>() : this is not contains \"Model*\"!");
					Sleep(1000);
					//return (Model*)nullptr;
					return (T)nullptr;
				}
			}
			else {
				debug->Error("GameObject::GetComponent() : unknow type \"" + std::string(typeid(T).name()) + "\"!");
				Sleep(1000);
				return T();
			}
		}
		template<typename T> inline void GameObject::AddComponent(T component) {
			if (std::is_same<T, Model*>::value) {
				this->model = (Model*)component;
			} else if (std::is_same<T, PointLight*>::value) {
				this->light = (PointLight*)component;
			} else {
				debug->Error("GameObject::AddComponent() : unknow type \"" + std::string(typeid(T).name()) + "\"!");
				Sleep(500);
			}
		}
	}
}

