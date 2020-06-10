// SRGraphics.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "SRGraphics.h"
#include <functional>

namespace SpaRcle {
	namespace Graphics {
		SRGraphics* SRGraphics::global = nullptr;

		bool SRGraphics::Create(Window* win) {
			if (!isCreate) {
				debug->Graph("Creating graphics engine...");

				if (!render || !camera) {
					debug->Error("Failed creating graphics engine!");
					return false;
				}

				//this->render = new Render(debug);
				if (camera) camera->Create();

				win->SetCamera(camera);
				win->SetRender(render);
				this->win = win;//new Window(debug, camera);

				isCreate = true;
				return true;
			}
			return false;
		}
		bool SRGraphics::Init() {
			debug->Graph("Initializing graphics engine...");

			win->Init(); // init and create window

			return true;
		}
		bool SRGraphics::Run() {
			debug->Graph("Running graphics engine...");

			if (camera) camera->Run();

			return true;
		}
		bool SRGraphics::Close() {
			isClose = true;

			debug->Graph("Close graphics engine...");
			if (camera) delete camera;
			delete this->win;

			return true;
		}
	}
}
