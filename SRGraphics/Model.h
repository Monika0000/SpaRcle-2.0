#pragma once
#include "Mesh.h"
#include "Texture.h"
#include <string>
#include <Interfaces.h>

namespace SpaRcle {
	namespace Graphics {
		using namespace Helper;

		/*
		struct Object3D {
		public:
			Object3D() {
				_mesh = nullptr;
				pos = new Vector3{ 0.f, 0.f, 0.f };
				scale = 1;
			};
			~Object3D() {
				if (_mesh) delete _mesh;
				delete pos;
			};
			Mesh* _mesh;
			void SetPosition(float x, float y, float z) {
				pos->x = x;
				pos->y = y;
				pos->z = z;

				_mesh->tris.clear();
				_mesh->tris = {
					// SOUTH
					{ 0.0f + x, 0.0f + y, 0.0f + z,    0.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z},
					{ 0.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 0.0f + y, 0.0f + z},

					// EAST                                                      
					{ 1.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z},
					{ 1.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 0.0f + y, 1.0f + z},

					// NORTH                                                     
					{ 1.0f + x, 0.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z},
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 1.0f + z},

					// WEST                                                      
					{ 0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 0.0f + z},
					{ 0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 0.0f + z,    0.0f + x, 0.0f + y, 0.0f + z},

					// TOP                                                       
					{ 0.0f + x, 1.0f + y, 0.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 1.0f + z},
					{ 0.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 0.0f + z},

					// BOTTOM                                                    
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 0.0f + z},
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 0.0f + y, 0.0f + z},
				};
			}
			float scale;
		private:
			Vector3* pos;
		};

		struct Cube : public Object3D {
			Cube(float x, float y, float z) {
				//pos->x = x;
				//pos->y = y;
				//pos->z = z;

				_mesh = new Mesh();
				_mesh->count = 12;

				//triangle t = { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f };

				_mesh->tris = {
					// SOUTH
					{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

					// EAST                                                      
					{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

					// NORTH                                                     
					{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

					// WEST                                                      
					{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
					{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

					// TOP                                                       
					{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
					{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

					// BOTTOM                                                    
					{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
					{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
				};

				SetPosition(x, y, z);
			};
		};
		*/

		class Shader;
		class Model : public IComponent {
		private:
			GLuint position = 0;
			GLuint texID    = 0;
			size_t t        = 0;
		private:
			bool destroy = false;
		public:
			bool isSelect  = false;
			bool CanSelect = true;
			bool enabled   = true;
			//Material* material;
			//Mesh* mesh;
			std::vector<Material*> materials = std::vector<Material*>();
			std::vector<Mesh*>	   meshes    = std::vector<Mesh*>();
		public:
			void SetPosition(glm::vec3 val) { for (auto& a : this->meshes) a->SetPosition(val); }
			void SetRotation(glm::vec3 val) { for (auto& a : this->meshes) a->SetRotation(val); }
			void SetScale   (glm::vec3 val) { for (auto& a : this->meshes) a->SetScale   (val); }
		public:
			void Destroy() { this->destroy = true; enabled = false; }
			bool Draw(Shader* shader);
			void FlatDraw(size_t number, Shader* shader); //, float scale_modifer = 0.f
			//void DrawSencil(Shader* stencil, Shader* shader);
			void DrawSencil(Shader* stencil);
			void AddMesh(Mesh* mesh, Material* material) { meshes.push_back(mesh); materials.push_back(material); };
		public:
			Model() { 
				enabled = true;
			}
			Model(std::vector<Material*> materials) {
				enabled = true;
				this->materials = materials;
			}
			Model(Mesh* mesh, Material* material) {
				enabled = true;
				this->materials.push_back(material);
				this->meshes.push_back(mesh);
			}
			~Model() {
				enabled = false;
				for (auto mesh : meshes)   mesh = nullptr;
				for (auto mat : materials) mat = nullptr;
			}
		};

