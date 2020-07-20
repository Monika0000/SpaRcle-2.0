#pragma once
#include "Vector3.h"

namespace SpaRcle {
	namespace Graphics {
		class ColorBuffer {
			struct cbInfo_t {
				int Name;
				vec3ui  Color;
			};
		public:
			ColorBuffer() {

			}
			~ColorBuffer() { Names.clear(); }
		private:
			std::vector<cbInfo_t> Names = std::vector<cbInfo_t>();
			size_t next = 0;
		public:
			void InitNames(size_t count_models);
			void LoadName(size_t OBJECT_ID, vec3ui color);
			int GetSelectColorObject(unsigned char* pixel);
			bool CheckColor(vec3ui& one, unsigned char* two);
		};
	}
}