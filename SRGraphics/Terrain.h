#pragma once
#include "Chunk.h"

namespace SpaRcle {
	namespace Graphics {
		class Terrain {
			typedef std::vector<std::vector<Chunk*>> Map;
		public:
			Terrain(size_t w, size_t h);
			~Terrain();
		public:
			Map map;
		public:
			void Draw();
		};
	}
}

