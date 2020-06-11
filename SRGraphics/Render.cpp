#include "pch.h"
#include "Render.h"
#include <GL\glew.h>
#include <GL\freeglut_std.h>

SpaRcle::Graphics::Render::Render(Debug* debug) {
	this->fog = true;
	this->debug = debug;
	this->_3d_objects = std::vector<Object3D*>();
}

void SpaRcle::Graphics::Render::DrawAllObjects() {
ret: if (clear) goto ret;
	render = true;
	if (fog)
		InitFog();
	else
		glDisable(GL_FOG);

	for (Object3D* obj : this->_3d_objects) {
	//size_t count = this->_3d_objects.size();
	//for(size_t t = 0; t < count; t++) {
		if ((unsigned long long)obj == 0xdddddddddddddddd) {
			debug->Error("Render::DrawAllObjects() : object has adress 0xdddddddddddddddd!");
			break;
		}
		//Object3D* obj = _3d_objects[t];

		glBegin(GL_TRIANGLES);
		//glColor3f(0.0, 1.0, 0.0);
		Vector3* pos = obj->pos;
		for (size_t t = 0; t < obj->_mesh->count; t++) {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[0].x + pos->x,
				obj->_mesh->tris[t].pos[0].y + pos->y,
				obj->_mesh->tris[t].pos[0].z + pos->z
			);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[1].x + pos->x,
				obj->_mesh->tris[t].pos[1].y + pos->y,
				obj->_mesh->tris[t].pos[1].z + pos->z
			);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[2].x + pos->x,
				obj->_mesh->tris[t].pos[2].y + pos->y,
				obj->_mesh->tris[t].pos[2].z + pos->z
			);
		}
		glEnd();
	}
	render = false;
	/*
	float size = 2.5f;

	//glPointSize(1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex2f(0, 0);
	glVertex2f(size, 0);
	glVertex2f(size, size);
	glVertex2f(0, size);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);                         // Задается текущий цвет примитивов
	glutWireCube(2.0f);                                  // Рисуется проволочный куб со стороной 2
	*/
}
void SpaRcle::Graphics::Render::DrawAllUI() {
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	gluLookAt( // visual bugs
		0, 1, 3,
		0, 1, 2,
		0, 1, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG); // Туман
	for (UI* ui : this->_ui_objects) {
		glRasterPos3f(
			ui->pos->x,
			ui->pos->y,
			*ui->size);

		for (int i = 0; i < *ui->t_len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)ui->text[i]);
		}
	}
	/*
	glRasterPos3f(
		0.5,
		1,
		1);
	std::string text = "Hello";
	for (int i = 0; i < text.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG); // Туман
}

void SpaRcle::Graphics::Render::AddObject3D(Object3D* obj) {
	if ((unsigned long long)obj == 0xdddddddddddddddd) {
		debug->Error("Render::AddObject3D() : object has adress 0xdddddddddddddddd!");
		return;
	}
	this->_3d_objects.push_back(obj);
}
void SpaRcle::Graphics::Render::AddUI(UI* ui) {
	if ((unsigned long long)ui == 0xdddddddddddddddd) {
		debug->Error("Render::AddObject3D() : object has adress 0xdddddddddddddddd!");
		return;
	}
	this->_ui_objects.push_back(ui);
}
