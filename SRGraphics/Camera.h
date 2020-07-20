#pragma once
#include <SRHelper.h>
#include "Shader.h"
#include <GL\glu.h>
#include <glm/glm.hpp>

namespace SpaRcle {
	using namespace Helper;

		namespace Graphics {
		class Camera {
		private:
			//! яйнпнярх оепелеыемхъ он няъл XYZ
			float spdx = 0.0;
			float spdy = 0.0;
			float spdz = 0.0;
			//! ялеыемхе йспянпю
			float dx = 0.0;
			float dy = 0.0;
			//! сцкш бпюыемхъ
			float yaw = 0.0;
			float ptc = 0.0;
			//! йннпдхмюрш рнвйх йсдю (хкх нрйсдю) ялнрпхр йюлепю
			float dxx = 0.0;
			float dxz = 0.0;
			float dyy = 0.0;
			//! йннпдхрюрш йюлепш он няъл XYZ
			float posx = 0.0;
			float posy = 0.0; // 2.0
			float posz = 0.0;
			//glm::vec3 pos = { 0,0,0 };

			POINT pt;
			float prevX;
			float prevY;
		private:
			void FixedMove();
		private:
			bool isCreate = false;
			bool isRun = false;
			bool* isMouseLock = nullptr;
		private:
			glm::mat4 viewMat;
			std::vector<GLuint> projMatIdxes;
			std::vector<GLuint> viewMatIdxes;
			std::vector<GLuint> CameraPositionIdxes;
			std::vector<Shader*> shaders;
			size_t count_shaders = 0;
			//?=========================================
			Shader* Selector = nullptr;
			GLuint  SelectorProjMat = 0;
			GLuint	SelectorViewMat = 0;
			GLuint	SelectorCameraPosition = 0;
			//?=========================================
			WindowFormat** format = nullptr;
			glm::mat4* projective = nullptr;
			int* x_pos = nullptr; int* y_pos = nullptr;
		private:
			Debug* debug = nullptr;
			std::thread move_thread;
		public:
			const glm::mat4 GetView() const noexcept { return viewMat; }
			const glm::mat4 GetProj() const { return *projective; }
		public:
			Camera(Debug*debug) {
				//x_size = NULL;
				//y_size = NULL;
				this->format = NULL;
				x_pos = NULL;
				y_pos = NULL;
				this->debug = debug;
				isCreate = false;
				isRun = false;
			};
			~Camera() { Close(); };
		public:
			bool Create(WindowFormat** format, int& x_pos, int& y_pos, glm::mat4& projective);
			bool Init(bool& isMouseLock);
			bool Run();
			void SetCursorPosition(int x, int y) {
				SetCursorPos(x, y);
				prevX = x;
				prevY = y;
			}
			void SetSelector(Shader* shader) {
				Selector = shader;

				SelectorProjMat = glGetUniformLocation(shader->ProgramID, "projMat");
				SelectorViewMat = glGetUniformLocation(shader->ProgramID, "viewMat");
				SelectorCameraPosition = glGetUniformLocation(shader->ProgramID, "CamPos");
			}
			void AddShader(Shader* shader) { 
				this->shaders.push_back(shader);

				projMatIdxes.push_back(glGetUniformLocation(shader->ProgramID, "projMat"));
				viewMatIdxes.push_back(glGetUniformLocation(shader->ProgramID, "viewMat"));
				CameraPositionIdxes.push_back(glGetUniformLocation(shader->ProgramID, "CamPos"));

				count_shaders++;
			}
			bool Close();
			void Move();
			void MoveSelector();
		public:
			//void CameraFunc();
			void ResetCameraPos() {
				posx = 0; posy = 0; posz = 0;
				yaw = 0; ptc = 0;
				dxx = 0; dxz = 0; dyy = 0;
			}
		};
	}
}

