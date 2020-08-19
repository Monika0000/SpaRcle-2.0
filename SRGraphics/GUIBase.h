#pragma once
#define GLEW_STATIC
#define NOMINMAX
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <vector>

namespace SpaRcle {
	namespace Graphics {
		class Shader;
		namespace GUI {
			enum class OrientationV {
				CENTER, UP, DOWN
			};
			enum class OrientationH {
				CENTER, LEFT, RIGHT
			};

			class Canvas;
			class GUIBase {
			public:
				GUIBase(Canvas* canvas, glm::vec2 pos, glm::vec2 scale, glm::vec4 color);
				~GUIBase() {
					this->canvas				= nullptr;
					this->shader				= nullptr;
					this->isDestroy				= true;
				}
			public:
				bool isDestroy					= false;
				std::vector<GUIBase*> Childs	= std::vector<GUIBase*>();
				GUIBase* parent					= nullptr;
			public:
				//float offset_size_y				= 1.0;
				//float offset_pos_y				= 0.0;
				OrientationV	orientationV	= OrientationV::CENTER;
				OrientationH	orientationH	= OrientationH::CENTER;

				glm::vec2 posit					= { 0, 0 };
				//glm::vec2 offset				= { 0, -0.005 };
				glm::vec2 offset				= { 0, 0 };
				glm::vec2 scale					= { 1, 1 };
				glm::vec4 color					= { 1, 1, 1, 1 };
				//glm::mat4 model					= glm::mat4(1.0f);
				Canvas* canvas					= nullptr;
				Shader* shader					= nullptr;
			 public:
				//void SetOffsetY(float offset_pos_y) { this->offset_pos_y = offset_pos_y; }
				 void SetOrientationV(OrientationV orint) { 
					 this->orientationV = orint; 
					 this->SetScale(scale.x, scale.y);
				 }
				 void SetOrientationH(OrientationH orint) { 
					 this->orientationH = orint; 
					 this->SetScale(scale.x, scale.y);
				 }
			public:
				// [WITH CHILDS]
			public:
				// [NO CHILDS | SET DEFAULT VALUES | FOR INITIALIZE]
				virtual void		SetColor	(float r, float g, float b, float a)		{ this->color	= {r,g,b,a};			};
				virtual void		SetPosition	(float x, float y)							{ this->posit	= {x,y};				};
				virtual void		Move(float x, float y);
				virtual glm::vec2	GetPosition	()											{ return posit;							};
				virtual void		SetScale	(float x, float y);
				void SetParent(GUIBase* parent) {
					this->parent = parent;
					this->SetScale(scale.x, scale.y);
					this->parent->Childs.push_back(this);
				}
				//void SetLocalScale	(glm::vec2 scale);
			protected:
				//void UpdateMatrix();
			public:
				virtual bool Draw()				{ return false; };
				virtual void Flat(size_t index) { return;		};
			};
		}
	}
}

//SpaRcle::Graphics::GUI::GUIBase::GUIBase(Canvas* canvas) {
//	this->canvas = canvas;
//}