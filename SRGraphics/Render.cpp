#define GLEW_STATIC
#include "pch.h"
#include "Render.h"
#include <GL\glew.h>
#include <GL\freeglut_std.h>
#include "SRGraphics.h"
#include <glm\gtc\type_ptr.hpp>
//#pragma comment(lib, "glew32s.lib")

static size_t t = 0;

SpaRcle::Graphics::Render::Render(Debug* debug) {
	this->fog = true;
	this->debug = debug;
	this->texManager = NULL;
	this->count_models = 0;
	this->models = std::vector<Model*>();
	//this->clear = false;
	this->isCreate = false;
	this->isInit = false;
	this->isRun = false;
	//this->_3d_objects = std::vector<Object3D*>();
}

bool SpaRcle::Graphics::Render::Create(Camera* camera, SRGraphics* graph) {
	debug->Graph("Creating render...");

	this->graph = graph;
	this->camera = camera;

	this->fbxLoader  = new FbxLoader(debug, this->graph);

	this->texManager = new TextureManager(debug, graph);
	this->matManager = new MaterialManager(debug, graph);

	this->def_mat = new Material(texManager->LoadTexture("default.png"));

	this->modManager = new ModelManager(debug, graph, def_mat);

	this->raytracing = new RayTracing(camera);

	//?//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	this->shader		 = new Shader("shader", debug);
	this->skyboxShader	 = new Shader("skybox", debug);
	this->selectorShader = new Shader("selector", debug);
	this->Stencil		 = new Shader("stencil", debug);
	this->PostProcessing = new Shader("PostProcessing", debug);

	isCreate = true;
	return true;
}
bool SpaRcle::Graphics::Render::Init() {
	if (!isCreate) {
		debug->Error("Render is not create!");
		return false;
	}

	debug->Graph("Initializing render...");


	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		// All ok
	//}
	//else {
	//	debug->Error("Render::Init() : Failed bind the frame buffer!");
	//	return false;
	//}

	this->EditorMode = this->graph->EditorMode;

	this->shader->Compile();
	this->skyboxShader->Compile();
	this->PostProcessing->Compile();

	if (EditorMode) {
		this->selectorShader->Compile();
		this->Stencil->Compile();
	}

	/*
		Сначала необходимо выполнить шейдер скайбокса, 
		а только потом основной шейдер программы!
		Иначе ничего не будет работать
	*/

	this->win = graph->GetWindow();

	this->camera->SetSkybox(skyboxShader);
	//this->camera->AddShader(skyboxShader);
	this->camera->AddShader(shader);

	if (EditorMode) {
		this->camera->SetSelector(selectorShader);
		this->camera->SetStencil(Stencil);
	}
	//this->InitFog();

	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::QuadVertices), &Geometry::QuadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}

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

	delete raytracing;
}

