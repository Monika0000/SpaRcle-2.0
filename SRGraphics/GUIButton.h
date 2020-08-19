#pragma once
#include "GUIBase.h"
#include <functional>

namespace SpaRcle {
	namespace Graphics {
		namespace GUI {
			class GUIObject;
			class GUIText;

			class GUIButton : public GUIBase {
			public:
				GUIButton(Canvas* canvas, std::string bttn_name, glm::vec2 pos, glm::vec2 scale, glm::vec4 color = { 1,1,1,1 },
					OrientationH orH = OrientationH::CENTER, OrientationV orV = OrientationV::CENTER);
				~GUIButton();
			private:
				std::function<void(void)> callback = std::function<void(void)>();
				bool hasCallBack = false;

				GUIObject* main_object	= nullptr;
				GUIText*   text			= nullptr;
			public:
				void SetCallBack(std::function<void(void)> callback) {
					this->callback = callback;
					this->hasCallBack = true;
				}
			public:
				void Flat(size_t index) override;
				bool Draw() override;
			};
		}
	}
}


