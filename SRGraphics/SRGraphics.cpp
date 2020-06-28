// SRGraphics.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "SRGraphics.h"
#include <functional>

namespace SpaRcle {
	namespace Graphics {
		SRGraphics* SRGraphics::global = nullptr;

		bool SRGraphics::Create(Window* win, Render* render, Camera* camera) {
			if (!isCreate) {
				debug->Graph("Creating graphics engine...");

				if (!render) {
					debug->Error("Failed creating graphics engine! Render is nullptr!");
					return false;
				} else { 
					this->render = render; 
					if (!this->render->Create()) {
						debug->Error("Failed creating of render!");
						return false;
					}
				}

				if (!camera) {
					debug->Error("Failed creating graphics engine! Camera is nullptr!");
					return false;
				} else this->camera = camera;

				if (camera) camera->Create(
					//win->format->size_x,
					//win->format->size_y,
					win->format,
					win->x_pos,
					win->y_pos
				);

				win->SetCamera(camera);
				win->SetRender(render);
				this->win = win;//new Window(debug, camera);

				if (!this->win->Create(
					this->argcp,
					this->argv)) 
				{
					debug->Error("Failed creating of engine!");
					return false;
				}

				isCreate = true;
				return true;
			}
			return false;
		}
		bool SRGraphics::Init() {
			if (!isCreate) {
				debug->Error("SRGraphics is not create!");
				EventsManager::PushEvent(EventsManager::Events::Error);
				Sleep(1000);
				return false;
			}

			debug->Graph("Initializing graphics engine...");

			if (!win->Init()) { // init and create window
				debug->Error("Failed initializing of window!");
				return false;
			}

			//if (!render->Init()) {
			//	debug->Error("Failed initializing of render!");
			//	return false;
			//}

			isInit = true;

			return true;
		}
		bool SRGraphics::Run() {
			if (!isInit) {
				debug->Error("SRGraphics is not initialize!");
				EventsManager::PushEvent(EventsManager::Events::Error);
				Sleep(1000);
				return false;
			}

			debug->Graph("Running graphics engine...");

			if (!render->Run()) {
				debug->Error("Failed running of render!");
				return false;
			}

			if (camera) if (!camera->Run()) {
				debug->Error("Failed running of camera!");
				return false;
			}

			isRun = true;

			return true;
		}
		bool SRGraphics::Close() {
			isClose = true;

			debug->Graph("Close graphics engine...");
			delete this->win;			// 1
			if (camera) delete camera;	// 2

			//delete this->render;		// 3
			this->render->Close();		// 3

			return true;
		}
	}
}
