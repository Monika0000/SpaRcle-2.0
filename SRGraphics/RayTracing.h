#pragma once
#include <GL\glew.h>
#include "Light.h"
#include <vector>
#include "Shader.h"

namespace SpaRcle {
	namespace Graphics {
		class RayTracing {
			//const float light0_diffuse[3] = { 0.4, 0.7, 0.2 }; // устанавливаем диффузный цвет света 
			//const float light0_direction[4] = {0.0, 0.0, 1.0, 0.0}; // устанавливаем направление света
		private:
			size_t t = 0;
			std::vector<Light*> lights = std::vector<Light*>();
			size_t count_lights = 0;
		public: 
			RayTracing() {

			};
			~RayTracing() {};
		public:
			void AddLight(Light* light) {
				lights.push_back(light);
				count_lights++;
			}
		public:
			void Enable(Shader* shader) {
				glEnable(GL_LIGHTING);

				for (t = 0; t < count_lights; t++) {
					if (lights[t] == nullptr) { lights.erase(lights.begin() + t); count_lights--; return; }

					if (t == 0) {
						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.position"), 1, &lights[t]->position[0]);
						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.ambient"), 1, &lights[t]->ambient[0]);
					}
				}
				//glEnable(GL_LIGHT0); // разрешаем использовать light0 
				//glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее 
				//glLightfv(GL_LIGHT0, GL_POSITION, light0_direction); // устанавливаем направление источника света, указанное ранее
			}
			void Disable() {
				//glDisable(GL_LIGHT0); // отключаем освещение
				glDisable(GL_LIGHTING);
			}
		};
	}
}

