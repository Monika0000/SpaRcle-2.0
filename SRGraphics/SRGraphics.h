#pragma once
#include "Window.h"
#include "Render.h"
#include "Camera.h"
#include "Json.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphics {
		class SRGraphics {
		private:
			std::string resources_folder;
		public:
			const bool EditorMode;
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
			Window* GetWindow() {
				if (win) return win;
				else {
					debug->Error("SRGraphics : window is nullptr!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					Sleep(3000);
					return nullptr;
				}
			}
			Render* GetRender() {
				if (render) return render;
				else {
					debug->Error("SRGraphics : render is nullptr!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					Sleep(3000);
					return nullptr;
				}
			}
			/*
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
			}*/
			Camera* GetCamera() {
				if (!camera) {
					debug->Error("Camera is nullptr!");
					EventsManager::PushEvent(EventsManager::Events::Error);
					return nullptr;
				}
				else
					return camera;
			}
			std::string GetResourcesFolder() const { return resources_folder; };
		public:
			SRGraphics(int argcp, char** argv, Debug* debug, bool EditorMode = false);
			~SRGraphics() { if (!isClose) Close(); }

			bool Create(Window* win, Render* render, Camera* camera);
			bool Init();
			bool Run();

			bool Close();
		};
	}
}