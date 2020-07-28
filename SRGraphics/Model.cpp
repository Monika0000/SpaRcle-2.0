#include "pch.h"
#include "Model.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	namespace Graphics {
		Material* model_temp_material = nullptr;
		bool SpaRcle::Graphics::Model::Draw(Shader* shader) {
			if (destroy) return false;

			for (auto& mat : materials) {
				if (!mat) return true;
				if (!mat->isGenerate) mat->Generate();
			}

			for (t = 0; t < meshes.size(); t++) {
				model_temp_material = materials[t];

				//std::cout << meshes.size() << std::endl;

				if (model_temp_material->diffuse) {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, model_temp_material->diffuse->id);
					glUniform1i(glGetUniformLocation(shader->ProgramID, "DiffuseMap"), 0); // This is GL_TEXTURE0
				}
				if (model_temp_material->normal) {
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, model_temp_material->normal->id);
					glUniform1i(glGetUniformLocation(shader->ProgramID, "NormalMap"), 1); // This is GL_TEXTURE1
				}

				//glm::vec4 c = model_temp_material->Color;
				//std::cout << c.r << " " << c.g << " " << c.b << "\n";

				glUniform4fv(glGetUniformLocation(shader->ProgramID, "color"), 1, &model_temp_material->Color[0]);
				//std::cout << model_temp_material->use_light << std::endl;
				//glUniform1i(glGetUniformLocation(shader->ProgramID, "use_light"), model_temp_material->use_light);

				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				//position = glGetUniformLocation(shader->ProgramID, "ObjPos");
				//glUniform3fv(position, 1, &meshes[t]->position[0]);

				//glm::mat4 model = glm::mat4(1.0f);
				//model = glm::translate(model, meshes[t]->position);
				//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
				glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(meshes[t]->model));

				meshes[t]->Draw();

				glBindTexture(GL_TEXTURE_2D, 0);
				glActiveTexture(GL_TEXTURE0);
			}

			return true;
		}

		void Model::FlatDraw(size_t number, Shader* shader) {//, float scale_modifer
			if (destroy || !CanSelect) return;

			for (t = 0; t < meshes.size(); t++) {
				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				//position = glGetUniformLocation(shader->ProgramID, "ObjPos");
				//glUniform3fv(position, 1, &meshes[t]->position[0]);

				//glm::mat4 model = glm::mat4(1.0f);
				//model = glm::translate(model, meshes[t]->position);
				//model = glm::scale(model, glm::vec3(1.f + scale_modifer, 1.f + scale_modifer, 1.f + scale_modifer));
				glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(meshes[t]->model));

				vec3uc c = GraphUtils::IntToColor(number + 1);
				float* color = GraphUtils::TransliteFloatColor((unsigned int)c.x, (unsigned int)c.y, (unsigned int)c.z);
				//float* color = GraphUtils::TransliteFloatColor(0, 0, number + 1);
				//std::cout << "flat : " << color[0] << " " << color[1] << " " << color[2] << "\n";

				texID = glGetUniformLocation(shader->ProgramID, "color");
				glUniform3fv(texID, 1, &color[0]);

				delete color;

				meshes[t]->FlatDraw();
			}
		}

		/*
		void Model::DrawSencil(Shader* stencil, Shader* shader) {
			if (destroy) return;

			stencil->Use();

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);

			for (t = 0; t < meshes.size(); t++) {
				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3{ meshes[t]->position.x, meshes[t]->position.y, meshes[t]->position.z });
				glUniformMatrix4fv(glGetUniformLocation(stencil->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(model));


				meshes[t]->FlatDraw();
			}

			//?========================================================

			//glBindFramebuffer(GL_READ_FRAMEBUFFER, Render::defaultFBO);
			//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Render::silhouetteFBO);

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);

			shader->Use();

			Draw(shader);

			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);

			//glBindFramebuffer(GL_FRAMEBUFFER, Render::defaultFBO);
		}*/
		void Model::DrawSencil(Shader* shader) {
			for (t = 0; t < meshes.size(); t++) {
				if (!meshes[t]->isGenerate) meshes[t]->Generate();
				if (!meshes[t]->isBind) meshes[t]->Bind();

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3{ meshes[t]->position.x, meshes[t]->position.y, meshes[t]->position.z });
				glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "modelMat"), 1, GL_FALSE, glm::value_ptr(model));

				meshes[t]->FlatDraw();
			}
		}



		bool ModelManager::AddMeshToModel(Model* model, std::string name, std::vector<Material*>& mats, glm::vec3& pos) {
			if (Current_mesh == "") {
				Current_mesh = name;
				return true;
			}

			if(final_verts.size() != 0)
				debug->Log("Add mesh to model : " + Current_mesh);
			else {
				debug->Error("Failed add mesh to model : " + Current_mesh);
				return false;
			}

			//?=========================================================
			Mesh* mesh = new Mesh(final_verts, pos);

			count_meshes++;

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

			//?=========================================================

			Current_mesh = name;
			return true;
		}

		std::string ReadLine(FILE*pFile) {
			char buffer[256] = { 0 };
			fgets(buffer, sizeof(buffer), pFile);
			std::string line = buffer;
			line.resize(line.size() - 1);
			return line.substr(1);
		}

		Model* ModelManager::LoadModelFromObj(const char* file, std::vector<Material*> mats, glm::vec3 pos) {
			std::string path = graph->GetResourcesFolder() + "\\Models\\" + std::string(file);
			path = String::MakePath(path);
			auto find = Models.find(path);
			if (find != Models.end())
				return find->second;

			debug->Log("Loading obj model : " + std::string(path));

			verts.clear(); uvs.clear(); normals.clear(); final_verts.clear(); Current_mesh = ""; count_meshes = 0; count_uncorrect_triangles = 0;

			Model* model = new Model();

			char buffer[256] = { 0 }; std::string temp = ""; std::vector<std::string> components;
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
						auto sp = String::Split(ReadLine(pFile), " ");
						if (sp.size() > 1) if (sp[0] == "object") AddMeshToModel(model, sp[1], mats, pos);
						break;
					}
					case 'g': {
						AddMeshToModel(model, ReadLine(pFile), mats, pos);
						break;
					}
					case 'o': {
						if (std::string(buffer) == "off") break;
						AddMeshToModel(model, ReadLine(pFile), mats, pos);
						break;
					}
					//!=========================[MESH NAME]==========================
					case 'v': {
						switch (buffer[1]) {
							case '\0': { // v
								glm::vec3 pos;
								int i = fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
								verts.push_back(pos);
								//? Needed setlocale(LC_NUMERIC, "C"); 
								//? std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
								break;
							}//?=======================
							case 'n': { // vn
								glm::vec3 pos;
								int i = fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
								normals.push_back(pos);
								break;
							} //?=======================
							case 't': { // vt
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
							default: break;
						}

						break;
					}
					case 'f': {
						fgets(buffer, sizeof(buffer), pFile);
						temp = buffer; temp = temp.substr(1); temp.resize(temp.size() - 1);

						components = String::Split(temp, " ", true);

						if (components.size() == 3)
							AddTriangle(final_verts, verts, uvs, normals, components);
						else count_uncorrect_triangles++;

						break;
					}
					default: fgets(buffer, sizeof(buffer), pFile); break;
				}
			}

			AddMeshToModel(model, "end", mats, pos);

			fclose(pFile);

			if (count_meshes > 0) {
				this->Models.insert(std::make_pair(path, model));
				if (count_uncorrect_triangles > 0)
					debug->Warn("When loading the model, incorrect polygons were found, possibly triangulation is required. \n\tPath : " +
						path + "\n\tCount error polygons : " + std::to_string(count_uncorrect_triangles));
				return model;
			}
			else {
				debug->Error("Failed loading model : " + path + 
					"\n\tReason : count meshes is zero!\n\tSolution : possibly triangulation is required");
				return nullptr;
			}
		}
		
		/*
		Model* SpaRcle::Graphics::ModelManager::LoadModelFromObj(const char* file, std::vector<Material*> mats, glm::vec3 pos) {
			std::string path = graph->GetResourcesFolder() + "\\Models\\" + std::string(file);

			//path = String::ReplaceAll(path, "\\\\", "\\");
			//path = String::ReplaceAll(path, "/", "\\");
			path = String::MakePath(path);

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
					case 'g': {
						temp = ReadLine(pFile);
						//fgets(buffer, sizeof(buffer), pFile);
						//std::string line = buffer;
						//line.resize(line.size() - 1);

						//debug->Log("Add mesh to model : " + line.substr(1) + " (g)");
						debug->Log("Add mesh to model : " + temp + " (g)");

						if (count_meshes > 0)
							if (!addMesh()) return nullptr;
						count_meshes++;
						break;
					}
					case 'o': {
						if (std::string(buffer) == "off") break;

						temp = ReadLine(pFile);
						//fgets(buffer, sizeof(buffer), pFile);
						//std::string line = buffer;
						//line.resize(line.size() - 1);

						//debug->Log("Add mesh to model : " + line.substr(1) + " (o)");
						debug->Log("Add mesh to model : " + temp + " (o)");
						if (count_meshes > 0)
							if (!addMesh()) return nullptr;
						count_meshes++;
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
							// Needed setlocale(LC_NUMERIC, "C"); 
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
		*/
	}
}