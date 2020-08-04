#include "pch.h"
#include "GameObject.h"
#include "Render.h"
#include "SREngine.h"
#include <Windows.h>
#include <Model.h>

namespace SpaRcle {
	using namespace Graphics;
	namespace Engine {

		GameObject::GameObject(SREngine* engine, std::string name) : transform(this) {
			this->engine = engine;

			this->render = engine->GetRender();
			this->debug  = engine->GetDebug();
			this->name	 = name;
			//this->transform = Transform(this);
			this->model  = nullptr;
		};

		void GameObject::SetPosition(float x, float y, float z) {
			for (auto g : Childs) g->SetPosition(x, y, z);
			transform.SetPosition(x, y, z);
		}
		void GameObject::SetRotation(float x, float y, float z) {
			for (auto g : Childs) g->SetRotation(x, y, z);
			transform.SetRotation(x, y, z);
		}
		void GameObject::SetScale(float x, float y, float z) {
			for (auto g : Childs) g->SetScale(x, y, z);
			transform.SetScale(x, y, z);
		}

		void GameObject::Move(float x, float y, float z) {
			for (auto g : Childs)
				g->Move(x, y, z);
			transform.Move(x, y, z);
		}
		void GameObject::Move(glm::vec3 dir) {
			for (auto g : Childs)
				g->Move(dir);
			transform.Move(dir);
		}

		void GameObject::Rotate(float x, float y, float z) {
			for (auto g : Childs)
				g->Rotate(x, y, z);
			transform.Rotate(x, y, z);
		}

		void GameObject::SetAimingEnabled(bool val) {
			if (!canAiming && val) {
				if (model)
					for (auto& m : model->meshes)
						render->AddAimingMesh(m);
				canAiming = true;
			}  else if (canAiming && !val) {
				if (model)
					for (auto& m : model->meshes)
						render->RemoveAimingMesh(m);
				canAiming = false;
			}
		}
		void GameObject::SetModel(Model* model) {
			if (this->model) { this->model->Destroy(); }
			this->model = model;
			this->render->AddModel(model);
		}
		void GameObject::SetActive(bool enabled) {
			if (this->enabled == enabled) return;
			this->enabled = enabled;

			if (model) { 
				model->enabled = enabled;
				SetAimingEnabled(enabled);
			}

			if (this->enabled) {

			}
			else {

			}
		}

		//?=============================================================================

		void Transform::SetPosition(glm::vec3 val) {
			this->position = val;
			if (this->gameObject->model) this->gameObject->model->SetPosition(val);
		}
		void Transform::SetRotation(glm::vec3 val) {
			this->rotation = val;
			if (this->gameObject->model) this->gameObject->model->SetRotation(val);
		}
		void Transform::SetScale(glm::vec3 val) {
			this->scale = val;
			if (this->gameObject->model) this->gameObject->model->SetScale(val);
		}

		void Transform::SetPosition(float x, float y, float z) {
			this->position = { x,y,z };
			if (this->gameObject->model) this->gameObject->model->SetPosition(position);
		}
		void Transform::SetRotation(float x, float y, float z) {
			this->rotation = { x,y,z };
			if (this->gameObject->model) this->gameObject->model->SetRotation(rotation);
		}
		void Transform::SetScale(float x, float y, float z) {
			this->scale = { x,y,z };
			if (this->gameObject->model) this->gameObject->model->SetScale(scale);
		}

		void Transform::Rotate(glm::vec3 val) {
			this->rotation += val;

			//std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

			//std::cout << rotation.x << std::endl;

			if (this->gameObject->model) this->gameObject->model->SetRotation(rotation);
		}
		void Transform::Rotate(float x, float y, float z) {
			this->rotation += glm::vec3{x,y,z};
			if (this->gameObject->model) this->gameObject->model->SetRotation(rotation);
		}

		void Transform::Move(float x, float y, float z) {
			this->position += glm::vec3 {x, y, z};
			if (this->gameObject->model) this->gameObject->model->SetPosition(this->position);
		}
		void Transform::Move(glm::vec3 dir) {
			this->position += dir;
			if (this->gameObject->model) this->gameObject->model->SetPosition(this->position);
		}

		//template <typename T> T GameObject::GetComponent() {
		/*	if (std::is_same<T, Model*>::value) {
				if (model) return model;
				else {
					engine->GetDebug()->Error("GameObject::GetComponent<Model*>() : this is not contains \"Model*\"!");
					Sleep(1000);
					return nullptr;
				}
			}
			else {
				engine->GetDebug()->Error("GameObject::GetComponent<>() : unknow type \"" + typeid(T).name() + "\"!");
				Sleep(1000);
				return nullptr;
			}
			*/
		//}
	}
}