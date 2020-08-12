#include "pch.h"
#include "FbxLoader.h"
#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "SRGraphics.h"

namespace SpaRcle {
	namespace Graphics {
		SpaRcle::Graphics::FbxLoader::FbxLoader(Debug* debug, SRGraphics* graph) {
			this->debug = debug;
			this->graph = graph;
			this->res_path = graph->GetResourcesFolder();
			this->count_meshes = 0;
			this->line_number = 0;
		}
		void SpaRcle::Graphics::FbxLoader::Clear() {
			this->_vertices.clear(); this->_indexes.clear(); this->_uvs.clear(); this->_normals.clear(); _uvs_indexs.clear();
			this->state = State::Unknown;
		}

		SpaRcle::Graphics::FbxLoader::ModelState* SpaRcle::Graphics::FbxLoader::FindModelState(size_t ID) {
			for (auto a : this->modelsStates)
				if (a.id == ID)
					return &a;

			debug->Error("FbxLoader::FindModelState() : failed find model state of ID : " + std::to_string(ID));
			Sleep(500);
			return nullptr;
		}

		Mesh* SpaRcle::Graphics::FbxLoader::FindMesh(size_t ID) {
			if (!current_model) {
				debug->Error("FbxLoader::FindMesh() : current model is nullptr! Logical error!");
				Sleep(500);
				return nullptr;
			}

			for (auto a : current_model->meshes) {
				if (a->GeometryID == ID)
					return a;
				//else
				//	std::cout << a->GeometryID << std::endl;
			}

			debug->Error("FbxLoader::FindMesh() : failed find mesh of ID : " + std::to_string(ID));
			Sleep(500);
			return nullptr;
		}

		void SpaRcle::Graphics::FbxLoader::ParseConnections() {
			GetLine();

			while (line != "}") {
				line = String::ReadToChar(String::ReplaceAll(line, "\t", ""), ':');

				if (line == ";Geometry") {
					GetLine();
					split = String::Split(line, ",");

					Mesh* mesh = FindMesh(std::stoll(split[1]));
					ModelState* state = FindModelState(std::stoll(split[2]));

					if (!mesh || !state)
						return;

					mesh->default_position = state->pos;
					mesh->default_position.y *= -1;

					mesh->default_rotation = state->rot;
					mesh->default_scale = state->scl;
					mesh->UpdateMatrix();
					//std::cout << mesh->default_position.x << " "
					//	<< mesh->default_position.y << " "
					//	<< mesh->default_position.z << "\n";
				}

				GetLine();
			}
		}

		void SpaRcle::Graphics::FbxLoader::ParseModel() {
			ModelState state = ModelState();
			if (split.size() == 5) {
				state.id = (size_t)std::atoll(String::ReadToChar(split[1], ',').c_str());
				state.name = String::BetweenCharacters(split[2], ':', '\"').substr(1);
			}
			else if (split.size() == 4) {
				state.id = 0;
				state.name = String::BetweenCharacters(split[1], ':', '\"').substr(1);
			}
			else {
				debug->Error("FbxLoader::ParseModel() : failed parse model!\n\tPath : " + current_file
					+ "\n\tReason : unknow model configuration! Split elements is : " + std::to_string(split.size()));
				return;
			}

			GetLine(); // Version
			GetLine(); // Properties

			int PVer = std::stoi(String::ReadToChar(line.substr(2 + 10), ':'));

			GetLine();

			auto math = [](std::string& str)->glm::vec3 {
				std::vector<double> v = String::SplitDouble(String::SubstringPlus(str, ',', 0), ",");
				return { v[0], v[1], v[2] };
			};

			while (line != "\t\t}") {
				line = line.substr(3);
				split = String::SplitWithoutBacktick(line, ' ');
				//std::cout << v[0] << " " << v[1] << " " << v[2] << std::endl;

				if (PVer == 70) {
					if (split[1] == "\"Lcl Translation\",")
						state.pos = math(split[4]);
					else if (split[1] == "\"Lcl Rotation\",")
						state.rot = math(split[4]);
					else if (split[1] == "\"Lcl Scaling\",")
						state.scl = math(split[4]);
				}
				else if (PVer == 60) {
					if (split[1] == "\"Lcl Translation\",")
						state.pos = math(split[3]);
					else if (split[1] == "\"Lcl Rotation\",")
						state.rot = math(split[3]);
					else if (split[1] == "\"Lcl Scaling\",")
						state.scl = math(split[3]);
				}
				else debug->Warn("FbxLoader::ParseModel() : unknown properties version! Version : " + std::to_string(PVer));

				//std::cout << 
				//	"Pos : " << state.pos[0] << " " << state.pos[1] << " " << state.pos[2] << 
				//	"; Rot : " << state.rot[0] << " " << state.rot[1] << " " << state.rot[2] <<
				//	"; Scl : " << state.scl[0] << " " << state.scl[1] << " " << state.scl[2]
				//<< std::endl;

				GetLine();
			}

			this->modelsStates.push_back(state);
		}

