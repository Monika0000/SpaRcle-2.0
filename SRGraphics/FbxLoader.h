#pragma once
#include <Debug.h>
#include <SRHelper.h>
#include <vector>
#include <fstream>

namespace SpaRcle {
	using namespace Helper;
	namespace Graphics {
		class Model;
		class Mesh;

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
						Layer // this is end geometry
			};
		private:
			void Clear();
			Mesh* MakeMesh();
			void ProcessLine();
			void Parse();
		private:
			std::ifstream in;
			std::string line			   = "";
			std::string temp			   = "";
			std::vector<std::string> split = std::vector<std::string>();

			std::string geometry_name = "";
			size_t geometry_id		  = 0;

			std::vector<double>		vertices = std::vector<double>();
			std::vector<int>		indexes  = std::vector<int>();
			std::vector<double>		coords   = std::vector<double>();
			std::vector<double>		normals  = std::vector<double>();
		private:
			bool load				= false;
			State state				= State::Unknown;
			Debug* debug			= nullptr;
			std::string res_path	= "[undefined]";
		public:
			FbxLoader(Debug* debug, std::string resources_folder) {
				this->debug = debug;
				this->res_path = resources_folder;
			}
		public:
			Model* LoadModel(std::string name);
			void LoadAnimation() {  };
		};
	}
}

