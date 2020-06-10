#pragma once
#include "Window.h"
#include "Render.h"
#include "Camera.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphics {
		class SRGraphics {
		private:
			bool isCreate;
			bool isInit;
			bool isRun;
			bool isClose;
			static SRGraphics* global;
		private:
			char** argv;
			int argcp;
		private:
			Window* win;
			Debug* debug;
			Render* render;
			Camera* camera;
		public:
			static SRGraphics* Get() {
				if (global) {
					return global;
				}
				else {
					Debug::InternalError("Graphics engine is not create!");
					return nullptr;
				}
			}
		public:
			Render* GetRender() {
				if (render) return render;
				else {
					debug->Error("SRGraphics : render is nullptr!");
					Sleep(3000);
					return nullptr;
				}
			}
			void SetCamera(Camera* camera) {
				if (!isCreate)
					this->camera = camera;
				else
					debug->Error("The camera can only be set before creation!");
			}
			void SetRender(Render* render) {
				if (!isCreate)
					this->render = render;
				else
					debug->Error("The render can only be set before creation!");
			}
			Camera* GetCamera() {
				if (!camera) {
					debug->Error("Camera is nullptr!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					return nullptr;
				}
				else
					return camera;
			}
		public:
			SRGraphics(int argcp, char** argv, Debug* debug) {
				if (global) {
					debug->Error("Graphics engine already create!");
					return;
				}
				else {
					this->argcp = argcp;
					this->argv = argv;

					this->render = nullptr;
					this->win = nullptr;

					this->global = this;
					this->debug = debug;

					this->camera = nullptr;

					isClose = false;
				}
			}
			~SRGraphics() { if (!isClose) Close(); }

			bool Create(Window* win);
			bool Init();
			bool Run();

			bool Close();
		};
	}
}