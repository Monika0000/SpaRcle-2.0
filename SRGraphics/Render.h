#pragma once
#include <vector>
#include <string>
#include <SRHelper.h>
#include "Object3D.h"
#include "UI.h"

namespace SpaRcle {
	namespace Graphics {
		class Render {
		public:
			Render(Debug* debug);
			~Render();
		public:
			void DrawAllObjects();
			void AddObject3D(Object3D* obj);
		private:
			Debug* debug;
		private:
			std::vector<Object3D*> _3d_objects;
			std::vector<UI> _ui_objects;
		};
	}
}

