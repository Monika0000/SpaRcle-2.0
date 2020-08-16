#include "pch.h"
#include "GUIObject.h"
#include "Mesh.h"
#include "Canvas.h"
#include "Shader.h"
#include "Texture.h"

SpaRcle::Graphics::GUI::GUIObject::GUIObject(Canvas* canvas, glm::vec2 pos, glm::vec2 scale, glm::vec4 color) 
	: GUIBase(canvas, pos, scale, color) 
{

}
SpaRcle::Graphics::GUI::GUIObject::GUIObject(
	Canvas* canvas, OrientationH orH, OrientationV orV,
	glm::vec2 pos, glm::vec2 scale, glm::vec4 color
)
	: GUIBase(canvas, pos, scale, color)  { 
	this->SetOrientationH(orH);
	this->SetOrientationV(orV);
	this->SetScale(scale.x, scale.y);
}
SpaRcle::Graphics::GUI::GUIObject::~GUIObject() {
	if (VAO) glDeleteVertexArrays(1, &this->VAO);
	if (VBO) glDeleteBuffers(1, &this->VBO);
	if (UV)  glDeleteTextures(1, &this->UV);
}

bool SpaRcle::Graphics::GUI::GUIObject::Bind() {
	if (isBind)
		return false;

	//this->UpdateMatrix();

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::QuadVertices), &Geometry::QuadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	isBind = true;

	return true;
}

void SpaRcle::Graphics::GUI::GUIObject::SetTexture(Texture* texture) { this->texture = texture; }

bool SpaRcle::Graphics::GUI::GUIObject::Draw() {
	if (isDestroy) return false;
	if (!isBind) Bind();

	this->shader->SetVec2("size", this->scale);
	this->shader->SetVec2("offset", this->posit + this->offset);
	this->shader->SetVec4("color", this->color);
	glBindVertexArray(VAO);
	if (texture) {
		if (!texture->isGenerate) this->texture->Generate();

		glBindTexture(GL_TEXTURE_2D, texture->id);	// use the color attachment texture as the texture of the quad plane
		//shader->SetTexture("Texture", texture->id);
	}
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return true;
}

void SpaRcle::Graphics::GUI::GUIObject::Flat() {

}
