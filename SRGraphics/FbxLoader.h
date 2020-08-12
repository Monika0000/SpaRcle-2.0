#pragma once
#include <Debug.h>
#include <SRHelper.h>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Model;
		class Mesh;
		class SRGraphics;
		class Material;

		class FbxLoader {
			enum class State {
				Unknown,
				Objects, 
					Geometry, 
						Vertices, PolygonVertexIndex, 
						LayerElementNormal,
							Normals, NormalsW,
						LayerElementUV, 
							UV, UVIndex,
						Layer, // this is end geometry
					Model,
						Properties,
			};
			class ModelState{
			public:
				size_t id				= 0;
				std::string name		= "";
				glm::vec3 pos			= { 0, 0, 0 };
				glm::vec3 rot			= { 0, 0, 0 };
				glm::vec3 scl			= { 1, 1, 1 };
			};
		private:
			void Clear();

			ModelState* FindModelState(size_t ID);
			Mesh* FindMesh(size_t ID);
			void ParseConnections();
			void ParseModel();

			std::vector<glm::vec3> MathTangents();
			Mesh* MakeMesh();
			void GetLine() {
				std::getline(in, line);
				line_number++;
			}
			bool MoreLines(std::vector<double>& vec) {
				vec = String::SplitDouble(line, ",");
				while (vec.size() < needLoad) {
					GetLine();
					if (line.size() < 10) if (String::Contains(line.c_str(), '}')) return false;
					std::vector<double> v = String::SplitDouble(line, ",");
					vec.insert(vec.end(), v.begin(), v.end());
				}
				return true;
			}
			bool MoreLines(std::vector<int>& vec) {
				vec = String::SplitInt(line, ",");
				while (vec.size() < needLoad) {
					GetLine();
					if (line.size() < 10) if (String::Contains(line.c_str(), '}')) return false;
					std::vector<int> v = String::SplitInt(line, ",");
					vec.insert(vec.end(), v.begin(), v.end());
				}
				return true;
			}

			bool ProcessLine();
			bool Parse();
		private:
			std::ifstream in;
			std::string line						= "";
			std::string sourceLine					= "";
			std::string temp						= "";
			std::vector<std::string> split			= std::vector<std::string>();
			int needLoad							= 0;
			size_t line_number						= 0;

			std::string geometry_name				= "";
			size_t geometry_id						= 0;
			size_t t								= 0;
			size_t count_meshes						= 0;
			Model* current_model					= nullptr;

			std::vector<glm::vec3> verts			= std::vector<glm::vec3>();
			std::vector<glm::vec2> uvs				= std::vector<glm::vec2>();
			std::vector<int> fix_indexes			= std::vector<int>();
			std::vector<ModelState>	modelsStates	= std::vector<ModelState>();

			std::vector<double>		_vertices		= std::vector<double>();
			std::vector<int>		_indexes		= std::vector<int>();
			std::vector<double>		_uvs			= std::vector<double>();
			std::vector<int>		_uvs_indexs		= std::vector<int>();
			std::vector<double>		_normals		= std::vector<double>();
		private:
			std::string current_file				= "";
			bool load								= false;
			State state								= State::Unknown;
			Debug* debug							= nullptr;
			SRGraphics*	graph						= nullptr;
			std::string res_path					= "[undefined]";
		public:
			FbxLoader(Debug* debug, SRGraphics* graph);
		public:
			Model* LoadModel(std::string name, std::vector<Material*> mats = std::vector<Material*>());
			void LoadAnimation() {  };
		};
	}
}

