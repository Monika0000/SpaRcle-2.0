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
		public:
			ModelManager(Debug* debug) {
				this->debug = debug;
				Models = std::map<std::string, Model*>();
			}
			~ModelManager() {
				//TODO: Delete all meshes!
			}
		public:
			Model* LoadModelFromObj(const char* path, Material* mat, vec3f pos = { 0, 0, 0 }) {
				auto find = Models.find(path);
				if (find == Models.end()) {
					std::vector<glm::vec3> verts;

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
						}
						else if (s == "f") {

						}
					}
					Mesh* mesh = nullptr;//new Mesh(verts, _3D_Models::CubeUV, pos);
					Model* model = new Model(mesh, nullptr);
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