void SpaRcle::Graphics::Render::DrawSelectorObjects() {
//	if (!isRun) return;
//ret: if (clear) goto ret;
//	render = true;

	for (t = 0; t < this->count_models; t++)
		models[t]->FlatDraw(t, selectorShader);

	glUseProgram(0);

//	render = false;
}
void SpaRcle::Graphics::Render::DrawAimingObjects() {
	for (t = 0; t < this->count_aiming_meshes; t++) {
		glUniformMatrix4fv(glGetUniformLocation(selectorShader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(aiming_meshes[t]->model));

		vec3uc c = GraphUtils::IntToColor(t + 10);
		float* color = GraphUtils::TransliteFloatColor((unsigned int)c.x, (unsigned int)c.y, (unsigned int)c.z);

		GLuint texID = glGetUniformLocation(selectorShader->ProgramID, "color");
		glUniform3fv(texID, 1, &color[0]);

		delete color;

		aiming_meshes[t]->FlatDraw();
	}
	glUseProgram(0);
}

void SpaRcle::Graphics::Render::DrawAllObjects() {
	if (FBO) {
		//? =================================
		//? Пока не уверен в надобности этого
		//? =================================
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	//if (fog)
	//	InitFog();
	//else
	//	glDisable(GL_FOG);

	raytracing->Enable(shader);
	
	for (t = 0; t < this->count_models; t++)// {
		//std::cout << models[t]->GetPosition().x << " "
		//	<< models[t]->GetPosition().y << " "
		//	<< models[t]->GetPosition().z << "\n";
		if (models[t] && models[t]->enabled) {
			if (!models[t]->isSelect) {
				//shader->Use();
				//glBindFramebuffer(GL_FRAMEBUFFER, FBO);
				if (!models[t]->Draw(shader)) {
					delete models[t]; models[t] = nullptr;
					models.erase(models.begin() + t);
					t--;
					count_models--;
				}
				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				//glUseProgram(0);
			}
			else {
				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_ALWAYS, 1, 1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				glStencilMask(1);
				glClearStencil(0);
				glClear(GL_STENCIL_BUFFER_BIT);

				models[t]->Draw(shader);

				glStencilFunc(GL_EQUAL, 0, 1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				glStencilMask(0x00);

				Stencil->Use();

				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				// Скайбокс перекрывает обводку
				models[t]->DrawSencil(this->Stencil);
				//glBindFramebuffer(GL_FRAMEBUFFER, FBO);

				glDisable(GL_STENCIL_TEST);

				shader->Use();
			}
		}
	//}

	raytracing->Disable();

	if (skybox) skybox->Draw(skyboxShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	PostProcessing->Use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, ScreenTexture);	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);

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

//	render = false;
}
void SpaRcle::Graphics::Render::DrawAllUI() {
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	gluLookAt(
		0, 1, 3,
		0, 1, 2,
		0, 1, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG); // Туман

	bool mouse_left_down = Input::GetKeyDown(KeyCode::MouseLeft);
	bool mouse_left_up   = Input::GetKeyUp(KeyCode::MouseLeft);

	vec2d pos =  win->GetMousePos();
	//std::cout << "mouse_x = " << pos.x << "; mouse_y = " << pos.y << std::endl;
	for (UI* ui : this->_ui_objects) {
		ui->Draw(
			{ mouse_left_down, mouse_left_up },  
			pos
		);
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
	//std::cout << "New model added : " << model << "; pos = " 
	//	<<		  model->GetPosition().x
	//	<< " " << model->GetPosition().y 
	//	<< " " << model->GetPosition().z << std::endl;
}
void SpaRcle::Graphics::Render::AddAimingMesh(Mesh* model) {
//	model->CanSelect = false; //? Я так хочу.
	this->aiming_meshes.push_back(model);
	this->count_aiming_meshes++;
//	AddModel(model);
}
bool SpaRcle::Graphics::Render::RemoveAimingMesh(Mesh* mesh) {
	for (size_t t = 0; t < count_aiming_meshes; t++)
		if (aiming_meshes[t] == mesh) {
			count_aiming_meshes--; //!!!!!
			aiming_meshes.erase(aiming_meshes.begin() + t);
			return true;
		}
	return false;
}
void SpaRcle::Graphics::Render::AddUI(UI* ui) {
	if ((unsigned long long)ui == 0xdddddddddddddddd) {
		debug->Error("Render::AddObject3D() : object has adress 0xdddddddddddddddd!");
		return;
	}
	this->_ui_objects.push_back(ui);
}

SpaRcle::Graphics::Mesh* SpaRcle::Graphics::Render::GetAimingMesh() {
	if (count_aiming_meshes == 0) return nullptr;
	else {
		glClearColor(0.f, 0.f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)
		glLoadIdentity();

		camera->MoveSelector();

		win->colorBuffer->InitNames(count_aiming_meshes);
		for (t = 0; t < count_aiming_meshes; t++) {
			if (!aiming_meshes[t]) {
				count_aiming_meshes--;
				aiming_meshes.erase(aiming_meshes.begin() + t);
				return nullptr;
			}
			win->colorBuffer->LoadName(t, GraphUtils::IntToColor(t + 10));
		}
		DrawAimingObjects();

		vec2d pos = this->win->GetMousePos();

		unsigned char pixel[3] = { 0 };
		unsigned int x = pos.x * win->format->size_x;
		unsigned int y = pos.y * win->format->size_y;

		glReadPixels(x, this->win->GetYSize() - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel[0]);

		int i = win->colorBuffer->GetSelectColorObject(pixel);

		if (i != -1) return aiming_meshes[i];
		else return nullptr;
	}
}
SpaRcle::Graphics::Model* SpaRcle::Graphics::Render::GetSelectedModel() {
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)
	glLoadIdentity();

	camera->MoveSelector();

	win->colorBuffer->InitNames(GetCountModels());
	for (size_t t = 0; t < GetCountModels(); t++) {
		//vec3uc color = GraphUtils::IntToColor(t + 1);
		//vec3uc color{ 0, 0, t + 1};
		//debug->Log("Add color : "+  std::to_string(color.x) + " " + std::to_string(color.y) + " " + std::to_string(color.z));
		win->colorBuffer->LoadName(t, GraphUtils::IntToColor(t + 10));
	}
	DrawSelectorObjects();

	//Vector2d* pos = this->GetMousePosition();
	vec2d pos = this->win->GetMousePos();

	unsigned char pixel[3] = { 0 };
	unsigned int x = pos.x * win->format->size_x;
	unsigned int y = pos.y * win->format->size_y;

	//debug->Log(std::to_string(x) + " " + std::to_string(y));

	glReadPixels(x, this->win->GetYSize() - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel[0]);

	//debug->Log(std::to_string(pixel[0]) + " " + std::to_string(pixel[1]) + " " + std::to_string(pixel[2]));

	int select = win->colorBuffer->GetSelectColorObject(pixel);
	debug->Log("Select object : " + std::to_string(select));

	if (select != -1) return models[select];
	else return nullptr;
}
