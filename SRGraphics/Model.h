#pragma once
#include "Mesh.h"

namespace SpaRcle {
	namespace Graphics {
		/*
		struct Object3D {
		public:
			Object3D() {
				_mesh = nullptr;
				pos = new Vector3{ 0.f, 0.f, 0.f };
				scale = 1;
			};
			~Object3D() {
				if (_mesh) delete _mesh;
				delete pos;
			};
			Mesh* _mesh;
			void SetPosition(float x, float y, float z) {
				pos->x = x;
				pos->y = y;
				pos->z = z;

				_mesh->tris.clear();
				_mesh->tris = {
					// SOUTH
					{ 0.0f + x, 0.0f + y, 0.0f + z,    0.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z},
					{ 0.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 0.0f + y, 0.0f + z},

					// EAST                                                      
					{ 1.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z},
					{ 1.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 0.0f + y, 1.0f + z},

					// NORTH                                                     
					{ 1.0f + x, 0.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z},
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 1.0f + z},

					// WEST                                                      
					{ 0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 0.0f + z},
					{ 0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 1.0f + y, 0.0f + z,    0.0f + x, 0.0f + y, 0.0f + z},

					// TOP                                                       
					{ 0.0f + x, 1.0f + y, 0.0f + z,    0.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 1.0f + z},
					{ 0.0f + x, 1.0f + y, 0.0f + z,    1.0f + x, 1.0f + y, 1.0f + z,    1.0f + x, 1.0f + y, 0.0f + z},

					// BOTTOM                                                    
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 0.0f + z},
					{ 1.0f + x, 0.0f + y, 1.0f + z,    0.0f + x, 0.0f + y, 0.0f + z,    1.0f + x, 0.0f + y, 0.0f + z},
				};
			}
			float scale;
		private:
			Vector3* pos;
		};

		struct Cube : public Object3D {
			Cube(float x, float y, float z) {
				//pos->x = x;
				//pos->y = y;
				//pos->z = z;

				_mesh = new Mesh();
				_mesh->count = 12;

				//triangle t = { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f };

				_mesh->tris = {
					// SOUTH
					{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

					// EAST                                                      
					{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

					// NORTH                                                     
					{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

					// WEST                                                      
					{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
					{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

					// TOP                                                       
					{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
					{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

					// BOTTOM                                                    
					{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
					{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
				};

				SetPosition(x, y, z);
			};
		};
		*/
	}
}