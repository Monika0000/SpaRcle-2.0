#pragma once
#include "Material.h"
#include "Vectors.h"

namespace SpaRcle {
	namespace Graphics {
		struct triangle { vec3f pos[3]; };

		struct mesh {
		public:
			mesh() {
				tris = std::vector<triangle>();
				count = 0;
			}
			~mesh() {
				tris.clear();
			}
			size_t count;
			std::vector<triangle> tris;
		};
	}
}