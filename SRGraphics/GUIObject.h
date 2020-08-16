#pragma once
#include "GUIBase.h"
#include <vector>

namespace SpaRcle {
	namespace Helper {
		class Debug;
	}
	namespace Graphics {
		class Texture;
		using namespace Helper;
		namespace GUI {
			class GUIObject : public GUIBase {
			public:
				GUIObject(Canvas* canvas, glm::vec2 pos = { 0,0 }, glm::vec2 scale = { 1,1 }, glm::vec4 color = { 1,1,1,1 });
				GUIObject(Canvas* canvas, OrientationH orH, OrientationV orV, glm::vec2 pos = { 0,0 }, glm::vec2 scale = { 1,1 }, glm::vec4 color = { 1,1,1,1 });
				~GUIObject();
			private:
				bool Bind();
			private:
				Texture* texture					= nullptr;
				bool isBind							= false;
				GLuint VAO							= 0;
				GLuint VBO							= 0;
				GLuint UV							= 0;
			public:
				void SetTexture(Texture* texture);
			public:
				bool Draw() override;
				virtual void Flat();
			};
		}
	}
}
