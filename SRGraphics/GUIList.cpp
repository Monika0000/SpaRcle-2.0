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

	bool vertical = scale.y > scale.x;

	this->text = new GUIText(canvas, name,
		//glm::vec2(-0.25, 0), // + glm::vec2(-2.195, 2.1875),  // + glm::vec2(0, 2.1875)
		//glm::vec2(0.025, -0.06), // + glm::vec2(-2.195, 2.1875),  // + glm::vec2(0, 2.1875)
		{0,0}, // + glm::vec2(-2.195, 2.1875),  // + glm::vec2(0, 2.1875)
		{ 0.25,0.25 }, 
		{ 1,1,1,1 }
	);
	this->text->SetParent(this);
	if(vertical)
		this->text->SetPosition(0.01, -0.23);
	else
		this->text->SetPosition(0.02, -0.165);
	//	this->text->GUIBase::SetPosition(0.02, -0.055);
	//else
	//	this->text->GUIBase::SetPosition(0.02, -0.055 - (0.5f / GUIText::begin_y));
	this->text->Move(0, (scale.y - 1));
	this->text->SetOrientationH(orH);
	this->text->SetOrientationV(OrientationV::UP);

	Texture* texture = vertical
		? canvas->LoadTexture("GUI/GUI_UP.png") : canvas->LoadTexture("GUI/GUI_RIGHT.png");


	this->main_object = new GUIObject(canvas, orH, orV, this->posit, { scale.x, scale.y }, { 0.7, 0.7, 0.7, 0.7 });
	this->main_object->SetTexture(texture);
	this->main_object->SetParent(this);


	this->top_object  = new GUIObject(canvas, orH, OrientationV::UP, 
		this->posit -= vertical ? glm::vec2(0, 0.0125) : glm::vec2(0,0), { scale.x, 0.021 }, { 0.4, 0.4, 0.4, 0.7 });
	this->top_object->Move(0, (scale.y - 1));
	this->top_object->SetTexture(texture);
	this->top_object->SetParent(this);

	//!====================================================================================================================================

	//this->main_object->SetPosition(1.5, 0);
	//this->top_object->SetPosition(1.5, 0);
	//this->text->SetPosition(1.5f, -0.2);

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
	if (isDestroy) return false;

	this->main_object->Draw();
	this->top_object->Draw();
	glUseProgram(0);
	this->text->Draw();
	canvas->UseShader();

    return true;
}

/*
void SpaRcle::Graphics::GUI::GUIList::Move(float x, float y) {
	GUIBase::Move(x, y);
	for (auto& a : Childs) {
		a->Move(x, y);
		//glm::vec2 old = a->GetPosition();
		//glm::vec2 delta = { x - old.x, y - old.y };

		//a->SetPosition(old.x, old.y);
		//a->SetPosition(old.x + x, old.y + y);
	};
}
*/