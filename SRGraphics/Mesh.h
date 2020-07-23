#pragma once
//#include "Material.h"
#include "Vectors.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <Vector3.h>
#include <SRHelper.h>

namespace SpaRcle {
	namespace Graphics {
		using namespace Helper;

		struct Vertex {
		//public:
			glm::vec3 Position;
		 	glm::vec2 TexCoords;
			glm::vec3 Normal;
			glm::vec3 Tangent;

			//public:
		//	Vertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 TexCoords) : Position(Position), Normal(Normal), TexCoords(TexCoords) {};
			//Vertex(vec3f Position, vec3f Normal, vec3f TexCoords) : 
			//	Position(Position.x, Position.y, Position.z), 
			//	Normal(Normal.x, Normal.y, Normal.z),
			//	TexCoords(TexCoords.x, TexCoords.y) {};
		//	~Vertex() {};
		};

		class Render;
		class Model;
		class ModelManager;
		class Shader;
		class Texture;

		struct Mesh {
			friend class Render;
			friend class Model;
			friend class ModelManager;
		private:
			size_t count_vertices;
			std::vector<Vertex> vertices;
			//std::vector<glm::vec3> vertices;
			//std::vector<glm::vec2> uvs;
			GLuint VAO, VBO;//, EBO, UV;

			bool isGenerate;
			bool isBind;
			glm::vec3 position;
		private:
			void Bind() {
				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);

				//? [VERTEX]
				glBufferData(GL_ARRAY_BUFFER, count_vertices * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

				//? [TEXTURE]
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

				//? [NORMAL]
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,	sizeof(Vertex), (void*)offsetof(Vertex, Normal));

				//? [TANGENT]
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

				glBindVertexArray(0);
				
				//this->count_vertices = 0;
				//this->vertices.clear();

				isBind = true;
			}
			void Generate() {
				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);

				isGenerate = true;
			}
		public:
			void SetPosition(glm::vec3 pos) {
				position = pos;
				//vec3f p_temp = pos;
				//pos.x -= position.x;
				////pos.y -= position.y;
				//pos.z -= position.z;
				//position = p_temp;

				//for (auto& v : vertices) {
				//	v.Position.x += pos.x;
				//	v.Position.y += pos.y;
				//	v.Position.z += pos.z;
				//}

				//isBind = false;
			}
			void Draw();
			void FlatDraw();
			//void Bind() const {
			//	glBindVertexArray(this->VAO);
			//}
		public:
			Mesh(std::vector<Vertex> vertices, glm::vec3 pos = { 0.f, 0.f, 0.f }, size_t count_vertices = Math::size_t_max) {
			//Mesh(Data* data, vec3f pos = { 0.f, 0.f, 0.f }) {
			//Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, vec3f pos = { 0.f, 0.f, 0.f }) {
				this->VAO = 0;
				this->VBO = 0;
				//this->EBO = 0;

				this->isBind = false;
				this->isGenerate= false;

				this->position = pos;
				//position = { 0.f, 0.f, 0.f };

				this->vertices = vertices;
				//this->uvs= uvs;

				//SetPosition(pos);
				if(count_vertices == Math::size_t_max)
					this->count_vertices = vertices.size();
				if (this->count_vertices == 0) {
					Debug::InternalError("Mesh constructor : count_vertices == 0!");
					Sleep(1000);
				}
				//this->Compile();
			}
			~Mesh() {
				//this->verts.clear();
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
			/*
			inline static std::vector<Vertex> CubeVertex = {
				// SOUTH
				{ { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },
				
				// EAST
				{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },

				// NORTH
				{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },

				// WEST
				{ { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },

				// TOP
				{ { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },

				// BOTTOM
				{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0, 0, 0 } },		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },
				{ { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, { 0, 0, 0 } },		{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 0, 0, 0 } },		{ { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0, 0, 0 } },
			};*/
		};
	}
}