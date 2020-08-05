#pragma once
#include <glm/glm.hpp>

namespace SpaRcle {
	namespace Graphics {
		struct Light {
			//float intensity = 1.f;
			//float radius    = 1.f;
			//glm::vec3 color = { 1.f, 1.f, 1.f }; // white
			//glm::vec3 pos   = { 0.f, 0.f, 0.f };
			//glm::vec3 dir   = { 0.f, 0.f, 0.f };
			//bool shandows   = true;

			glm::vec3 position;

			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;

			float constant;
			float linear;
			float quadratic;
		};

		class DirectionalLight : public Light {

		};

		class PointLight : public Light {
		public:
			PointLight() {
				this->position = { 0,0,0 };

				this->ambient = { 0.2f, 0.2f, 0.2f };
				this->diffuse = { 0.5f, 0.5f, 0.5f };
				this->specular = { 1.0f, 1.0f, 1.0f };
				this->constant = 1.0f;
				this->linear = 0.09f;	
				this->quadratic = 0.032f;
			};
			~PointLight() {};
		};

		
		class SpotLight : public Light {

		};

		class AreaLight : public Light {

		};
	}
}