		std::vector<glm::vec3> SpaRcle::Graphics::FbxLoader::MathTangents() {
			std::vector<glm::vec3> tangents = std::vector<glm::vec3>();
			size_t indxs_count = _indexes.size();

			//!====================================[TANGENT]========================================
			if (Math::IsFractional((float(indxs_count) / 3.f))) {
				debug->Error("FbxLoader::MathTangents() : error number 3214! Model needed triangulate!");
				while (Math::IsFractional((float(indxs_count) / 3.f))) {
					fix_indexes.pop_back();
					indxs_count--;
				}
			}

			for (t = 0; t < indxs_count; t += 3) {
				//if (line_number == 3214) {
					//std::cout << t << std::endl;
					//if (t == 26580) {
					//	std::cout << "fix_indexes = " << fix_indexes.size() << "; t = " << t;
						//std::cout << "verts = " << verts.size() << "; index[t+1]" << fix_indexes[t + 1] << "; index[t]" << fix_indexes[t];
					//}
				//}

				glm::vec3 edge1 = verts[fix_indexes[t + 1]] - verts[fix_indexes[t]];				// pos2 - pos1 | face.y - face.x
				glm::vec3 edge2 = verts[fix_indexes[t + 2]] - verts[fix_indexes[t]];				// pos3 - pos1 | face.z - face.x
				glm::vec2 deltaUV1 = uvs[_uvs_indexs[t + 1]] - uvs[_uvs_indexs[t]];					// uv2 - uv1   | uv.y   - uv.x
				glm::vec2 deltaUV2 = uvs[_uvs_indexs[t + 2]] - uvs[_uvs_indexs[t]];					// uv3 - uv1	  | uv.z   - uv.x 

				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

				tangents.push_back({
					 f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
					 f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
					 f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)
					});
			}
			//!====================================[TANGENT]========================================

