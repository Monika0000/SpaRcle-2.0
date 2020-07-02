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
			std::string name;
			bool isLinked = false;
			Debug* debug;
		public:
			GLuint ProgramID;
			Shader(std::string name, Debug* debug);
			~Shader();
		public:
			void setInt(const std::string& name, int value) const {
				glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value);
			}
		public:
			bool Compile();
			bool Use(); //GLuint tex1, GLuint vbo, GLuint uv
			bool Release();
		};
	}
}

