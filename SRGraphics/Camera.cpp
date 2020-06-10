#include "pch.h"
#include "Camera.h"

bool SpaRcle::Graphics::Camera::Create() {
	debug->Info("Creating camera...");

	ResetCameraPos();
	isCreate = true;

	return true;
}

bool SpaRcle::Graphics::Camera::Init(){
	debug->Graph("Initializing camera...");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		gluPerspective(40, 1.f, 0.01, 5000.0);
		gluLookAt( // visual bugs
			0, 1, 3,
			0, 1, 2,
			0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	GetCursorPos(&pt);              // �������� ������� �������
	prevX = pt.x;                   // �� ������
	prevY = pt.y;                   // �� ������         

	SetCursorPos(1600 / 2, 900 / 2);// ������ ������ � ����� ����
	GetCursorPos(&pt);              // �������� ������� �������
	//prevX = pt.x;                   // �� ������
	//prevY = pt.y;                   // �� ������                
	//Sleep(10);
	//GetCursorPos(&pt);              // ����� �������� ������� �������

	dx = pt.x - prevX;              // ��������� �������� ������� �� 10 ���������� �� ������
	dy = pt.y - prevY;              // ��������� �������� ������� �� 10 ���������� �� ������

	//yaw += dx / 1000.0;               // �������� �� ������ ������������� � ���� �������� ������-�����
	//ptc += dy / 1000.0;
	
	yaw -= dx / 1000.0;               // �������� �� ������ ������������� � ���� �������� ������-�����
	ptc -= dy / 1000.0;

	if (Input::GetKey(KeyCode::W)) spdx += -0.05;
	else if (Input::GetKey(KeyCode::S)) spdx += 0.05;
	else spdx = 0.0;

	if (Input::GetKey(KeyCode::LShift)) spdy += -0.05;
	else if (Input::GetKey(KeyCode::Space)) spdy += 0.05;
	else spdy = 0;

	if (Input::GetKey(KeyCode::A)) spdz += 0.05;
	else if (Input::GetKey(KeyCode::D)) spdz += -0.05;
	else spdz = 0.0;

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

	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	gluLookAt(posx + dxx, posy + dyy, posz - dxz, posx, posy, posz, 0.0, 1.0, 0.0);
}