			return tangents;
		}
		Mesh* SpaRcle::Graphics::FbxLoader::MakeMesh() {
			std::vector<Vertex> final_vertices = std::vector<Vertex>();

			if (Math::IsFractional((double)this->_vertices.size() / 3.0)) {
				debug->Error("FbxLoader::MakeMesh() : failed create mesh!\n\tPath : "
					+ current_file + "\n\t Reason : count verices is fractional!\n\tCount vertices coords : " + std::to_string(_vertices.size()));
				Clear();
				return nullptr;
			}

			//! =============== [ Math vertices ] ===============
			verts.clear();
			for (t = 0; t < _vertices.size(); t += 3)
				verts.push_back({ _vertices[t], _vertices[t + 1], _vertices[t + 2] });

			//! =============== [ Math indexes ] ===============
			fix_indexes.clear();
			for (t = 0; t < _indexes.size(); t++) {
				int result = _indexes[t];
				if (result < 0) result = (result * -1) - 1;
				fix_indexes.push_back(result);
			}

			//! =============== [ Math uvs ] ===============
			uvs.clear();
			for (t = 0; t < _uvs.size(); t += 2)
				uvs.push_back({ _uvs[t], _uvs[t + 1] });

			//! =============== [ Math normals ] ===============
			std::vector<glm::vec3> norms = std::vector<glm::vec3>();
			for (t = 0; t < _normals.size(); t += 3)
				norms.push_back({ _normals[t], _normals[t + 1], _normals[2] });

			//if (line_number == 3214) {
			//	std::cout << "verts = " << verts.size() << "; indexes = " << fix_indexes.size() 
			//		<< "; uvs = " << uvs.size() << "; normals = " << norms.size() << std::endl;
			//}

			if (uvs.size() != 0) {
				//! =============== [ Math tangents ] ===============
				std::vector<glm::vec3> tangents = MathTangents();

				//? =============== [ Check correction data ] ===============
				if (!(fix_indexes.size() == _uvs_indexs.size() && _uvs_indexs.size() == norms.size())) {
					debug->Error("FbxLoader::MakeMesh() : failed create mesh!\n\tPath : " +
						current_file + "\n\tReason : count elements is not equals!\n\tVerts : " +
						std::to_string(fix_indexes.size()) + "\n\tUVs : " + std::to_string(_uvs_indexs.size()) 
						+ "\n\tNormals : " + std::to_string(norms.size()) + "\n\tLine : " +std::to_string(line_number));
					Sleep(100);
					return nullptr;
				}

				for (t = 0; t < fix_indexes.size(); t++) {
					final_vertices.push_back({
						verts[fix_indexes[t]],
						uvs[_uvs_indexs[t]],
						norms[t],
						tangents[int((float)t / 3.f)]
						});
				}
			}
			else {
				for (t = 0; t < fix_indexes.size(); t++) {
					final_vertices.push_back({
						verts[fix_indexes[t]],
						{ 0, 0 },
						norms[fix_indexes[t]],
						{ 0,0,0 }
						});
				}
			}

			if (final_vertices.size() == 0) {
				debug->Error("FbxLoader::MakeMesh() : failed create mesh!\n\tPath : " +
					current_file + "\n\tReason : final vertices equal zero!\n\tIndexes : "
					+ std::to_string(_indexes.size()) + "\n\tVerts : " + std::to_string(verts.size()) + "\n\tVerts coords : "
					+ std::to_string(_vertices.size()) + "\n\tLine number : " + std::to_string(line_number)); //+ "\n\tGeomety name : " + geometry_name
				Sleep(100);
				return nullptr;
			}

			Mesh* mesh = new Mesh(final_vertices);
			mesh->GeometryID = this->geometry_id;
			mesh->GeometryName = this->geometry_name;

			debug->Log("FbxLoader::MakeMesh() : mesh \"" + this->geometry_name + "\" has been created! Verts : "
				+ std::to_string(final_vertices.size()) + "; ID : " + std::to_string(geometry_id));

			Clear();
			return mesh;
		}

