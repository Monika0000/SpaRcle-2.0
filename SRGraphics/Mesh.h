#pragma once
//#include "Material.h"
#include "Vectors.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <Vector3.h>
#include <SRHelper.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

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
			void SetPosition(float x, float y, float z) { Position = { x, y, z }; };
		};

		class Render;
		class Model;
		class ModelManager;
		class Shader;
		class Texture;
		class FbxLoader;

		struct Mesh {
			friend class Render;
			friend class Model;
			friend class ModelManager;
			friend class FbxLoader;
		public:
			size_t GeometryID		 = 0;
			std::string GeometryName = "";
		public:
			float min_x = 0.f, min_y = 0.f, min_z = 0.f,
				  max_x = 0.f, max_y = 0.f, max_z = 0.f;
		private:
			void UpdateMatrix();
		private:
			size_t count_vertices;
			std::vector<Vertex> vertices;

			GLuint VAO, VBO;//, EBO, UV;

			glm::mat4 model = glm::mat4(1.0f);

			bool isGenerate;
			bool isBind;

			glm::vec3 position = { 0, 0, 0 };
			glm::vec3 rotation = { 0, 0, 0 };
			glm::vec3 scale	   = { 1, 1, 1 };

			glm::vec3 default_position = { 0, 0, 0 };
			glm::vec3 default_rotation = { 0, 0, 0 };
			glm::vec3 default_scale	   = { 1, 1, 1 };
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
			void SetBind(bool v) { this->isBind = v; }
			Vertex* GetVertex(size_t index) { return &vertices[index]; }
			void SetPosition(glm::vec3 pos) { position = pos; UpdateMatrix(); }
			void SetRotation(glm::vec3 rot) { 
				//const float angle = 1.f; // radians

				//float x = rot.x * sin(angle / 2.f); //RotationAngle / 2
				//float y = rot.y * sin(angle / 2.f); //RotationAngle / 2
				//float z = rot.z * sin(angle / 2.f); //RotationAngle / 2
				//float w =         cos(angle / 2.f); //RotationAngle / 2

				//rotation = glm::angleAxis(angle, rot);
				//rotation = { x, y, z, w };

				rotation = rot;
				UpdateMatrix();
			}
			void SetScale   (glm::vec3 scl) { 
				//glm::vec3 delta = scl - scale;
				scale    = scl; 
				
				UpdateMatrix(); 
			}
		public:
			void Draw();
			void FlatDraw();
		public:
			Mesh* Copy() {
				Mesh* mesh = new Mesh(vertices);

				mesh->default_position = this->default_position;
				mesh->default_rotation = this->default_rotation;
				mesh->default_scale    = this->default_scale;

				mesh->SetPosition(position);
				mesh->SetRotation(rotation);
				mesh->SetScale(scale);
				mesh->isBind = isBind;
				mesh->isGenerate = isGenerate;

				mesh->max_x = max_x; mesh->min_x = min_x;
				mesh->max_y = max_y; mesh->min_y = min_y;
				mesh->max_z = max_z; mesh->min_z = min_z;

				mesh->model = model;

				mesh->VAO = VAO;
				mesh->VBO = VBO;
				mesh->count_vertices = count_vertices;

				mesh->GeometryID   = GeometryID;
				mesh->GeometryName = GeometryName;

				return mesh;
			}
			Mesh(std::vector<Vertex> vertices, glm::vec3 pos = { 0.f, 0.f, 0.f }, size_t count_vertices = Math::size_t_max) {
			//Mesh(Data* data, vec3f pos = { 0.f, 0.f, 0.f }) {
			//Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, vec3f pos = { 0.f, 0.f, 0.f }) {
				this->VAO = 0;
				this->VBO = 0;
				//this->EBO = 0;

				this->isBind = false;
				this->isGenerate= false;

				this->position = pos;

				this->vertices = vertices;
				//this->uvs= uvs;

				//SetPosition(pos);
				if(count_vertices == Math::size_t_max)
					this->count_vertices = vertices.size();
				if (this->count_vertices == 0) {
					Debug::InternalError("Mesh constructor : count_vertices == 0!");
					Sleep(500);
					return;
				} else {
					max_x = vertices[0].Position.x;
					min_x = vertices[0].Position.x;

					max_y = vertices[0].Position.y;
					min_y = vertices[0].Position.y;

					max_z = vertices[0].Position.z;
					min_z = vertices[0].Position.z;

					for (size_t t = 1; t < this->count_vertices; t++) {
						if (vertices[t].Position.x > max_x) max_x = vertices[t].Position.x;
						else if (vertices[t].Position.x < min_x) min_x = vertices[t].Position.x;

						if (vertices[t].Position.y > max_y) max_y = vertices[t].Position.y;
						else if (vertices[t].Position.y < min_y) min_y = vertices[t].Position.y;

						if (vertices[t].Position.z > max_z) max_z = vertices[t].Position.z;
						else if (vertices[t].Position.z < min_z) min_z = vertices[t].Position.z;
					}
				}
				//this->Compile();

				this->UpdateMatrix();
			}
			~Mesh() {
				//this->verts.clear();
			}
		};
		/*
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
			};
		}; */
	}
}