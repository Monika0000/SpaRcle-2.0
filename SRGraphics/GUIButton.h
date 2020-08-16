#pragma once
#include "GUIBase.h"
#include <functional>

namespace SpaRcle {
	namespace Graphics {
		namespace GUI {
			class GUIButton : public GUIBase {
			public:
				GUIButton(Canvas* canvas, glm::vec2 pos, glm::vec2 scale, glm::vec4 color = { 1,1,1,1 })
					: GUIBase(canvas, pos, scale, color)
				{

				};
				~GUIButton() { };
			private:
				std::function<void(void)> callback			= std::function<void(void)>();
				bool hasCallBack							= false;
			public:
				void SetCallBack(std::function<void(void)> callback) {
					this->callback		= callback;
					this->hasCallBack	= true;
				}
			};
		}
	}
}


