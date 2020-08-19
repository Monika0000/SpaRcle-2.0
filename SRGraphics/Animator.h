#pragma once
#include "Animation.h"
#include "Skeleton.h"

namespace SpaRcle {
	namespace Graphics {
		class Model;
		class Shader;

		class Animator {
		private:
			Model* model = nullptr;
			Skeleton* avatar = nullptr;

			Animation* animation = nullptr;
			//TODO: More animations
		public:
			bool Play();
			void SetAnimation(Animation* anim);
			void SetSkeleton(Skeleton* avatar);
		public:
			void Use(Shader* shader, unsigned int mesh_number);
		};
	}
}
