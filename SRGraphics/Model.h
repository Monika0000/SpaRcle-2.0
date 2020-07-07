#pragma once
#include "Mesh.h"
#include "Texture.h"

namespace SpaRcle {
	namespace Graphics {
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
		class Model {
		public:
			Material* material;
			Mesh* mesh;
		public:
			void Draw(Shader* shader);
		public:
			Model(Mesh* mesh, Material* material) {
				this->material = material;
				this->mesh = mesh;
			}
			~Model() {
				material = NULL;
				delete mesh;
			}
		};

		class ModelManager {
			const glm::vec3 negative1 = glm::vec3(-1, -1, -1);
			const glm::vec2 negative2 = glm::vec3(-1, -1, -1);
		public:
			ModelManager(Debug* debug) {
				this->debug = debug;
				Models = std::map<std::string, Model*>();
			}
			~ModelManager() {
				//TODO: Delete all meshes!
			}
		public:
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
			}

			void AddTriangle(std::vector<Vertex>& result, std::vector<glm::vec3> verts, std::vector<glm::vec2>& uvs, std::vector<std::string> faces) {
				glm::vec3 face;
				glm::vec3 uv;

				std::string pos_1 = String::ReadToChar(faces[0], '/');
				std::string pos_2 = String::ReadToChar(faces[1], '/');
				std::string pos_3 = String::ReadToChar(faces[2], '/');

				for (unsigned char i = 0; i < 3; i++) {
					face.x = (unsigned int)atoi(pos_1.c_str());
					face.y = (unsigned int)atoi(pos_2.c_str());
					face.z = (unsigned int)atoi(pos_3.c_str());
				}

				pos_1 = String::ReadToChar(pos_1, '/');
				pos_2 = String::ReadToChar(pos_2, '/');
				pos_3 = String::ReadToChar(pos_3, '/');

				for (unsigned char i = 0; i < 3; i++) {
					uv.x = atof(pos_1.c_str());
					uv.y = atof(pos_2.c_str());
					uv.z = atof(pos_3.c_str());
				}

				result.push_back({ { verts[face.x - 1.f] }, {0,0,0}, uvs[uv.z - 1.f] }); //z
				result.push_back({ { verts[face.y - 1.f] }, {0,0,0}, uvs[uv.x - 1.f] }); //x
				result.push_back({ { verts[face.z - 1.f] }, {0,0,0}, uvs[uv.y - 1.f] }); //y

				//? OKAY
				//result.push_back({ { verts[face.x - 1.f] }, {0,0,0}, uvs[uv.z - 1.f] }); //z
				//result.push_back({ { verts[face.y - 1.f] }, {0,0,0}, uvs[uv.x - 1.f] }); //x
				//result.push_back({ { verts[face.z - 1.f] }, {0,0,0}, uvs[uv.y - 1.f] }); //y

				//? Вывернуть наизнанку
				//result.push_back({ { verts[face.z - 1.f] * negative1, }, {0,0,0}, uvs[face.z - 1.f] });
				//result.push_back({ { verts[face.y - 1.f] * negative1, }, {0,0,0}, uvs[face.x - 1.f] });
				//result.push_back({ { verts[face.x - 1.f] * negative1, }, {0,0,0}, uvs[face.y - 1.f] });
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

				result.push_back({ { verts[face.x - 1], }, {0,0,0}, uvs[uv.x - 1] });
				result.push_back({ { verts[face.y - 1], }, {0,0,0}, uvs[uv.y - 1] });
				result.push_back({ { verts[face.z - 1], }, {0,0,0}, uvs[uv.z - 1] });

				result.push_back({ { verts[face.z - 1], }, {0,0,0}, uvs[uv.z - 1] });
				result.push_back({ { verts[face.w - 1], }, {0,0,0}, uvs[uv.w - 1] });
				result.push_back({ { verts[face.x - 1], }, {0,0,0}, uvs[uv.x - 1] });
			}

			Model* LoadModelFromObj(const char* path, Material* mat, vec3f pos = { 0, 0, 0 }) {
				auto find = Models.find(path);
				if (find == Models.end()) {
					size_t count_vertices = 0;
					size_t count_texcoord = 0;

					std::vector<glm::vec3> verts = std::vector<glm::vec3>();
					std::vector<glm::vec2> uvs   = std::vector<glm::vec2>();
					std::vector<Vertex> final_verts = std::vector<Vertex>();

					std::string s;
					std::ifstream fin(path);
					if (!fin) {
						debug->Error("LoadModelFromObj() : Failed loading obj model!\n\tPath : " + std::string(path));
						Sleep(1000);
						return nullptr;
					}
					while (fin >> s) {
						if (s == "v") {
							glm::vec3 pos;
							fin >> pos.x >> pos.y >> pos.z;
							verts.push_back(pos);
							count_vertices++;
						}
						else if (s == "vt") {
							glm::vec2 uv;
							fin >> uv.x >> uv.y;
							uvs.push_back(uv);
							count_texcoord++;
						}
						else if (s == "f") {
							std::string temp;
							std::getline(fin, temp);
							temp = temp.substr(1);
							std::vector<std::string> faces = String::Split(temp, " ");

							if (faces.size() == 3)
								AddTriangle(final_verts, verts, uvs, faces);
							else if (faces.size() == 4)
								AddQuad(final_verts, verts, uvs, faces);

							//faces.clear();
						}
					}
					fin.close();

					//for (auto v : verts)
					//	std::cout << v.x << " " << v.y << " " << v.z << std::endl;

					Mesh* mesh = new Mesh(final_verts, pos);
					if (mesh->count_vertices == 0) {
						debug->Error("LoadModelFromObj() : Failed loading obj model!\n\tPath : " + std::string(path) + "\n\tReason : count_vertices == 0!");
						Sleep(1000);
						return nullptr;
					}

					Model* model = new Model(mesh, mat);

					//model->mesh->vertices.swap(model->mesh->vertices); ??????

					return model;
				}
				else return find->second;
			}
		private:
			std::map<std::string, Model*> Models;
		private:
			Debug* debug;
		};
	}
}