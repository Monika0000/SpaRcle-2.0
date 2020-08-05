#pragma once
#define GLEW_STATIC
#define NOMINMAX

#include <SRHelper.h>
#include "Shader.h"
#include <GL\glu.h>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace SpaRcle {
	using namespace Helper;
		
		namespace Graphics {

		class Camera {
		private:
			//! — Œ–Œ—“» œ≈–≈Ã≈Ÿ≈Õ»ﬂ œŒ Œ—ﬂÃ XYZ
			float spdx = 0.0;
			float spdy = 0.0;
			float spdz = 0.0;
			//! —Ã≈Ÿ≈Õ»≈  ”–—Œ–¿
			float dx = 0.0;
			float dy = 0.0;
			//! ”√À€ ¬–¿Ÿ≈Õ»ﬂ
			float yaw = 0.0;
			float ptc = 0.0;
			//!  ŒŒ–ƒ»Õ¿“€ “Œ◊ »  ”ƒ¿ (»À» Œ“ ”ƒ¿) —ÃŒ“–»“  ¿Ã≈–¿
			float dxx = 0.0;
			float dxz = 0.0;
			float dyy = 0.0;
			//!  ŒŒ–ƒ»“¿“€  ¿Ã≈–€ œŒ Œ—ﬂÃ XYZ
			float posx = 0.0;
			float posy = 0.0; // 2.0
			float posz = 0.0;
			//glm::vec3 pos = { 0,0,0 };

			//POINT pt = { 0, 0 };
			vec2d pt = { 0,0 };
			double prevX;
			double prevY;
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
			//std::vector<GLuint> CameraPositionIdxes;
			//std::vector<GLuint> modelMatIdxes;
			std::vector<Shader*> shaders;
			size_t count_shaders = 0;
			//?=========================================
			Shader* Skybox = nullptr;
			GLuint  SkyboxProjMat = 0;
			GLuint	SkyboxViewMat = 0;
			GLuint	SkyboxCameraPosition = 0;
			//?=========================================
			Shader* Selector = nullptr;
			GLuint  SelectorProjMat = 0;
			GLuint	SelectorViewMat = 0;
			//GLuint	SelectorCameraPosition = 0;
			//?=========================================
			Shader* Stencil = nullptr;
			GLuint  StencilProjMat = 0;
			GLuint	StencilViewMat = 0;
			//GLuint	StencilCameraPosition = 0;
			//?=========================================
			WindowFormat** format = nullptr;
			glm::mat4* projective = nullptr;
			int* x_pos = nullptr; int* y_pos = nullptr;
		private:
			Debug* debug = nullptr;
			GLFWwindow* window = nullptr;
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
			bool Init(bool& isMouseLock, GLFWwindow*win);
			bool Run();
			const vec2l GetMousePos() const noexcept { return { (long)pt.x, (long)pt.y }; }
			void SetCursorPosition(int x, int y) {
				SetCursorPos(x, y);
				prevX = x;
				prevY = y;
			}

			inline const vec3f GetPosition() const noexcept { return { posx, posy, posz }; }

			float Distance(glm::vec3 pos) {
				return sqrtf(
					pow(pos.x - this->posx, 2) +
					pow(pos.y - this->posy, 2) +
					pow(pos.z - this->posz, 2) 
				);
			}

			glm::vec3 dXYZ() { return glm::vec3{ dxx, dyy, dxz }; }

			void SetSkybox(Shader* shader) {
				Skybox = shader;

				SkyboxProjMat = glGetUniformLocation(shader->ProgramID, "projMat");
				SkyboxViewMat = glGetUniformLocation(shader->ProgramID, "viewMat");
				SkyboxCameraPosition = glGetUniformLocation(shader->ProgramID, "CamPos");
			}
			void SetSelector(Shader* shader) {
				Selector = shader;

				SelectorProjMat = glGetUniformLocation(shader->ProgramID, "projMat");
				SelectorViewMat = glGetUniformLocation(shader->ProgramID, "viewMat");
				//SelectorCameraPosition = glGetUniformLocation(shader->ProgramID, "CamPos");
			}
			void SetStencil(Shader* shader) {
				Stencil = shader;

				StencilProjMat = glGetUniformLocation(shader->ProgramID, "projMat");
				StencilViewMat = glGetUniformLocation(shader->ProgramID, "viewMat");
				//StencilCameraPosition = glGetUniformLocation(shader->ProgramID, "CamPos");
			}
			void AddShader(Shader* shader) { 
				this->shaders.push_back(shader);

				projMatIdxes.push_back(glGetUniformLocation(shader->ProgramID, "projMat"));
				viewMatIdxes.push_back(glGetUniformLocation(shader->ProgramID, "viewMat"));
				//CameraPositionIdxes.push_back(glGetUniformLocation(shader->ProgramID, "CamPos"));
				//modelMatIdxes.push_back(glGetUniformLocation(shader->ProgramID, "ModelMat"));

				count_shaders++;
			}
			bool Close();
			void Move();
			void MoveSelector();
			void MoveStencil();
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

