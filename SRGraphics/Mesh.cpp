#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <glm\ext\matrix_transform.hpp>
#include <glm/detail/type_float.hpp>
#include "Model.h"
#include "Animator.h"

using namespace SpaRcle::Graphics;

//{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 1, 1 } }, { { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 1, 0 } }, { { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },
//{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 1, 0 } }, { { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } }, { { 1.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 1 } },

/*
const std::vector<Vertex> _3D_Models::Cube = {
		// SOUTH
		{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },
		{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },

		// EAST
		{ { 1.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },
		{ { 1.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },

		// NORTH
		{ { 1.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },
		{ { 1.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },

		// WEST
		//{ { 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },
		//{ { 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },

		// TOP
		//{ { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },
		//{ { 0.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 1.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },

		// BOTTOM
		//{ { 1.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },
		//{ { 1.0f, 0.0f, 1.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 0.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },	{ { 1.0f, 0.0f, 0.0f }, { 0, 0, 0 }, { 0, 0 } },
	};
	*/

/*
	 1, 1	0, 1		1, 0		+

*/

namespace SpaRcle {
	namespace Graphics {
		void Mesh::UpdateMatrix() {
			glm::mat4 mat = glm::mat4(1.0f);
			mat = glm::translate(mat, position + default_position);


			//const mat4 rotationMatrix = glm::mat4_cast();

			//auto r = glm::eulerAngles(rotation);

			//mat *= glm::mat4_cast(rotation)

			//mat = glm::rotate(mat, rotation.x, { 1, 0, 0 });
			//mat = glm::rotate(mat, rotation.y, { 0, 1, 0 });
			//mat = glm::rotate(mat, rotation.z, { 0, 0, 1 });

			//(glm::mediump_float)
			 
			mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * (rotation.x + default_rotation.x) / 180.f), { 1, 0, 0 });
			mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * (rotation.y + default_rotation.y) / 180.f), { 0, 1, 0 }); //WARNING
			mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * (rotation.z + default_rotation.z) / 180.f), { 0, 0, 1 });

			model = glm::scale(mat, scale * default_scale);



			//mat = glm::translate(mat, position);
			//mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * rotation.x / 180.f), { 1, 0, 0 });
			//mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * rotation.y / 180.f), { 0, 1, 0 }); //WARNING
			//mat = glm::rotate(mat, (glm::mediump_float32)(Math::PI * rotation.z / 180.f), { 0, 0, 1 });
			//model = glm::scale(mat, scale);
		}
		void Mesh::Draw() {
			if ((unsigned long long)this == 0xdddddddddddddddd) return;

			//if (!isCompile) Compile();
			//if (!isRecompile) Recompile();

			//if (anim) {
				//anim->Use();
			//}

			//glColor4f(0.2f, 0.f, 0.f, 1.f);
			glBindVertexArray(this->VAO);
			//!!glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glDrawElements(GL_TRIANGLES, count_vertices, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, count_vertices); //Начиная с вершины 0 и рисуем count_vertices штуки. Всего => count_vertices/3 треугольника
			//glDisableVertexAttribArray(0);

			//!======================================

			//glBindTexture(GL_TEXTURE_2D, 0); //? IMPORTANT
		}

		void Mesh::FlatDraw() {
			if ((unsigned long long)this == 0xdddddddddddddddd) return;
			//glColor3ubv(&Obj[o].Color.v[0]);
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, count_vertices);
		}
	}
}