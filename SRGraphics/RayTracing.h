#pragma once
#include <GL\glew.h>

namespace SpaRcle {
	namespace Graphics {
		class RayTracing {
			const float light0_diffuse[3] = { 0.4, 0.7, 0.2 }; // устанавливаем диффузный цвет света 
			const float light0_direction[4] = {0.0, 0.0, 1.0, 0.0}; // устанавливаем направление света
		public: 
			RayTracing() {

			};
			~RayTracing() {};
		public:
			void Enable() {
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0); // разрешаем использовать light0 
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее 
				glLightfv(GL_LIGHT0, GL_POSITION, light0_direction); // устанавливаем направление источника света, указанное ранее
			}
			void Disable() {
				glDisable(GL_LIGHT0); // отключаем освещение
				glDisable(GL_LIGHTING);
			}
		};
	}
}

