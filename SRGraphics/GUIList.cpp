#include "pch.h"
#include "GUIList.h"
#include "GUIText.h"
#include "GUIObject.h"
#include "Canvas.h"
#include "Texture.h"

SpaRcle::Graphics::GUI::GUIList::GUIList(
	Canvas* canvas, std::string name, glm::vec2 pos, glm::vec2 scale, glm::vec4 color,
	OrientationH orH, OrientationV orV
)
	: GUIBase(canvas, pos, scale, color)
{
	this->SetOrientationH(orH);
	this->SetOrientationV(orV);

	this->text = new GUIText(canvas, name,
		//glm::vec2(-0.25, 0), // + glm::vec2(-2.195, 2.1875),  // + glm::vec2(0, 2.1875)
		glm::vec2(0.025, -0.06), // + glm::vec2(-2.195, 2.1875),  // + glm::vec2(0, 2.1875)
		{ 0.25,0.25 }, 
		{ 1,1,1,1 }
	);
	this->text->SetParent(this);
	this->Childs.push_back(text);
	this->text->SetOrientationH(orH);
	this->text->SetOrientationV(OrientationV::UP);

	this->main_object = new GUIObject(canvas, orH, orV,				 this->posit, { scale.x, 1}, { 0.7, 0.7, 0.7, 0.7 });
	this->main_object->SetTexture(canvas->LoadTexture("GUI/GUI UP.png"));

	this->top_object  = new GUIObject(canvas, orH, OrientationV::UP, this->posit -= glm::vec2(0, 0.015), { scale.x, 0.021 }, { 0.4, 0.4, 0.4, 0.7 });
	this->top_object->SetTexture(canvas->LoadTexture("GUI/GUI UP.png"));

	//!====================================================================================================================================

	//this->main_object->SetPosition(1, 0);
	//this->top_object->SetPosition(1, 0);
	//this->text->SetPosition(2.0 - scale.x / 2.0, 0);

	//this->main_object->SetPosition(0, 0);
	//this->top_object->SetPosition(0, 0);
	//this->text->SetPosition(-1.0, 0);
};

SpaRcle::Graphics::GUI::GUIList::~GUIList() {
	if (this->main_object)		delete main_object;
	if (this->top_object)		delete top_object;
	if (this->text)				delete text;
}

bool SpaRcle::Graphics::GUI::GUIList::Draw() {
	this->main_object->Draw();
	this->top_object->Draw();
	glUseProgram(0);
	this->text->Draw();
	canvas->UseShader();

    return true;
}