		bool SpaRcle::Graphics::FbxLoader::ProcessLine() {
			GetLine();
			line = String::ReplaceAll(line, "\t", "").substr(3);

			switch (state) {
			case SpaRcle::Graphics::FbxLoader::State::Vertices: {
				MoreLines(_vertices);
				break; }
			case SpaRcle::Graphics::FbxLoader::State::PolygonVertexIndex: {
				MoreLines(_indexes);
				break; }

			case SpaRcle::Graphics::FbxLoader::State::Normals:
				MoreLines(_normals);
				break;
			case SpaRcle::Graphics::FbxLoader::State::NormalsW:
				break;

			case SpaRcle::Graphics::FbxLoader::State::UV:
				MoreLines(_uvs);
				//this->_uvs = String::SplitDouble(line, ",");
				break;
			case SpaRcle::Graphics::FbxLoader::State::UVIndex:
				MoreLines(_uvs_indexs);
				//this->_uvs_indexs = String::SplitInt(line, ",");
				break;


				//case SpaRcle::Graphics::FbxLoader::State::
			default:
				break;
			}

			return true;
		}
		bool SpaRcle::Graphics::FbxLoader::Parse() {
			sourceLine = line;
			line = String::ReplaceAll(line, "\t", "");
			split = String::Split(line, " ", true);

			//if (line_number == 3214)
			//	std::cout << line << std::endl;

			if (split.size() == 0) return true;

			if (split[0] == "Objects:") {
				state = State::Objects;
				return true;
			}
			else if (split[0] == "Geometry:") {
				state = State::Geometry;
				geometry_id = (size_t)std::atoll(String::ReadToChar(split[1], ',').c_str());
				geometry_name = String::BetweenCharacters(split[2], ':', '\"').substr(1);

				//std::cout << geometry_id << std::endl;
				//std::cout << geometry_name << std::endl;
				//std::cout << String::ReadToChar(String::SubstringPlus(split[2], ':', 1), '\"') << std::endl;
				return true;
			}
			else if (split[0] == "Vertices:") {
				needLoad = std::stoi(split[1].substr(1));
				state = State::Vertices;
				return ProcessLine();
			}
			else if (split[0] == "PolygonVertexIndex:") {
				needLoad = std::stoi(split[1].substr(1));
				state = State::PolygonVertexIndex;
				return ProcessLine();
			}
			else if (split[0] == "Normals:") {
				needLoad = std::stoi(split[1].substr(1));
				state = State::Normals;
				return ProcessLine();
			}
			else if (split[0] == "UV:") {
				needLoad = std::stoi(split[1].substr(1));
				state = State::UV;
				return ProcessLine();
			}
			else if (split[0] == "UVIndex:") {
				needLoad = std::stoi(split[1].substr(1));
				state = State::UVIndex;
				return ProcessLine();
			}
			else if (split[0] == "Layer:") {
				state = State::Layer;
				return true;
			}
			else if (split[0] == "Model:") {
				ParseModel();
			}
			else if (split[0] == "Connections:") {
				ParseConnections();
			}

			return true;
		}

		Model* SpaRcle::Graphics::FbxLoader::LoadModel(std::string name, std::vector<Material*> mats) {
		ret: if (load) goto ret;

			load = true;

			Clear(); count_meshes = 0; line_number = 0; this->modelsStates.clear();

			current_file = this->res_path + "\\Models\\" + name + ".fbx";
			current_file = String::MakePath(current_file);
			debug->Log("FbxLoader : load \"" + current_file + "\"");

			std::string ascii = res_path + "\\Cache\\model_ascii_" + name + ".fbx";

			if (!File::FileExists(current_file)) {
				debug->Error("FbxLoader : failed load model : " + current_file + "\n\tReason : file is not exists!");
				Sleep(500);
				load = false;
				return nullptr;
			}

			std::string command = res_path + "\\Utilites\\FbxFormatConverter.exe -c " +
				current_file + " -o " +
				ascii + " -ascii -hidden";

			system(command.c_str());
			Sleep(50);

			//Model* model = new Model(); 
			current_model = new Model();

			in = std::ifstream(ascii);
			if (in.is_open()) {
				while (!in.eof()) {
					GetLine();
					if (!this->Parse()) {
						debug->Error("FbxLoader::LoadModel() : failed load model! Error line is " + std::to_string(line_number));
						delete current_model;
						load = false;
						Sleep(500);
						return nullptr;
					}

					if (state == State::Layer && sourceLine == "\t}") {
						state = State::Unknown;
						//std::cout << "[" << line
						Mesh* mesh = MakeMesh();
						if (mesh) {
							count_meshes++;

							Material* mat = nullptr;
							if (count_meshes > mats.size())
								mat = this->graph->GetRender()->GetDefMat();
							else
								mat = mats[count_meshes - 1];

							current_model->AddMesh(mesh, mat);
						}
					}
				}
			}
			else {
				debug->Error("FbxLoader : failed load model : " + ascii + "\n\tReason : failed create ascii fbx model!");
				Sleep(500);
				delete current_model;
				load = false;
				return nullptr;
			}

			in.close();

			if (current_model->meshes.size() == 0) {
				Sleep(500);
				debug->Error("FbxLoader : failed load model!\n\tPath : " + current_file + "\n\tReason : count meshes is zero!");
				delete current_model;
				load = false;
				return nullptr;
			}

			load = false;
			return current_model;
		}
	}
}