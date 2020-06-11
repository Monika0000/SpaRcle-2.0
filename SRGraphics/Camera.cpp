#include "pch.h"
#include "Camera.h"
#include <GL\glut.h>

bool SpaRcle::Graphics::Camera::Create(
	unsigned short& x_size, 
	unsigned short& y_size,
	int& x_pos, int& y_pos) 
{
	debug->Info("Creating camera...");

	this->x_size = &x_size;
	this->y_size = &y_size;

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
		debug->Info("Running camera...");

		isRun = true;
		//task = std::thread(&Camera::CameraFunc, this);

		return true;
	} else {
		debug->Error("Camera is not create!");
		return false;
	}
}

bool SpaRcle::Graphics::Camera::Close() {
	debug->Info("Close camera...");
	isRun = false;
	//if (task.joinable()) task.join();
	return true;
}
void SpaRcle::Graphics::Camera::Move() {
	if (isRun) {
		if (*isMouseLock)
			GetCursorPos(&pt);              // онксвюел онгхжхч йспянпю

		prevX = pt.x;                   // он ьхпхме
		prevY = pt.y;                   // он бшянре         

		if (*isMouseLock) {
			//SetCursorPos(1600 / 2, 900 / 2);// ярюбхл йспянп б жемрп нймю
			bool b = Input::FixedGetKeyDown(KeyCode::F);
			SetCursorPos(
				*x_pos + *x_size / 2,
				*y_pos + *y_size / 2
			);// ярюбхл йспянп б жемрп нймю
			GetCursorPos(&pt);              // онксвюел онгхжхч йспянпю
			//prevX = pt.x;                   // он ьхпхме
			//prevY = pt.y;                   // он бшянре                
			//Sleep(10);
			//GetCursorPos(&pt);              // ямнбю онксвюел онгхжхч йспянпю

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

		dx = pt.x - prevX;              // бшвхякъел ялеыемхе йспянпю гю 10 лхкхяейсмд он ьхпхме
		dy = pt.y - prevY;              // бшвхякъел ялеыемхе йспянпю гю 10 лхкхяейсмд он бшянре

		yaw -= dx / 1000.0;               // ялеыемхе он ьхпхме мюйюокхбюеряъ б сцнк бпюыемхъ бопюбн-бкебн
		ptc -= dy / 1000.0;

		// цнпхгнмрюкэмни окняйнярэч ъбкъеряъ X-Z
		dxx = sin(yaw); // dxx - онкнфемхе рнвйх нрмняхрекэмн нях X
		dxz = cos(yaw); // dxz - онкнфемхе рнвйх нрмняхрекэмн нях Z
		dyy = sin(ptc); // dyy - онкнфемхе рнвйх нрмняхрекэмн нях Y

		/*
		glDisable(GL_DEPTH_TEST);
		glRasterPos3f(
			posx,
			posy,
			posz);
		std::string text = "Hello";
		//std::cout << dxx << " " << dxz << " " << dyy << std::endl;

		for (int i = 0; i < text.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
		}
		glEnable(GL_DEPTH_TEST);
		*/
		// йнппейрхпсел яйнпнярэ оепелеыемхъ б гюбхяхлнярх нр сцкю онбнпнрю йюлепш
		// врнаш йюлепю дбхцюкюяэ рсдю, йсдю ялнрпхр, ю ме бднкэ няеи X х Z
		posz += spdz * dxx;
		posx += spdx * dxx;
		posx += spdz * dxz;
		posz -= spdx * dxz;
		posy += spdy / 10;

		//std::cout << posx << " " << posy << " " << posz << std::endl;

		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		gluLookAt(posx + dxx, posy + dyy, posz - dxz, posx, posy, posz, 0.0, 1.0, 0.0);
	}
}