#pragma once
#include "Window.h"

namespace SpaRcle {
	using namespace Helper;

	namespace Graphics {
		class SRGraphics {
		private:
			bool isClose;
			static SRGraphics* global;
		private:
			char** argv;
			int argcp;
		private:
			Window* win;
			Debug* debug;
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
			SRGraphics(int argcp, char** argv, Debug* debug) {
				if (global) {
					debug->Error("Graphics engine already create!");
					return;
				}
				else {
					this->argcp = argcp;
					this->argv = argv;

					this->win = nullptr;

					this->global = this;
					this->debug = debug;

					isClose = false;
				}
			}
			~SRGraphics() { if (!isClose) Close(); }

			bool Init();

			bool Close() {
				isClose = true;

				debug->Graph("Close graphics engine...");
				delete this->win;

				return true;
			}
		};
	}
}