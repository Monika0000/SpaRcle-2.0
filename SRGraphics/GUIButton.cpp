#include "pch.h"
#include "GUIButton.h"
#include "GUIObject.h"
#include "GUIText.h"
#include "Canvas.h"
#include "Texture.h"

SpaRcle::Graphics::GUI::GUIButton::GUIButton(Canvas* canvas, std::string bttn_name, glm::vec2 pos, glm::vec2 scale, glm::vec4 color, 
	OrientationH orH, OrientationV orV) 
	: GUIBase(canvas, pos, scale, color) 
{
	this->SetOrientationH(orH);
	this->SetOrientationV(orV);

	this->main_object = new GUIObject(canvas, orH, orV, pos, scale, color);
	this->main_object->SetTexture(canvas->LoadTexture("GUI/GUI.png"));
	this->main_object->SetParent(this);

	this->text = new GUIText(canvas, bttn_name, { 0, -0.01 }, { 0.25, 0.25 }, { 1,1,1,1 });
	this->text->Move(scale.x - 0.0115 / 2 * bttn_name.size(), 0);
	this->text->SetParent(this);
	this->text->SetOrientationH(orH);
	this->text->SetOrientationV(OrientationV::CENTER);

	switch (orV) {
	case SpaRcle::Graphics::GUI::OrientationV::CENTER:
		break;
	case SpaRcle::Graphics::GUI::OrientationV::UP:
		this->text->Move(0, 0.5 - scale.y / 2.f);
		break;
	case SpaRcle::Graphics::GUI::OrientationV::DOWN:
		this->text->Move(0, -0.5 + scale.y / 2.f);
		break;
	default:
		break;
	}
}

SpaRcle::Graphics::GUI::GUIButton::~GUIButton(){
	if (text) delete text;
	if (main_object) delete main_object;
}

void SpaRcle::Graphics::GUI::GUIButton::Flat(size_t index) {

}

bool SpaRcle::Graphics::GUI::GUIButton::Draw() {
	if (isDestroy) return false;

	this->main_object->Draw();

	glUseProgram(0);

	this->text->Draw();

	this->canvas->UseShader();

	return true;
}
