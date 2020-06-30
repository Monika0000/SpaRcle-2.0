#define GLEW_STATIC
#include "pch.h"
#include "Render.h"
#include <GL\glew.h>
#include <GL\freeglut_std.h>

//#pragma comment(lib, "glew32s.lib")

SpaRcle::Graphics::Render::Render(Debug* debug) {
	this->fog = true;
	this->debug = debug;
	this->texManager = NULL;
	this->count_models = 0;
	this->models = std::vector<Model*>();
	this->clear = false;
	this->isCreate = false;
	this->isInit = false;
	this->isRun = false;
	//this->_3d_objects = std::vector<Object3D*>();
}

bool SpaRcle::Graphics::Render::Create() {
	debug->Graph("Creating render...");
	this->texManager = new TextureManager(debug);
	isCreate = true;

	this->shader = new Shader("shader", debug);

	return true;
}
bool SpaRcle::Graphics::Render::Init() {
	if (!isCreate) {
		debug->Error("Render is not create!");
		return false;
	}

	debug->Graph("Initializing render...");

	this->shader->Compile();

	//this->InitFog();

	isInit = true;
	return true;
}
bool SpaRcle::Graphics::Render::Run() {
	if (!isInit) {
		debug->Error("Render is not initialize!");
		return false;
	}

	debug->Graph("Running render...");

	isRun = true;
	return true;
}
void SpaRcle::Graphics::Render::Close() {
	debug->Graph("Close render...");

	isRun = false;
	Sleep(10); //! We wait until the render has time to close. 
	//Clear();
	for (UI* ui : this->_ui_objects)
		if (ui) delete ui;
	//_ui_objects.clear();
}

static size_t t = 0;
void SpaRcle::Graphics::Render::DrawAllObjects() {
	if (!isRun) return;
ret: if (clear) goto ret;
	render = true;
	if (fog)
		InitFog();
	else
		glDisable(GL_FOG);

	//glRotatef(90, 0, 0, 1);

	for (Model* model : models)
		model->Draw(shader);

	/*
	if (useOldSlowRender) {
		glBegin(GL_TRIANGLES);
		for (Object3D* obj : this->_3d_objects) {
			if ((unsigned long long)obj == 0xdddddddddddddddd) {
				debug->Error("Render::DrawAllObjects() : object has adress 0xdddddddddddddddd!");
				break;
			}

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
	}
	*/

	render = false;
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

void SpaRcle::Graphics::Render::AddModel(Model* model) {
	if ((unsigned long long)model == 0xdddddddddddddddd) {
		debug->Error("Render::AddModel() : model has adress 0xdddddddddddddddd!");
		return;
	}
	this->models.push_back(model);
	this->count_models++;
}
void SpaRcle::Graphics::Render::AddUI(UI* ui) {
	if ((unsigned long long)ui == 0xdddddddddddddddd) {
		debug->Error("Render::AddObject3D() : object has adress 0xdddddddddddddddd!");
		return;
	}
	this->_ui_objects.push_back(ui);
}
