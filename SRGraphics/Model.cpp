#include "pch.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void SpaRcle::Graphics::Model::Draw(Shader* shader) {
	if (!material->isGenerate) material->Generate();

	if (!mesh->isGenerate) mesh->Generate();
	if (!mesh->isBind) {
		mesh->Bind(); 
	}

	if (material->diffuse) {
		glBindTexture(GL_TEXTURE_2D, material->diffuse->id);
		GLuint texID = glGetUniformLocation(shader->ProgramID, "img");
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texID, 0); // This is GL_TEXTURE0
	}

	mesh->Draw();
}