		class ModelManager : public IResourceManager {
			const glm::vec3 negative1 = glm::vec3(-1, -1, -1);
			const glm::vec2 negative2 = glm::vec3(-1, -1, -1);
			Material* DefMat = nullptr;
		public:
			ModelManager(Debug* debug, SRGraphics* graph, Material* DefMat) : IResourceManager(debug, graph) {
				Models = std::map<std::string, Model*>();
				this->DefMat = DefMat;
			}
			~ModelManager() {
				//TODO: Delete all meshes!
			}
		private:
			std::vector<glm::vec3> verts = std::vector<glm::vec3>();
			std::vector<glm::vec2> uvs = std::vector<glm::vec2>();
			std::vector<glm::vec3> normals = std::vector<glm::vec3>();
			std::vector<Vertex> final_verts = std::vector<Vertex>();
			std::string Current_mesh = "";
			size_t count_meshes = 0; size_t count_uncorrect_triangles = 0;
		private:
			std::string pos_1 = "";
			std::string pos_2 = "";
			std::string pos_3 = "";
		public:
			/*
			std::vector<Vertex> MakeModel(std::vector<glm::vec3>& vetexes, std::vector<vec3ui>& faces) {
				std::vector<Vertex> final_verts = std::vector<Vertex>();
				for (size_t t = 0; t < faces.size(); t++) {
					std::cout << faces[t].x - 1 << std::endl;
					std::cout << faces[t].y - 1 << std::endl;
					std::cout << faces[t].z - 1 << std::endl;
					glm::vec3& vert = vetexes[faces[t].x - 1];
					final_verts.push_back({ { vert.x, vert.y, vert.z }, { 0,0,0 }, { 0,0 } });
					vert = vetexes[faces[t].y - 1];
					final_verts.push_back({ { vert.x, vert.y, vert.z }, { 0,0,0 }, { 0,0 } });
					vert = vetexes[faces[t].z - 1];
					final_verts.push_back({ { vert.x, vert.y, vert.z }, { 0,0,0 }, { 0,0 } });
				}
				return final_verts;
			}*/

			bool Close() override {
				return false;
			}

