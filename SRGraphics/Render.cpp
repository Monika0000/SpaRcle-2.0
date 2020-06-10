#include "pch.h"
#include "Render.h"
#include <GL\glew.h>
#include <GL\freeglut_std.h>

SpaRcle::Graphics::Render::Render(Debug* debug) {
	this->debug = debug;
	this->_3d_objects = std::vector<Object3D*>();
}

SpaRcle::Graphics::Render::~Render() {

}

void SpaRcle::Graphics::Render::DrawAllObjects() {
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

void SpaRcle::Graphics::Render::AddObject3D(Object3D* obj) {
	if ((unsigned long long)obj == 0xdddddddddddddddd) {
		debug->Error("Render::AddObject3D() : object has adress 0xdddddddddddddddd!");
		return;
	}
	_3d_objects.push_back(obj);
}