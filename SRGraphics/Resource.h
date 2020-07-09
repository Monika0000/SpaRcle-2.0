#pragma once
#define GLEW_STATIC
#define NOMINMAX

#include <iostream>
#include <GL\glew.h>
#include <map>
//#include <GL\glut.h>
//#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <GL\glaux.h>
#include <Debug.h>
#pragma comment(lib, "SOIL.lib")

namespace SpaRcle {
	namespace Graphics {
		using namespace Helper;

		class SRGraphics;

		class IResourceManager {
		public:
			IResourceManager(Debug* debug, SRGraphics* graph) : debug(debug), graph(graph) {

			};
		protected:
			Debug* debug = nullptr;
			SRGraphics* graph = nullptr;
			virtual bool Close() = 0;
		};
	}
}