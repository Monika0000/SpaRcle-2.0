#include "pch.h"
#include "Camera.h"
//#include <GL\glut.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"

bool SpaRcle::Graphics::Camera::Create(WindowFormat** format, int& x_pos, int& y_pos, glm::mat4& projective)  {
	debug->Graph("Creating camera...");

	//this->x_size = &x_size;
	//this->y_size = &y_size;

	this->projective = &projective;

	this->format = format;

	this->x_pos = &x_pos;
	this->y_pos = &y_pos;

	ResetCameraPos();
	isCreate = true;

	return true;
}

bool SpaRcle::Graphics::Camera::Init(bool& isMouseLock, GLFWwindow* win){
	debug->Graph("Initializing camera...");

	this->isMouseLock = &isMouseLock;
	this->window = win;
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		gluPerspective(40, 1.f, 0.01, 5000.0);
		gluLookAt( // visual bugs
			0, 1, 3,
			0, 1, 2,
			0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
	return true;
}

bool SpaRcle::Graphics::Camera::Run() {
	if (isCreate) {
		debug->Graph("Running camera...");

		isRun = true;
		move_thread = std::thread(&Camera::FixedMove, this);

		return true;
	} else {
		debug->Error("Camera is not create!");
		return false;
	}
}
bool SpaRcle::Graphics::Camera::Close() {
	debug->Graph("Close camera...");
	isRun = false;
	if (move_thread.joinable()) move_thread.join();
	return true;
}
void SpaRcle::Graphics::Camera::FixedMove() {
	int framelimit = 60; //��������� FPS �� 90
	int now = 0;
	unsigned sceneStartTime = 0;
	unsigned sceneSkipTime = 1000 / framelimit;

	while (isRun) {
		//���� ������� �� �������
		now = clock();
		if (now - sceneStartTime > sceneSkipTime) {
			sceneStartTime = clock();
			if (!isMouseLock || !format) continue;


			if (*isMouseLock) {
				//!GetCursorPos(&pt);          // �������� ������� �������
				glfwGetCursorPos(window, &pt.x, &pt.y);

				prevX = pt.x;                   // �� ������
				prevY = pt.y;                   // �� ������         
			}

			//std::cout << (*format)->size_x << " " << (*format)->size_y << std::endl;
				 
			if (*isMouseLock) {
				//SetCursorPos(1600 / 2, 900 / 2);// ������ ������ � ����� ����
				//bool b = Input::FixedGetKeyDown(KeyCode::F);
				
				if ((unsigned long long)(*format) == 0xdddddddddddddddd) { 
					debug->Warn("Camera : *format has been adress 0xdddddddddddddddd");
					break; }
				SetCursorPos(
					*x_pos + (*format)->size_x / 2,
					*y_pos + (*format)->size_y / 2
				);// ������ ������ � ����� ����

				glfwGetCursorPos(window, &pt.x, &pt.y);
				//!GetCursorPos(&pt);              // �������� ������� �������
				//prevX = pt.x;                   // �� ������
				//prevY = pt.y;                   // �� ������                
				//Sleep(10);
				//GetCursorPos(&pt);              // ����� �������� ������� �������

				if (Input::GetKey(KeyCode::W)) spdx += -0.05;
				else if (Input::GetKey(KeyCode::S)) spdx += 0.05;
				else spdx = 0.0;

				if (Input::GetKey(KeyCode::LShift)) spdy += -0.05;
				else if (Input::GetKey(KeyCode::Space)) spdy += 0.05;
				else spdy = 0;

				if (Input::GetKey(KeyCode::A)) spdz += 0.05;
				else if (Input::GetKey(KeyCode::D)) spdz += -0.05;
				else spdz = 0.0;
			}
			else 
				glfwGetCursorPos(window, &pt.x, &pt.y);
				//!GetCursorPos(&pt);
			
			if (*isMouseLock) {
				dx = pt.x - prevX;              // ��������� �������� ������� �� 10 ���������� �� ������
				dy = pt.y - prevY;              // ��������� �������� ������� �� 10 ���������� �� ������

				yaw -= dx / 1000.0;             // �������� �� ������ ������������� � ���� �������� ������-�����
				ptc -= dy / 1000.0;

				if (abs(ptc) >= 2.f) ptc = 2.f * (ptc / abs(ptc));

				// �������������� ���������� �������� X-Z
				dxx = sin(yaw); // dxx - ��������� ����� ������������ ��� X
				dxz = cos(yaw); // dxz - ��������� ����� ������������ ��� Z
				dyy = sin(ptc / 4.f) * 4.f; // dyy - ��������� ����� ������������ ��� Y

				//std::cout << "sin(" << ptc << ") = " << dyy << std::endl;

				// ������������ �������� ����������� � ����������� �� ���� �������� ������
				// ����� ������ ��������� ����, ���� �������, � �� ����� ���� X � Z
				posz += spdz * dxx;
				posx += spdx * dxx;
				posx += spdz * dxz;
				posz -= spdx * dxz;
				posy += spdy / 10;

				ViewPos = { posx + dxx,posy + dyy, posz - dxz };
				//ViewPos = { posx,posy, posz };
				//ViewPos = { dxx,dyy, dxz };
			}

			viewMat = glm::lookAt(glm::vec3(posx + dxx, posy + dyy, posz - dxz), glm::vec3(posx, posy, posz), glm::vec3(0, 1, 0));
			//pos = { posx, posy, posz };
		}
	}
}

void SpaRcle::Graphics::Camera::MoveSelector() {
	if (isRun) {
		if (!Selector) {
			debug->Error("Camera::MoveSelector() : selector is nullptr!");
			Sleep(1000);
			return;
		}
		Selector->Use();
		glUniformMatrix4fv(SelectorProjMat, 1, GL_FALSE, glm::value_ptr(*this->projective));
		glUniformMatrix4fv(SelectorViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
		//if (SelectorCameraPosition != 4294967295) {
		//	glm::vec3 pos(posx, posy, posz);
		//	glUniform3fv(SelectorCameraPosition, 1, &pos[0]);
		//}
	}
}
void SpaRcle::Graphics::Camera::MoveStencil() {
	if (isRun) {
		if (!Selector) {
			debug->Error("Camera::MoveStencil() : stencil is nullptr!");
			Sleep(1000);
			return;
		}
		Stencil->Use();
		glUniformMatrix4fv(StencilProjMat, 1, GL_FALSE, glm::value_ptr(*this->projective));
		glUniformMatrix4fv(StencilViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
	}
}
void SpaRcle::Graphics::Camera::Move() {
	if (isRun) {
		//if (shader) {
			//glm::mat4 viewMat = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
			//glm::mat4 modelMat = glm::mat4(); // identity

			//GLuint modelMatIdx = glGetUniformLocation(shader->ProgramID, "modelMat");
			//std::cout << projMatIdx << " " << viewMatIdx << " " << modelMatIdx << std::endl;

		if (Skybox) {
			Skybox->Use();
			glUniformMatrix4fv(SkyboxProjMat, 1, GL_FALSE, glm::value_ptr(*this->projective));
			glUniformMatrix4fv(SkyboxViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
			if (SkyboxCameraPosition != 4294967295) {
				glm::vec3 pos(posx, posy, posz);
				glUniform3fv(SkyboxCameraPosition, 1, &pos[0]);
			}
		}

		for (size_t t = 0; t < count_shaders; t++) {
			shaders[t]->Use();
			glUniformMatrix4fv(projMatIdxes[t], 1, GL_FALSE, glm::value_ptr(*this->projective));
			glUniformMatrix4fv(viewMatIdxes[t], 1, GL_FALSE, glm::value_ptr(viewMat));
			//if (CameraPositionIdxes[t] != 4294967295) {
			//if (modelMatIdxes[t] != 4294967295) {
				//glm::mat4 model = glm::mat4(1.0f);
				//model = glm::translate(model, glm::vec3(posx, posy, posz));
				//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
				//glUniformMatrix4fv(modelMatIdxes[t], 1, GL_FALSE, glm::value_ptr(viewMat));
			//	glm::vec3 pos(posx, posy, posz);
			//	glUniform3fv(CameraPositionIdxes[t], 1, &pos[0]);
			//}		
		}
			//glUniformMatrix4fv(modelMatIdx, 1, GL_FALSE, glm::value_ptr(modelMat));
			//}
		//else {
		//	debug->Error("Camera::Move() : shader is nullptr!");
		//}
		//glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		//gluLookAt(posx + dxx, posy + dyy, posz - dxz, posx, posy, posz, 0.0, 0.1, 0.0);
	}
}