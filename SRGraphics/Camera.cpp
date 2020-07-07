#include "pch.h"
#include "Camera.h"
#include <GL\glut.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

bool SpaRcle::Graphics::Camera::Init(bool& isMouseLock){
	debug->Graph("Initializing camera...");

	this->isMouseLock = &isMouseLock;
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
				GetCursorPos(&pt);          // �������� ������� �������

				prevX = pt.x;                   // �� ������
				prevY = pt.y;                   // �� ������         
			}

			//std::cout << (*format)->size_x << " " << (*format)->size_y << std::endl;
				 
			if (*isMouseLock) {
				//SetCursorPos(1600 / 2, 900 / 2);// ������ ������ � ����� ����
				bool b = Input::FixedGetKeyDown(KeyCode::F);
				
				if ((unsigned long long)(*format) == 0xdddddddddddddddd) { 
					debug->Warn("Camera : *format has been adress 0xdddddddddddddddd");
					break; }
				SetCursorPos(
					//*x_pos + *x_size / 2,
					//*y_pos + *y_size / 2
					*x_pos + (*format)->size_x / 2,
					*y_pos + (*format)->size_y / 2
				);// ������ ������ � ����� ����
				GetCursorPos(&pt);              // �������� ������� �������
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

			dx = pt.x - prevX;              // ��������� �������� ������� �� 10 ���������� �� ������
			dy = pt.y - prevY;              // ��������� �������� ������� �� 10 ���������� �� ������

			yaw -= dx / 1000.0;             // �������� �� ������ ������������� � ���� �������� ������-�����
			ptc -= dy / 1000.0;

			// �������������� ���������� �������� X-Z
			dxx = sin(yaw); // dxx - ��������� ����� ������������ ��� X
			dxz = cos(yaw); // dxz - ��������� ����� ������������ ��� Z
			dyy = sin(ptc); // dyy - ��������� ����� ������������ ��� Y

			// ������������ �������� ����������� � ����������� �� ���� �������� ������
			// ����� ������ ��������� ����, ���� �������, � �� ����� ���� X � Z
			posz += spdz * dxx;
			posx += spdx * dxx;
			posx += spdz * dxz;
			posz -= spdx * dxz;
			posy += spdy / 10;

			viewMat = glm::lookAt(glm::vec3(posx + dxx, posy + dyy, posz - dxz), glm::vec3(posx, posy, posz), glm::vec3(0, 1, 0));
		}
	}
}

void SpaRcle::Graphics::Camera::Move() {
	if (isRun) {
		//if (shader) {
			//glm::mat4 viewMat = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
			//glm::mat4 modelMat = glm::mat4(); // identity

			//GLuint modelMatIdx = glGetUniformLocation(shader->ProgramID, "modelMat");
			//std::cout << projMatIdx << " " << viewMatIdx << " " << modelMatIdx << std::endl;


		for (size_t t = 0; t < count_shaders; t++) {
			shaders[t]->Use();
			glUniformMatrix4fv(projMatIdxes[t], 1, GL_FALSE, glm::value_ptr(*this->projective));
			glUniformMatrix4fv(viewMatIdxes[t], 1, GL_FALSE, glm::value_ptr(viewMat));
			if (CameraPositionIdxes[t] != 4294967295) {
				glm::vec3 pos(posx, posy, posz);
				glUniform3fv(CameraPositionIdxes[t], 1, &pos[0]);
			}
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