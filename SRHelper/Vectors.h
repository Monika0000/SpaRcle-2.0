#pragma once
#define _CRT_SECURE_NO_WARNINGS
namespace SpaRcle {
	namespace Graphics {
		struct vec2f { float x, y; };
		struct vec2i { int x, y; };
		struct vec2l { long x, y; };
		struct vec2b { bool x, y; };
		struct vec2d { double x, y; };

		struct vec3f { float x, y, z; };
		struct vec3d { double x, y, z; };
		struct vec3b { bool x, y, z; };
		struct vec3i { int x, y, z; };
		struct vec3ui { unsigned int x, y, z; };
		struct vec3uc { unsigned char x, y, z; };
		struct vec3s { short x, y, z; };
		struct vec3l { long x, y, z; };

		//struct vec3ub { byte x, y, z; };
	}
}