#pragma once
#include <GL\glew.h>

namespace SpaRcle {
	namespace Graphics {
		class RayTracing {
			const float light0_diffuse[3] = { 0.4, 0.7, 0.2 }; // ������������� ��������� ���� ����� 
			const float light0_direction[4] = {0.0, 0.0, 1.0, 0.0}; // ������������� ����������� �����
		public: 
			RayTracing() {

			};
			~RayTracing() {};
		public:
			void Enable() {
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0); // ��������� ������������ light0 
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // ������������� ��������� ����� light0 ��������� ����, ������� ������� ����� 
				glLightfv(GL_LIGHT0, GL_POSITION, light0_direction); // ������������� ����������� ��������� �����, ��������� �����
			}
			void Disable() {
				glDisable(GL_LIGHT0); // ��������� ���������
				glDisable(GL_LIGHTING);
			}
		};
	}
}

