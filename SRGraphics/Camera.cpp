#include "pch.h"
#include "Camera.h"
#include <GL\glut.h>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

bool SpaRcle::Graphics::Camera::Create(WindowFormat* format, int& x_pos, int& y_pos, glm::mat4& projective)  {
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
	int framelimit = 60; //îãðàíè÷èì FPS äî 90
	int now = 0;
	unsigned sceneStartTime = 0;
	unsigned sceneSkipTime = 1000 / framelimit;

	while (isRun) {
		//èùåì ðàçíèöó âî âðåìåíè
		now = clock();
		if (now - sceneStartTime > sceneSkipTime) {
			sceneStartTime = clock();
			if (!isMouseLock) continue;

			if (*isMouseLock)
				GetCursorPos(&pt);          // ÏÎËÓ×ÀÅÌ ÏÎÇÈÖÈÞ ÊÓÐÑÎÐÀ

			prevX = pt.x;                   // ÏÎ ØÈÐÈÍÅ
			prevY = pt.y;                   // ÏÎ ÂÛÑÎÒÅ         

			if (*isMouseLock) {
				//SetCursorPos(1600 / 2, 900 / 2);// ÑÒÀÂÈÌ ÊÓÐÑÎÐ Â ÖÅÍÒÐ ÎÊÍÀ
				bool b = Input::FixedGetKeyDown(KeyCode::F);
				SetCursorPos(
					//*x_pos + *x_size / 2,
					//*y_pos + *y_size / 2
					*x_pos + format->size_x / 2,
					*y_pos + format->size_y / 2
				);// ÑÒÀÂÈÌ ÊÓÐÑÎÐ Â ÖÅÍÒÐ ÎÊÍÀ
				GetCursorPos(&pt);              // ÏÎËÓ×ÀÅÌ ÏÎÇÈÖÈÞ ÊÓÐÑÎÐÀ
				//prevX = pt.x;                   // ÏÎ ØÈÐÈÍÅ
				//prevY = pt.y;                   // ÏÎ ÂÛÑÎÒÅ                
				//Sleep(10);
				//GetCursorPos(&pt);              // ÑÍÎÂÀ ÏÎËÓ×ÀÅÌ ÏÎÇÈÖÈÞ ÊÓÐÑÎÐÀ

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

			dx = pt.x - prevX;              // ÂÛ×ÈÑËßÅÌ ÑÌÅÙÅÍÈÅ ÊÓÐÑÎÐÀ ÇÀ 10 ÌÈËÈÑÅÊÓÍÄ ÏÎ ØÈÐÈÍÅ
			dy = pt.y - prevY;              // ÂÛ×ÈÑËßÅÌ ÑÌÅÙÅÍÈÅ ÊÓÐÑÎÐÀ ÇÀ 10 ÌÈËÈÑÅÊÓÍÄ ÏÎ ÂÛÑÎÒÅ

			yaw -= dx / 1000.0;             // ÑÌÅÙÅÍÈÅ ÏÎ ØÈÐÈÍÅ ÍÀÊÀÏËÈÂÀÅÒÑß Â ÓÃÎË ÂÐÀÙÅÍÈß ÂÏÐÀÂÎ-ÂËÅÂÎ
			ptc -= dy / 1000.0;

			// ÃÎÐÈÇÎÍÒÀËÜÍÎÉ ÏËÎÑÊÎÑÒÜÞ ßÂËßÅÒÑß X-Z
			dxx = sin(yaw); // dxx - ÏÎËÎÆÅÍÈÅ ÒÎ×ÊÈ ÎÒÍÎÑÈÒÅËÜÍÎ ÎÑÈ X
			dxz = cos(yaw); // dxz - ÏÎËÎÆÅÍÈÅ ÒÎ×ÊÈ ÎÒÍÎÑÈÒÅËÜÍÎ ÎÑÈ Z
			dyy = sin(ptc); // dyy - ÏÎËÎÆÅÍÈÅ ÒÎ×ÊÈ ÎÒÍÎÑÈÒÅËÜÍÎ ÎÑÈ Y

			// ÊÎÐÐÅÊÒÈÐÓÅÌ ÑÊÎÐÎÑÒÜ ÏÅÐÅÌÅÙÅÍÈß Â ÇÀÂÈÑÈÌÎÑÒÈ ÎÒ ÓÃËÀ ÏÎÂÎÐÎÒÀ ÊÀÌÅÐÛ
			// ×ÒÎÁÛ ÊÀÌÅÐÀ ÄÂÈÃÀËÀÑÜ ÒÓÄÀ, ÊÓÄÀ ÑÌÎÒÐÈÒ, À ÍÅ ÂÄÎËÜ ÎÑÅÉ X È Z
			posz += spdz * dxx;
			posx += spdx * dxx;
			posx += spdz * dxz;
			posz -= spdx * dxz;
			posy += spdy / 10;
		}
	}
}

void SpaRcle::Graphics::Camera::Move() {
	if (isRun) {
		if (shader) {
			//glm::mat4 viewMat = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
			glm::mat4 viewMat = glm::lookAt(glm::vec3(posx + dxx, posy + dyy, posz - dxz), glm::vec3(posx, posy, posz), glm::vec3(0, 1, 0));
			//glm::mat4 modelMat = glm::mat4(); // identity

			//GLuint modelMatIdx = glGetUniformLocation(shader->ProgramID, "modelMat");
			//std::cout << projMatIdx << " " << viewMatIdx << " " << modelMatIdx << std::endl;

			glUniformMatrix4fv(projMatIdx, 1, GL_FALSE, glm::value_ptr(*this->projective));
			glUniformMatrix4fv(viewMatIdx, 1, GL_FALSE, glm::value_ptr(viewMat));
			//glUniformMatrix4fv(modelMatIdx, 1, GL_FALSE, glm::value_ptr(modelMat));
		}
		else {
			debug->Error("Camera::Move() : shader is nullptr!");
		}
		//glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		//gluLookAt(posx + dxx, posy + dyy, posz - dxz, posx, posy, posz, 0.0, 0.1, 0.0);
	}
}