			void AddTriangle(std::vector<Vertex>& result, std::vector<glm::vec3> verts, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals, std::vector<std::string> faces) {
				vec3ui face;
				vec3ui uv;
				vec3ui normal;

				{ //? VERTEX
					pos_1 = String::Remove(faces[0], '/');
					pos_2 = String::Remove(faces[1], '/');
					pos_3 = String::Remove(faces[2], '/');

					for (unsigned char i = 0; i < 3; i++) {
						face.x = (unsigned int)atoi(pos_1.c_str());
						face.y = (unsigned int)atoi(pos_2.c_str());
						face.z = (unsigned int)atoi(pos_3.c_str());
					}
				}

				{ //? TEXTURE COORD
					pos_1 = String::Remove(faces[0], '/');
					pos_2 = String::Remove(faces[1], '/');
					pos_3 = String::Remove(faces[2], '/');

					for (unsigned char i = 0; i < 3; i++) {
						uv.x = (unsigned int)atoi(pos_1.c_str());
						uv.y = (unsigned int)atoi(pos_2.c_str());
						uv.z = (unsigned int)atoi(pos_3.c_str());
					}
				}

				if (normals.size() > 0) { //? NORMAL
					pos_1 = String::Remove(faces[0], '/');
					pos_2 = String::Remove(faces[1], '/');
					pos_3 = String::Remove(faces[2], '/');

					for (unsigned char i = 0; i < 3; i++) {
						normal.x = (unsigned int)atoi(pos_1.c_str());
						normal.y = (unsigned int)atoi(pos_2.c_str());
						normal.z = (unsigned int)atoi(pos_3.c_str());
					}
					
					//!====================================[TANGENT]========================================
					glm::vec3 edge1 = verts[face.y - 1.f] - verts[face.x - 1.f];	// pos2 - pos1
					glm::vec3 edge2 = verts[face.z - 1.f] - verts[face.x - 1.f];    // pos3 - pos1
					glm::vec2 deltaUV1 = uvs[uv.y - 1.f] - uvs[uv.x - 1.f];			// uv2 - uv1
					glm::vec2 deltaUV2 = uvs[uv.z - 1.f] - uvs[uv.x - 1.f];			// uv3 - uv1

					float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

					float tan_x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
					float tan_y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
					float tan_z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
					//!====================================[TANGENT]========================================

					result.push_back({ { verts[face.x - 1.f] }, uvs[uv.x - 1.f], normals[normal.x - 1], {tan_x,tan_y,tan_z} }); //z
					result.push_back({ { verts[face.y - 1.f] }, uvs[uv.y - 1.f], normals[normal.y - 1], {tan_x,tan_y,tan_z} }); //x
					result.push_back({ { verts[face.z - 1.f] }, uvs[uv.z - 1.f], normals[normal.z - 1], {tan_x,tan_y,tan_z} }); //y
				}
				else {
					result.push_back({ { verts[face.x - 1.f] }, uvs[uv.x - 1.f], {0,0,0} }); //z
					result.push_back({ { verts[face.y - 1.f] }, uvs[uv.y - 1.f], {0,0,0} }); //x
					result.push_back({ { verts[face.z - 1.f] }, uvs[uv.z - 1.f], {0,0,0} }); //y
				}
			}
			void AddQuad(std::vector<Vertex>& result, std::vector<glm::vec3> verts, std::vector<glm::vec2>& uvs, std::vector<std::string> faces) {
				glm::vec4 face;
				glm::vec4 uv;

				std::string pos_1 = String::ReadToChar(faces[0], '/');
				std::string pos_2 = String::ReadToChar(faces[1], '/');
				std::string pos_3 = String::ReadToChar(faces[2], '/');
				std::string pos_4 = String::ReadToChar(faces[3], '/');

				for (unsigned char i = 0; i < 4; i++) {
					face.x = (unsigned int)atoi(pos_1.c_str());
					face.y = (unsigned int)atoi(pos_2.c_str());
					face.z = (unsigned int)atoi(pos_3.c_str());
					face.w = (unsigned int)atoi(pos_4.c_str());
				}

				pos_1 = String::ReadToChar(pos_1, '/');
				pos_2 = String::ReadToChar(pos_2, '/');
				pos_3 = String::ReadToChar(pos_3, '/');
				pos_4 = String::ReadToChar(pos_4, '/');

				for (unsigned char i = 0; i < 4; i++) {
					uv.x = atof(pos_1.c_str());
					uv.y = atof(pos_2.c_str());
					uv.z = atof(pos_3.c_str());
					uv.w = atof(pos_4.c_str());
				}

				result.push_back({ verts[face.x - 1], uvs[uv.x - 1], {0,0,0} });
				result.push_back({ verts[face.y - 1], uvs[uv.y - 1], {0,0,0} });
				result.push_back({ verts[face.z - 1], uvs[uv.w - 1], {0,0,0} });

				result.push_back({ verts[face.z - 1], uvs[uv.w - 1], {0,0,0} });
				result.push_back({ verts[face.w - 1], uvs[uv.z - 1], {0,0,0} });
				result.push_back({ verts[face.x - 1], uvs[uv.x - 1], {0,0,0} });
			}

			bool AddMeshToModel(Model* model, std::string name, std::vector<Material*>& mats, glm::vec3& pos);

			Model* LoadModelFromObj(const char* path, glm::vec3 pos = { 0, 0, 0 }) { return LoadModelFromObj(path, { }, pos); }
			Model* LoadModelFromObj(const char* file, std::vector<Material*> mats, glm::vec3 pos = { 0, 0, 0 });
		private:
			std::map<std::string, Model*> Models;
		};
	}
}