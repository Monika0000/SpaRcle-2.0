#pragma once
#include <GL\glew.h>
#include "Light.h"
#include <vector>
#include "Shader.h"
#include "Camera.h"

namespace SpaRcle {
	namespace Graphics {
		class RayTracing {
			//const float light0_diffuse[3] = { 0.4, 0.7, 0.2 }; // устанавливаем диффузный цвет света 
			//const float light0_direction[4] = {0.0, 0.0, 1.0, 0.0}; // устанавливаем направление света
		private:
			Camera* camera = nullptr;
			size_t t = 0;
			std::vector<Light*> lights = std::vector<Light*>();
			size_t count_lights = 0;
		public: 
			RayTracing(Camera* camera) {
				this->camera = camera;
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

				glUniform3fv(glGetUniformLocation(shader->ProgramID, "viewPos"), 1, &camera->ViewPos[0]);

				for (t = 0; t < count_lights; t++) {
					if (lights[t] == nullptr) { lights.erase(lights.begin() + t); count_lights--; return; }

					if (t == 0) {
						//std::cout
						//	<< lights[t]->position.x << " "
						//	<< lights[t]->position.y << " "
						//	<< lights[t]->position.z << "\n";

						glUniform3fv(glGetUniformLocation(shader->ProgramID, "light.position"), 1, &lights[t]->position[0]);
						glUniform3fv(glGetUniformLocation(shader->ProgramID, "light.ambient"), 1, &lights[t]->ambient[0]);
						glUniform3fv(glGetUniformLocation(shader->ProgramID, "light.diffuse"), 1, &lights[t]->diffuse[0]);
						glUniform3fv(glGetUniformLocation(shader->ProgramID, "light.specular"), 1, &lights[t]->specular[0]);

						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.constant"), 1, &lights[t]->constant);
						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.linear"), 1, &lights[t]->linear);
						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.quadratic"), 1, &lights[t]->quadratic);

						glUniform1fv(glGetUniformLocation(shader->ProgramID, "light.intensity"), 1, &lights[t]->intensity);
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

