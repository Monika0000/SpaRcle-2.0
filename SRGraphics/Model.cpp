#include "pch.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	namespace Graphics {
		bool SpaRcle::Graphics::Model::Draw(Shader* shader) {
			if (destroy) return false;

			for (auto& mat : materials) {
				if (!mat) return true;
				if (!mat->isGenerate) mat->Generate();
			}

			for (t = 0; t < meshes.size(); t++) {
				if (materials[t]->diffuse) {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, materials[t]->diffuse->id);
					texID = glGetUniformLocation(shader->ProgramID, "DiffuseMap");
					glUniform1i(texID, 0); // This is GL_TEXTURE0
				}
				if (materials[t]->normal) {
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, materials[t]->normal->id);
					texID = glGetUniformLocation(shader->ProgramID, "NormalMap");
					glUniform1i(texID, 1); // This is GL_TEXTURE1
				}

				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				position = glGetUniformLocation(shader->ProgramID, "ObjPos");
				//glm::vec3 pos = { 10, 10, 100 };
				glUniform3fv(position, 1, &meshes[t]->position[0]);

				meshes[t]->Draw();

				glBindTexture(GL_TEXTURE_2D, 0);
				glActiveTexture(GL_TEXTURE0);
			}

			return true;
		}

		void Model::FlatDraw(size_t number, Shader* shader) {
			if (destroy) return;

			for (t = 0; t < meshes.size(); t++) {
				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				position = glGetUniformLocation(shader->ProgramID, "ObjPos");
				glUniform3fv(position, 1, &meshes[t]->position[0]);

				float* color = GraphUtils::TransliteFloatColor(number + 1, 0, 0);
				texID = glGetUniformLocation(shader->ProgramID, "color");
				glUniform3fv(texID, 1, &color[0]);

				meshes[t]->FlatDraw();
			}
		}

		Model* SpaRcle::Graphics::ModelManager::LoadModelFromObj(const char* file, std::vector<Material*> mats, glm::vec3 pos) {
			std::string path = graph->GetResourcesFolder() + "\\" + std::string(file);

			path = String::ReplaceAll(path, "\\\\", "\\");
			path = String::ReplaceAll(path, "/", "\\");

			auto find = Models.find(path);
			if (find == Models.end()) {
				debug->Log("Loading obj model : " + std::string(path));

				Model* model = new Model();

				size_t count_vertices = 0;
				size_t count_texcoord = 0;
				size_t count_faces = 0;
				size_t count_meshes = 0;

				std::vector<glm::vec3> verts = std::vector<glm::vec3>();//  verts.push_back({ 0, 0, 0 }); verts.push_back({ 0, 0, 0 }); verts.push_back({ 0, 0, 0 });
				std::vector<glm::vec2> uvs = std::vector<glm::vec2>();
				std::vector<glm::vec3> normals = std::vector<glm::vec3>();
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
							if (mats[0])
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
				FILE* pFile = fopen(path.c_str(), "r");
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
							glm::vec3 pos;
							int i = fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
							normals.push_back(pos);
							break;
						} //?=======================
						case 't': { // vt
							count_texcoord++;
							glm::vec2 pos;

							fgets(buffer, sizeof(buffer), pFile);
							temp = buffer; temp = temp.substr(1); temp.resize(temp.size() - 1); //TODO: Or  temp.resize(temp.size() - 2);
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
						temp = buffer; temp = temp.substr(1); temp.resize(temp.size() - 1);

						components = String::Split(temp, " ", true);

						if (components.size() == 3)
							AddTriangle(final_verts, verts, uvs, normals, components);
						//else if (components.size() == 4)
						//	AddQuad(final_verts, verts, uvs, components);

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
	}
}