#include "pch.h"
#include "ColorBuffer.h"

namespace SpaRcle {
	namespace Graphics {
		void ColorBuffer::InitNames(size_t count_models) {
			if (count_models > Names.size())
				Names.resize(count_models);

			for (auto& a : Names) {
				a.Color = { 0, 0, 0 };
				a.Name  = 0;
			}

			next = 0;
		}
		void ColorBuffer::LoadName(size_t OBJECT_ID, vec3uc color) {
			Names[next].Name = OBJECT_ID;
			Names[next].Color = color;
			next++;
		}
		int ColorBuffer::GetSelectColorObject(unsigned char* pixel) {
			for (int i = 0; i < next; i++) {
				if (CheckColor(Names[i].Color, pixel))
					return Names[i].Name;
			}
			return -1;
		}
		bool ColorBuffer::CheckColor(vec3uc& one, unsigned char* two) {
			if (one.x == two[0] && one.y == two[1] && one.z == two[2])
				return true;
			return false;
		}
	}
}