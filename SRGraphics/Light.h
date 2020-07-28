#pragma once
#include <glm/glm.hpp>

namespace SpaRcle {
	namespace Graphics {
		class Light {
			float intensity = 1.f;
			float radius    = 1.f;
			glm::vec3 color = { 1.f, 1.f, 1.f }; // white
			glm::vec3 pos   = { 0.f, 0.f, 0.f };
			glm::vec3 dir   = { 0.f, 0.f, 0.f };
			bool shandows   = true;
		};

		class DirectionalLight : public Light {

		};

		class PointLight : public Light {

		};

		
		class SpotLight : public Light {

		};

		class AreaLight : public Light {

		};
	}
}

