#include "pch.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void SpaRcle::Graphics::Model::Draw(Shader* shader) {
	if (texture) {
		if (!texture->isGenerate) texture->Generate();
	} else return;

	if (!mesh->isGenerate) mesh->Generate();
	if (!mesh->isBind) {
		mesh->Bind(); 
	}

	glBindTexture(GL_TEXTURE_2D, texture->id);
	GLuint texID = glGetUniformLocation(shader->ProgramID, "img");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texID, 0); // This is GL_TEXTURE0

	mesh->Draw();
}
