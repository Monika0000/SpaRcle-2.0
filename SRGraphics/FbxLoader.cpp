#include "pch.h"
#include "FbxLoader.h"
#include "Model.h"
#include "Mesh.h"

using namespace SpaRcle::Graphics;

void SpaRcle::Graphics::FbxLoader::Clear() {
		this->vertices.clear(); this->indexes.clear(); this->coords.clear(); this->normals.clear();
}

Mesh* SpaRcle::Graphics::FbxLoader::MakeMesh() {



	Clear();
	return nullptr;
}

void SpaRcle::Graphics::FbxLoader::ProcessLine() {
	std::getline(in, line);
	line = String::ReplaceAll(line, "\t", "").substr(3);

	switch (state) {
	case SpaRcle::Graphics::FbxLoader::State::Vertices: {
		this->vertices = String::SplitDouble(line, ",");
		//std::cout << "["+ String::MakeString(String::Split(line, ",")) << "]\n";
		//std::cout << (float)std::stod("1342.5432") << std::endl;
		break; }
	case SpaRcle::Graphics::FbxLoader::State::PolygonVertexIndex: {
		//std::cout << std::stoi("-4234") << std::endl;
		this->indexes = String::SplitInt(line, ",");
		break; }

	case SpaRcle::Graphics::FbxLoader::State::Normals:
		break;
	case SpaRcle::Graphics::FbxLoader::State::NormalsW:
		break;

	case SpaRcle::Graphics::FbxLoader::State::UV:
		break;
	case SpaRcle::Graphics::FbxLoader::State::UVIndex:
		break;
	default:
		break;
	}
}

void SpaRcle::Graphics::FbxLoader::Parse() {
	line  = String::ReplaceAll(line, "\t", "");
	split = String::Split(line, " ", true);
	
	if (split.size() == 0) return;
	
	if (split[0] == "Objects:") {
		state = State::Objects;
	}
	else if (split[0] == "Geometry:") {
		state = State::Geometry;
		geometry_id = (size_t)std::atoll(String::ReadToChar(split[1], ',').c_str());
		geometry_name = String::BetweenCharacters(split[2], ':', '\"').substr(1);

		//std::cout << geometry_name << std::endl;
		//std::cout << String::ReadToChar(String::SubstringPlus(split[2], ':', 1), '\"') << std::endl;

	}
	else if (split[0] == "Vertices:") {
		state = State::Vertices;
		ProcessLine();
	}
	else if (split[0] == "PolygonVertexIndex:") {
		state = State::PolygonVertexIndex;
		ProcessLine();
	}
	else if (split[0] == "Layer:")
		state = State::Layer;
}

Model* SpaRcle::Graphics::FbxLoader::LoadModel(std::string name) {
	ret:
	if (load)
		goto ret;

	load = true;

	Clear();

	std::string file = this->res_path + "\\Models\\" + name + ".fbx";
	file = String::MakePath(file);
	debug->Log("FbxLoader : load \"" + file + "\"");

	std::string ascii = res_path + "\\Cache\\model_ascii_" + name + ".fbx";

	if (!File::FileExists(file)) {
		debug->Error("FbxLoader : failed load model : " + file + "\n\tReason : file is not exists!");
		Sleep(500);
		load = false;
		return nullptr;
	}

	std::string command = res_path + "\\Utilites\\FbxFormatConverter.exe -c " +
		file + " -o " +
		ascii + " -ascii -hidden";

	system(command.c_str());
	Sleep(50);

	in = std::ifstream(ascii);
	if (in.is_open()) {
		while (!in.eof()) {
			std::getline(in, line);
			this->Parse();

			if (state == State::Layer) {
				Mesh* mesh = MakeMesh();
			}
		}
	} else {
		debug->Error("FbxLoader : failed load model : " + ascii + "\n\tReason : failed create ascii fbx model!");
		Sleep(500);
		load = false;
		return nullptr;
	}

	in.close();

	load = false;
	return nullptr;
}
