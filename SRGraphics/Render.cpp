#include "pch.h"
#include "Render.h"
#include <GL\glew.h>
#include <GL\freeglut_std.h>

SpaRcle::Graphics::Render::Render(Debug* debug) {
	this->fog = true;
	this->debug = debug;
	this->_3d_objects = std::vector<Object3D*>();
}

static size_t t = 0;
void SpaRcle::Graphics::Render::DrawAllObjects() {
ret: if (clear) goto ret;
	render = true;
	if (fog)
		InitFog();
	else
		glDisable(GL_FOG);

	glBegin(GL_TRIANGLES);
	for (Object3D* obj : this->_3d_objects) {
		if ((unsigned long long)obj == 0xdddddddddddddddd) {
			debug->Error("Render::DrawAllObjects() : object has adress 0xdddddddddddddddd!");
			break;
		}

		/*Vector3* pos = obj->pos;
		for (t = 0; t < obj->_mesh->count; t++) {
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
		*/
		for (t = 0; t < obj->_mesh->count; t++) {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[0].x,
				obj->_mesh->tris[t].pos[0].y,
				obj->_mesh->tris[t].pos[0].z
			);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[1].x,
				obj->_mesh->tris[t].pos[1].y,
				obj->_mesh->tris[t].pos[1].z
			);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(
				obj->_mesh->tris[t].pos[2].x,
				obj->_mesh->tris[t].pos[2].y,
				obj->_mesh->tris[t].pos[2].z
			);
		}
	}
	glEnd();

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
	gluLookAt(
		0, 1, 3,
		0, 1, 2,
		0, 1, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG); // Туман
	for (UI* ui : this->_ui_objects) {
		ui->Draw();
	}
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
