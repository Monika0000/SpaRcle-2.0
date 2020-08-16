#include "pch.h"
#include "GUIBase.h"
#include "Canvas.h"

SpaRcle::Graphics::GUI::GUIBase::GUIBase(Canvas* canvas, glm::vec2 pos, glm::vec2 scale, glm::vec4 color) {
	this->canvas = canvas;
	this->posit = pos;
	this->scale = scale;
	this->color = color;
	this->shader = this->canvas->GetShader();
	if (this->canvas->GetEditorMode()) {
		//this->offset_size_y = 0.965;
	}
	//this->SetLocalScale({ 1,1 });
}

void SpaRcle::Graphics::GUI::GUIBase::MoveTo(glm::vec3 new_pos) {

}

void SpaRcle::Graphics::GUI::GUIBase::SetScale(float x, float y) {
	//offset = { 0,-0.005 };
	offset = { 0,0 };

	switch (orientationV) {
	case SpaRcle::Graphics::GUI::OrientationV::CENTER: break; // None
	case SpaRcle::Graphics::GUI::OrientationV::UP:
		this->offset += glm::vec2(0, -y + 1);
		break;
	case SpaRcle::Graphics::GUI::OrientationV::DOWN:
		this->offset += glm::vec2(0, y - 1);
		break;
	default: break;
	}

	switch (orientationH) {
	case SpaRcle::Graphics::GUI::OrientationH::CENTER: break; // None
	case SpaRcle::Graphics::GUI::OrientationH::LEFT:
		this->offset += glm::vec2(x - 1, 0);
		break;
	case SpaRcle::Graphics::GUI::OrientationH::RIGHT:
		this->offset += glm::vec2(-x + 1, 0);
		break;
	default: break;
	}

	this->scale = {x,y};
}
//void SpaRcle::Graphics::GUI::GUIBase::SetGlobalScale(glm::vec2 scale) { this->scale = scale; }
/*
void SpaRcle::Graphics::GUI::GUIBase::SetLocalScale(glm::vec2 scale) {
	this->scale = {
		abs(scale.x),
		abs(scale.y) + (offset_size_y - 1.0)
	};

	auto math = [this](float size) -> float {
		if (size > 0)
			return (-1.0 / size) + 1.0;
		else if (size < 0)
			return (-1.0 / size) - 1.0;
		else
			return 0;
	};

	//this->SetPosition({ 
	this->posit = {
		math(scale.x), 
		math(scale.y + (offset_size_y - 1.0)) + offset_pos_y
	};

	//TODO: todo!
	//this->posit = scale * glm::vec2(-2.0, -2.0);
}
*/
//void SpaRcle::Graphics::GUI::GUIBase::UpdateMatrix() {
//	glm::mat4 mat = glm::mat4(1.0f);
//	mat = glm::translate(mat, posit);
//	model = glm::scale(mat, scale);
//}
