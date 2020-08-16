#include "pch.h"
#include "GUIText.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>

SpaRcle::Graphics::GUI::GUIText::GUIText(Canvas* canvas, glm::vec2 pos, glm::vec2 scale, glm::vec4 color) 
	: GUIBase(canvas, pos, scale, color) {
	this->SetString("[None]");
}

SpaRcle::Graphics::GUI::GUIText::GUIText(Canvas* canvas, std::string text, glm::vec2 pos, glm::vec2 scale, glm::vec4 color) 
	: GUIBase(canvas, pos, scale, color) {
	this->SetString(text);
}

SpaRcle::Graphics::GUI::GUIText::~GUIText() { }

void SpaRcle::Graphics::GUI::GUIText::SetString(std::string str) { 
	if (m_text) delete[] this->m_text;
	this->m_text = SpaRcle::Helper::String::CopyStringToCharPointer(str.c_str());
	t_len = strlen(m_text);
}

void SpaRcle::Graphics::GUI::GUIText::SetScale(float x, float y) {
	if (!parent) {
		GUIBase::SetScale(x, y);
		return;
	} else {
		offset = { 0,0 };

		const float begin_x = 2.21;
		const float begin_y = 0.245;

		switch (orientationH) {
		case SpaRcle::Graphics::GUI::OrientationH::CENTER: 
			this->offset += glm::vec2(-parent->scale.x * begin_x
				+ (begin_x * this->parent->posit.x),
			0);
			break; // None
		case SpaRcle::Graphics::GUI::OrientationH::LEFT:
			this->offset += glm::vec2(-begin_x
				+ (begin_x * this->parent->posit.x),
			0);
			break;
		case SpaRcle::Graphics::GUI::OrientationH::RIGHT:
			this->offset += glm::vec2(begin_x - (parent->scale.x * begin_x * 2.f)
				+ (begin_x * this->parent->posit.x),
			0);
			break;
		default: break;
		}

		switch (orientationV) {
		case SpaRcle::Graphics::GUI::OrientationV::CENTER:
			offset += glm::vec2(0, ((begin_y + 1.0) * this->parent->posit.y));
			break;
		case SpaRcle::Graphics::GUI::OrientationV::UP:
			offset += glm::vec2(0, 1 + begin_y
				+ ((begin_y + 1.0) * this->parent->posit.y)
			);
			break;
		case SpaRcle::Graphics::GUI::OrientationV::DOWN:
			offset += glm::vec2(0, -1 - begin_y
				+ ((begin_y + 1.0) * this->parent->posit.y)
			);
			break;
		default: break;
		}

		this->scale = { x,y };
	}

	/*
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

		this->scale = { x,y };
	//}
	*/
}

bool SpaRcle::Graphics::GUI::GUIText::Draw() {
	glPushMatrix();
	glColor4f(
		color.r,
		color.g,
		color.b,
		color.a);

	glTranslatef(posit.x + offset.x, posit.y + offset.y + 1.0, 0);
	glScalef(scale.x / 1000.f, scale.y / 1000.f, 1 / 1000.f);
	for (char* p = m_text; *p; p++) {
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
	}
	glPopMatrix();

	return true;
}
