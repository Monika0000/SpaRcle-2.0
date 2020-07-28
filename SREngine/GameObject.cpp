#include "pch.h"
#include "GameObject.h"
#include "Render.h"

namespace SpaRcle {
	namespace Engine {
		void GameObject::SetModel(Model* model) {
			if (this->model) { this->model->Destroy(); }
			this->model = model;
			this->render->AddModel(model);
		}
		void GameObject::SetActive(bool enabled) {
			if (this->enabled == enabled) return;
			this->enabled = enabled;

			if (model) model->enabled = enabled;

			if (this->enabled) {

			}
			else {

			}
		}

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

		void Transform::Rotate(glm::vec3 val) {
			this->rotation += val;

			std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

			//std::cout << rotation.x << std::endl;

			if (this->gameObject->model) this->gameObject->model->SetRotation(rotation);
		}
	}
}