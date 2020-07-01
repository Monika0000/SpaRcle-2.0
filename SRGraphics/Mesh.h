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

		static const GLfloat g_uv_buffer_data[] = {
			0.000059f, 1.0f - 0.000004f,
			0.000103f, 1.0f - 0.336048f,
			0.335973f, 1.0f - 0.335903f,
			1.000023f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.999958f, 1.0f - 0.336064f,	
			0.667979f, 1.0f - 0.335851f,
			0.336024f, 1.0f - 0.671877f,
			0.667969f, 1.0f - 0.671889f,
			1.000023f, 1.0f - 0.000013f,
			0.668104f, 1.0f - 0.000013f,
			0.667979f, 1.0f - 0.335851f,
			0.000059f, 1.0f - 0.000004f,
			0.335973f, 1.0f - 0.335903f,
			0.336098f, 1.0f - 0.000071f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.336024f, 1.0f - 0.671877f,
			1.000004f, 1.0f - 0.671847f,
			0.999958f, 1.0f - 0.336064f,
			0.667979f, 1.0f - 0.335851f,
			0.668104f, 1.0f - 0.000013f,
			0.335973f, 1.0f - 0.335903f,
			0.667979f, 1.0f - 0.335851f,
			0.335973f, 1.0f - 0.335903f,
			0.668104f, 1.0f - 0.000013f,
			0.336098f, 1.0f - 0.000071f,
			0.000103f, 1.0f - 0.336048f,
			0.000004f, 1.0f - 0.671870f,
			0.336024f, 1.0f - 0.671877f,
			0.000103f, 1.0f - 0.336048f,
			0.336024f, 1.0f - 0.671877f,
			0.335973f, 1.0f - 0.335903f,
			0.667969f, 1.0f - 0.671889f,
			1.000004f, 1.0f - 0.671847f,
			0.667979f, 1.0f - 0.335851f
		};

		//struct Vertex {
		//	glm::vec3 Position;
		//	glm::vec3 Normal;
		// 	glm::vec2 TexCoords;
		//};

		class Render;
		class Model;
		class Shader;
		class Texture;

		struct Mesh {
			friend class Render;
			friend class Model;
		private:
			size_t count_vertices;
			//std::vector<Vertex> vertices;
			std::vector<glm::vec3> verts;
			std::vector<glm::vec2> uvs;
			GLuint VAO, VBO, EBO, UV;

			bool isCompile;
			bool isRecompile;
			vec3f position;
		private:
			void Recompile() {
				glBindVertexArray(VAO);

				//? [VERTEX]
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, count_vertices * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);

				//? [TEXTURE]
				glBindBuffer(GL_ARRAY_BUFFER, UV);
				glBufferData(GL_ARRAY_BUFFER, count_vertices * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

				//glBufferData(GL_ARRAY_BUFFER, count_vertices * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

				//std::vector<glm::vec3> vt = {
				//	{ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }
				//};
				//glBufferData(GL_ARRAY_BUFFER, vt.size() * sizeof(glm::vec3), &vt[0], GL_STATIC_DRAW);

				//unsigned int indices[] = {
				//	0, 1, 3, // first triangle
				//	1, 2, 3,  // second triangle
				//};
				//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
				//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

				//Vertex Positionen
				///glEnableVertexAttribArray(0);
				///glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

				//Vertex Positionen
				///!glEnableVertexAttribArray(0);
				///!glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);

				//glEnableVertexAttribArray(2);
				//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, size, (GLvoid*)(6 * sizeof(float)));

				/*
				// position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				// color attribute
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
				glEnableVertexAttribArray(1);
				// texture coord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
				glEnableVertexAttribArray(2);
				*/

				/*
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
				*/

				isRecompile = true;
			}
			void Compile() {
				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);
				glGenBuffers(1, &this->EBO);
				glGenBuffers(1, &this->UV);

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

				for (glm::vec3& v : verts) {
					v.x += pos.x;
					v.y += pos.y;
					v.z += pos.z;
				}

				isRecompile = false;
			}
			void Draw();
			void Bind() const {
				glBindVertexArray(this->VAO);
			}
		public:
			//Mesh(std::vector<Vertex> vertices, vec3f pos = { 0.f, 0.f, 0.f }) {
			//Mesh(Data* data, vec3f pos = { 0.f, 0.f, 0.f }) {
			Mesh(std::vector<glm::vec3> verts, std::vector<glm::vec2> uvs, vec3f pos = { 0.f, 0.f, 0.f }) {
				this->VAO = 0;
				this->VBO = 0;
				this->EBO = 0;

				this->isCompile = false;
				this->isRecompile = false;

				position = { 0.f, 0.f, 0.f };

				this->verts = verts;
				this->uvs= uvs;

				SetPosition(pos);
				this->count_vertices = verts.size();
				//this->Compile();
			}
			~Mesh() {
				this->verts.clear();
			}
		};

		class _3D_Models {
		private:
			_3D_Models() { };
			~_3D_Models() { };
		public:
			//static const std::vector<Vertex> Cube;
			inline static std::vector<glm::vec3> Cube = { // по часовой
				// SOUTH
				{ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, 
				{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },

				// EAST
				{ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f },

				// NORTH
				{ 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f },

				// WEST
				{ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f },
				{ 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },

				// TOP
				{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f },

				// BOTTOM
				{ 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
			};
			inline static std::vector<glm::vec2> CubeUV = { // против часовой
				// SOUTH
				//{ 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f },
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f }, 

				// EAST
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f },

				// NORTH
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f },

				// WEST
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f },

				// TOP
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f },

				// BOTTOM
				{ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f },
				{ 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f },
			};
		};
	}
}