#pragma once
#include <string>
#include <Debug.h>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm\ext\matrix_transform.hpp>

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
			bool isRelease = false;
			Debug* debug;
		public:
			GLuint ProgramID;
			Shader(std::string name, Debug* debug);
			~Shader();
		public:
			void SetInt(const std::string& name, int value) const {
				glUniform1i(glGetUniformLocation(ProgramID, name.c_str()), value);
			}
			void SetMat4(const std::string& name, glm::mat4 mat);
			void SetVec2(const std::string& name, glm::vec2 vec);
			void SetVec4(const std::string& name, glm::vec4 vec);
			void SetTexture(const std::string& name, GLuint ID);
		public:
			bool Compile();
			bool Use(); //GLuint tex1, GLuint vbo, GLuint uv
			bool Release();
		};
	}
}

