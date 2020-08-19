#pragma once
#include <string>
#include <vector>

#include <SRString.h>
#include "GUIBase.h"

namespace SpaRcle {
	namespace Graphics {
		namespace GUI {
			class GUIText : public GUIBase {
			public:
				inline static const float begin_x = 2.21;
				inline static const float begin_y = 0.245;
			public:
				GUIText(Canvas* canvas, glm::vec2 pos = { 0,0 }, glm::vec2 scale = { 1,1 }, glm::vec4 color = {1,1,1,1});
				GUIText(Canvas* canvas, std::string text, glm::vec2 pos = { 0,0 }, glm::vec2 scale = { 1,1 }, glm::vec4 color = {1,1,1,1});
				~GUIText();
			private:
				char*			m_text = nullptr;
				unsigned short  t_len  = 0;
				unsigned short	i	   = 0;
			public:
				void SetString(std::string str);
				void SetScale(float x, float y) override;
				void SetPosition(float x, float y) override;
				void Move(float x, float y) override;
				glm::vec2 GetPosition() override;
				bool Draw() override;
			};
		}
	}
}

