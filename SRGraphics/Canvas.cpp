#include "pch.h"
#include "Canvas.h"
#include "Window.h"
#include "Shader.h"
#include "Render.h"
#include "Texture.h"

using namespace SpaRcle::Graphics;
using namespace SpaRcle::Helper;

SpaRcle::Graphics::GUI::Canvas::Canvas(Window* window) {
    this->window = window;
}
SpaRcle::Graphics::GUI::Canvas::~Canvas() {
    if (!this->isRelease) this->Release();
}
bool SpaRcle::Graphics::GUI::Canvas::Init() {
    this->debug = this->window->GetDebug();
    debug->Graph("Canvas::Init() : Initializing canvas...");

    this->cBuff = this->window->GetColorBuffer();
    this->isInit = true;

    this->shader = new Shader("GUI", debug);

    return this->shader->Compile();
}

bool SpaRcle::Graphics::GUI::Canvas::Release() {
    this->debug->Info("Canvas::Release() : Delete canvas...");

    if (this->shader) delete shader;

    for (auto a : this->m_objects)
        delete a;

    for (auto a : this->m_texts)
        delete a;

    // TODO: Delete all gui objects and texts

    this->isRelease = true;

    return true;
}

Texture* SpaRcle::Graphics::GUI::Canvas::LoadTexture(std::string name) {
    return this->window->GetRender()->GetTextureManager()->LoadTexture(name.c_str());
}

void SpaRcle::Graphics::GUI::Canvas::UseShader() {
    shader->Use();
}

bool SpaRcle::Graphics::GUI::Canvas::GetEditorMode() {
    return this->window->GetEditorMode();
}

bool SpaRcle::Graphics::GUI::Canvas::PoolEvents() {
    if (!isInit) return false;
    
    // Draw colored gui and select gui click

    return true;
}
bool SpaRcle::Graphics::GUI::Canvas::Draw() {
    if (!isInit) return false;

    //glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT); // Без этого ничего не будет работать (очистка буфера)
    glLoadIdentity();
    gluLookAt(
        0, 1, 3,
        0, 1, 2,
        0, 1, 0);
    glDisable(GL_DEPTH_TEST);

    shader->Use();

   // for (auto a : this->m_objects)
    DrawGUI(this->m_objects);
    //for (auto a : this->m_lists)
    DrawGUI(this->m_lists);

    DrawGUI(this->m_buttons);

    glUseProgram(0);

    //!=============================================================================================================================================================


    //glDisable(GL_FOG); // Туман

    //for (auto a : this->m_texts)
    DrawGUI(this->m_texts);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FOG); // Туман

    return true;
}
