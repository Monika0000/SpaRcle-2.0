#pragma once
//#include "Material.h"
#include "Vectors.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <Vector3.h>

namespace SpaRcle {
	namespace Graphics {
		//struct triangle { vec3f pos[3]; };

		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
		 	glm::vec2 TexCoords;
		};

		class _3D_Models {
		private:
			_3D_Models() { };
			~_3D_Models() { };
		public:
			static const std::vector<Vertex> Cube;
		};

		class Render;

		struct Mesh {
			friend class Render;
		private:
			size_t count_vertices;
			std::vector<Vertex> vertices;
			GLuint VAO, VBO, EBO;
			bool isCompile;
			bool isRecompile;
			vec3f position;
		private:
			void Recompile() {
				glBindVertexArray(this->VAO);

				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, count_vertices * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

				//?glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
				//?glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

				//Vertex Positionen
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

				//Vertex Normals
				//?glEnableVertexAttribArray(1);
				//?glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

				//Vertex Texture coordinates
				//?glEnableVertexAttribArray(2);
				//?glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

				//glBindVertexArray(0);

				isRecompile = true;
			}
			void Compile() {
				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);
				glGenBuffers(1, &this->EBO);

				//std::cout << "VAO = " << VAO << std::endl;

				Recompile();
			
				isCompile = true;
			}
		public:
			void SetPosition(vec3f pos) {
				vec3f p_temp = pos;
				pos.x -= position.x;
				pos.y -= position.y;
				pos.z -= position.z;
				position = p_temp;

				for (Vertex& v : vertices) {
					v.Position.x += pos.x;
					v.Position.y += pos.y;
					v.Position.z += pos.z;
				}

				isRecompile = false;
			}
			void Draw() {
				if ((unsigned long long)this == 0xFFFFFFFFFFFFFFCB) return;

				if (!isCompile) Compile();
				if (!isRecompile) Recompile();

				glColor4f(0.2f, 0.f, 0.f, 1.f);
				glBindVertexArray(this->VAO);

				glDrawArrays(GL_TRIANGLES, 0, count_vertices); //Начиная с вершины 0 и рисуем count_vertices штуки. Всего => count_vertices/3 треугольника
				//glDisableVertexAttribArray(0);
			}
		public:
			Mesh(std::vector<Vertex> vertices, vec3f pos = { 0.f, 0.f, 0.f }) {
				this->VAO = 0;
				this->VBO = 0;
				this->EBO = 0;

				this->isCompile = false;
				this->isRecompile = false;

				position = { 0.f, 0.f, 0.f };
				this->vertices = vertices;
				SetPosition(pos);
				this->count_vertices = vertices.size();
				//this->Compile();
			}
			~Mesh() {
				this->vertices.clear();
			}
		};
	}
}