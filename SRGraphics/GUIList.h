#pragma once
#include "GUIBase.h"
#include <string>
#include <vector>

namespace SpaRcle {
	namespace Graphics {
		namespace GUI {
			class GUIObject;
			class GUIText;
			class Canvas;

			class GUIList : public GUIBase {
			public:
				GUIList(
					Canvas* canvas, std::string name, glm::vec2 pos, glm::vec2 scale, glm::vec4 color = { 1,1,1,1 },
					OrientationH orH = OrientationH::CENTER, OrientationV orV = OrientationV::CENTER
				);
				~GUIList();
			private:
				GUIObject* main_object	= nullptr;
				GUIObject* top_object	= nullptr;
				GUIText* text			= nullptr;
			public:
				bool Draw() override;
				//void Move(float x, float y) override;
			};
		}
	}
}

