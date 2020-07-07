#include "pch.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void SpaRcle::Graphics::Model::Draw(Shader* shader) {
	for (auto& mat : materials) {
		if (!mat) return;
		if (!mat->isGenerate) mat->Generate();
	}

	for (size_t t = 0; t < meshes.size(); t++) {
		if (materials[t]->diffuse) {
			glBindTexture(GL_TEXTURE_2D, materials[t]->diffuse->id);
			GLuint texID = glGetUniformLocation(shader->ProgramID, "img");
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(texID, 0); // This is GL_TEXTURE0
		}

		if (!meshes[t]->isGenerate) meshes[t]->Generate();
		if (!meshes[t]->isBind) meshes[t]->Bind();
		meshes[t]->Draw();
	}
}
