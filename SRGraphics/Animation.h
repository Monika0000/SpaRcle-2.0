#pragma once
#include "Skeleton.h"

namespace SpaRcle {
	namespace Graphics {
		enum class AnimDir {
			X, Y, Z
		};

		class AnimationCurve {
		public:
			unsigned long		frames = 0;
			std::vector<float>	values = std::vector<float>();
			Bone*				bone = nullptr;
			AnimDir				dir = AnimDir::X;
		};

		class Animation {
		public:
			bool NextFrame();
		};
	}
}

