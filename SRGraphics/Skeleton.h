#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <Debug.h>

namespace SpaRcle {
	namespace Graphics {
		inline static const int MAX_BONES = 128;

		/*
		class Deformer {
		public:
			Deformer(std::vector<long> Indexes, std::vector<float> Weights) {
				count = Indexes.size();
				if (count != Weights.size()) {
					Helper::Debug::InternalError("Deformer::Constructor() : " + std::to_string(count) + " != " + std::to_string(Weights.size()));
					return;
				}

				this->Indexes = Indexes;
				this->Weights = Weights;
			};
		public:
			//size_t id;
			//std::string name;
			size_t count				= 0;
			std::vector<long>  Indexes	= std::vector<long>();
			std::vector<float> Weights	= std::vector<float>();
		};
		class SubDeformer {
			size_t id;
			std::string name;
		};

		class Bone {
		public:
			glm::vec3 position = { 0, 0, 0 };
			glm::vec3 rotation = { 0, 0, 0 };
			glm::vec3 scale	   = { 1, 1, 1 };
			Deformer* deformer = nullptr;
			//size_t id;
			//std::string name;
		};
		*/

		struct Bone {
			glm::vec3 position	= { 0, 0, 0 };
			glm::vec3 rotation	= { 0, 0, 0 };
			glm::vec3 scale		= { 1, 1, 1 };
		};

		class Skeleton {
		public:
			std::vector<Bone> Bones = std::vector<Bone>();
		};
	}
}