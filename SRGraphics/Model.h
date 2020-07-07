#pragma once
#include "Mesh.h"
#include "Texture.h"
#include <string>

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
			//Material* material;
			//Mesh* mesh;
			std::vector<Material*> materials = std::vector<Material*>();
			std::vector<Mesh*>	   meshes    = std::vector<Mesh*>();
		public:
			void Draw(Shader* shader);
			void AddMesh(Mesh* mesh, Material* material) { meshes.push_back(mesh); materials.push_back(material); };
		public:
			Model() { }
			Model(std::vector<Material*> materials) {
				this->materials = materials;
			}
			Model(Mesh* mesh, Material* material) {
				this->materials.push_back(material);
				this->meshes.push_back(mesh);
			}
			~Model() {
				//material = NULL;
				//delete mesh;
			}
		};

		class ModelManager {
			const glm::vec3 negative1 = glm::vec3(-1, -1, -1);
			const glm::vec2 negative2 = glm::vec3(-1, -1, -1);
			Material* DefMat = nullptr;
		public:
			ModelManager(Debug* debug, Material* DefMat) {
				this->debug = debug;
				Models = std::map<std::string, Model*>();
				this->DefMat = DefMat;
			}
			~ModelManager() {
				//TODO: Delete all meshes!
			}
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

			void AddTriangle(std::vector<Vertex>& result, std::vector<glm::vec3> verts, std::vector<glm::vec2>& uvs, std::vector<std::string> faces) {
				vec3ui face;
				vec3ui uv;

				std::string pos_1 = String::Remove(faces[0], '/');
				std::string pos_2 = String::Remove(faces[1], '/');
				std::string pos_3 = String::Remove(faces[2], '/');

				for (unsigned char i = 0; i < 3; i++) {
					face.x = (unsigned int)atoi(pos_1.c_str());
					face.y = (unsigned int)atoi(pos_2.c_str());
					face.z = (unsigned int)atoi(pos_3.c_str());
				}

				pos_1 = String::Remove(faces[0], '/');
				pos_2 = String::Remove(faces[1], '/');
				pos_3 = String::Remove(faces[2], '/');

				for (unsigned char i = 0; i < 3; i++) {
					uv.x = (unsigned int)atoi(pos_1.c_str());
					uv.y = (unsigned int)atoi(pos_2.c_str());
					uv.z = (unsigned int)atoi(pos_3.c_str());
				}

				result.push_back({ { verts[face.x - 1.f] }, uvs[uv.x - 1.f], {0,0,0} }); //z
				result.push_back({ { verts[face.y - 1.f] }, uvs[uv.y - 1.f], {0,0,0} }); //x
				result.push_back({ { verts[face.z - 1.f] }, uvs[uv.z - 1.f], {0,0,0} }); //y
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

			Model* LoadModelFromObj(const char* path, vec3f pos = { 0, 0, 0 }) { return LoadModelFromObj(path, { }, pos); }
			Model* LoadModelFromObj(const char* path, std::vector<Material*> mats, vec3f pos = { 0, 0, 0 }) {
				debug->Log("Loading obj model : " + std::string(path));
				auto find = Models.find(path);
				if (find == Models.end()) {
					Model* model = new Model();

					size_t count_vertices = 0;
					size_t count_texcoord = 0;
					size_t count_faces    = 0;
					size_t count_meshes   = 0;

					std::vector<glm::vec3> verts = std::vector<glm::vec3>();//  verts.push_back({ 0, 0, 0 }); verts.push_back({ 0, 0, 0 }); verts.push_back({ 0, 0, 0 });
					std::vector<glm::vec2> uvs   = std::vector<glm::vec2>();
					std::vector<Vertex> final_verts = std::vector<Vertex>();

					auto addMesh = [this, &final_verts, &pos, &count_meshes, &model, &path, &count_vertices, &count_texcoord, &mats]() -> bool {
						Mesh* mesh = new Mesh(final_verts, pos);
						if (mesh->count_vertices == 0) {
							debug->Error("LoadModelFromObj() : Failed loading obj model!\n\tPath : " + std::string(path)
								+ "\n\tReason : count_vertices == 0!\n\tVerts temp : " + std::to_string(count_vertices) + "\n\tUV's temp : " + std::to_string(count_texcoord));
							Sleep(1000);
							return false;
						}
						//std::cout << mats.size() << " >= " << count_meshes << std::endl;
						if (count_meshes == 0) {
							if (mats.size() > 0) {
								if(mats[0])
									model->AddMesh(mesh, mats[0]);
								else 
									model->AddMesh(mesh, DefMat);
							}
							else model->AddMesh(mesh, DefMat);
						}
						else if (mats.size() >= count_meshes) {
							if (mats[count_meshes - 1])
								model->AddMesh(mesh, mats[count_meshes - 1]);
							else model->AddMesh(mesh, DefMat);
						}
						else model->AddMesh(mesh, DefMat);

						final_verts.clear();

						//count_meshes++;

						return true;
					};

					std::string Name = ""; std::string temp = ""; std::vector<std::string> components;
					char buffer[256] = { 0 };
					FILE* pFile = fopen(path, "r");
					bool stop = false;

					if (!pFile) {
						debug->Error("LoadModelFromObj() : Failed loading obj model!\n\tPath : " + std::string(path));
						Sleep(1000);
						return nullptr;
					}

					while (fscanf(pFile, "%s", buffer) != EOF && !stop) {
						switch (buffer[0]) {
							//!=========================[MESH NAME]==========================
							case '#': {
								fgets(buffer, sizeof(buffer), pFile);
								std::string line = buffer;
								if (line.size() > 4) {
									line = line.substr(1); line.resize(line.size() - 1);
									auto split = String::Split(line, " ", true);
									if (split.size() == 2) {
										if (split[0] == "object") {
											debug->Log("Add mesh to model : " + split[1]);
											if (count_meshes > 0)
												if (!addMesh()) return nullptr;
											count_meshes++;
										}
									}
								}

								break;
							}
							//!=========================[MESH NAME]==========================

							case 'v': {
								switch (buffer[1]) {
									case '\0': { // v
										count_vertices++;
										glm::vec3 pos;
										int i = fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z); 
										verts.push_back(pos);
										/* Needed setlocale(LC_NUMERIC, "C"); */
										//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
										break;
									}//?=======================
									case 'n': { // vn
				
										break;
									} //?=======================
									case 't': { // vt
										count_texcoord++;
										glm::vec2 pos;

										fgets(buffer, sizeof(buffer), pFile);
										temp = buffer; temp = temp.substr(1); temp.resize(temp.size() - 2);
										components = String::Split(temp, " ", true);
										pos.x = atof(components[0].c_str());
										pos.y = atof(components[1].c_str());

										//fscanf(pFile, "%f %f", &pos.x, &pos.y);
										uvs.push_back(pos);
										break;
									} //?=======================
									default:
										break;
								}
								//glm::vec3 pos;
								//fin >> pos.x >> pos.y >> pos.z;
								//verts.push_back(pos);
								//}
								//else if (s == "vt") {
								//glm::vec2 uv;
								//fin >> uv.x >> uv.y;
								//uvs.push_back(uv);
								//count_texcoord++;
								break;
							}
							case 'f': {
								count_faces++;

								fgets(buffer, sizeof(buffer), pFile);
								temp = buffer; temp = temp.substr(1); temp.resize(temp.size() - 2);

								components = String::Split(temp, " ", true);

								if (components.size() == 3)
									AddTriangle(final_verts, verts, uvs, components);
								else if (components.size() == 4)
									AddQuad(final_verts, verts, uvs, components);

								break;
							}
							default:
								fgets(buffer, sizeof(buffer), pFile);
								break;
						}
					}

					if (!addMesh()) return nullptr;

					fclose(pFile);
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