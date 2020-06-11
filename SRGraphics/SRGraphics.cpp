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
				if (camera) camera->Create(
					win->x_size,
					win->y_size,
					win->x_pos,
					win->y_pos
				);

				win->SetCamera(camera);
				win->SetRender(render);
				this->win = win;//new Window(debug, camera);
				this->win->Create();

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
			delete this->win;			// 1
			if (camera) delete camera;	// 2

			delete this->render;		// 3

			return true;
		}
	}
}
