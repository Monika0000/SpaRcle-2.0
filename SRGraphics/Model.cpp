#include "pch.h"
#include "Model.h"
#include "Shader.h"

void SpaRcle::Graphics::Model::Draw(Shader* shader) {
	//mesh->Bind();
	if (texture) {
		if (!texture->isGenerate) texture->Generate();
		shader->Use(texture->id);
	}
	mesh->Draw();

	glUseProgram(0);
}
