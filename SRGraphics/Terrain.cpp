#include "pch.h"
#include "Terrain.h"

namespace SpaRcle {
	namespace Graphics {
		Terrain::Terrain(size_t w, size_t h) {
			this->map = std::vector<std::vector<Chunk*>>(w);
			for (auto& m : map) {
				m = std::vector<Chunk*>(h);
				for (size_t t = 0; t < h; h++)
					m[t] = nullptr;
			}
		}
		Terrain::~Terrain() {

		}

		void Terrain::Draw() {

		}
	}
}