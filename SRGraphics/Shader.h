#pragma once
#include <string>
#include <Debug.h>
#include <GL\glew.h>

namespace SpaRcle {
	namespace Graphics {
		using namespace Helper;
		class Mesh;
		class Texture;
		class Render;

		class Shader {
			friend class Render;
			friend class Mesh;
			friend class Texture;
		private:
			GLuint ProgramID;
			std::string name;
			bool isLinked = false;
			Debug* debug;
		public:
			Shader(std::string name, Debug* debug);
			~Shader();
		public:
			bool Compile();
			bool Use(GLuint tex1);
			bool Release();
		};
	}
}

