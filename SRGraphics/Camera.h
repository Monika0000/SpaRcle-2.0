#pragma once
#include <SRHelper.h>
#include <GL\glu.h>

namespace SpaRcle {
	using namespace Helper;

		namespace Graphics {
		class Camera {
		private:
			//! ÑÊÎÐÎÑÒÈ ÏÅÐÅÌÅÙÅÍÈß ÏÎ ÎÑßÌ XYZ
			float spdx = 0.0;
			float spdy = 0.0;
			float spdz = 0.0;
			//! ÑÌÅÙÅÍÈÅ ÊÓÐÑÎÐÀ
			float dx = 0.0;
			float dy = 0.0;
			//! ÓÃËÛ ÂÐÀÙÅÍÈß
			float yaw = 0.0;
			float ptc = 0.0;
			//! ÊÎÎÐÄÈÍÀÒÛ ÒÎ×ÊÈ ÊÓÄÀ (ÈËÈ ÎÒÊÓÄÀ) ÑÌÎÒÐÈÒ ÊÀÌÅÐÀ
			float dxx = 0.0;
			float dxz = 0.0;
			float dyy = 0.0;
			//! ÊÎÎÐÄÈÒÀÒÛ ÊÀÌÅÐÛ ÏÎ ÎÑßÌ XYZ
			float posx = 0.0;
			float posy = 0.0; // 2.0
			float posz = 0.0;

			POINT pt;
			float prevX;
			float prevY;
		private:
			bool isCreate;
			bool isRun;
			bool* isMouseLock;
		private:
			unsigned short* x_size;
			unsigned short* y_size;
			int* x_pos; int* y_pos;
		private:
			Debug* debug;
			//std::thread task;
		public:
			Camera(Debug*debug) {
				x_size = NULL;
				y_size = NULL;
				x_pos = NULL;
				y_pos = NULL;
				this->debug = debug;
				isCreate = false;
				isRun = false;
			};
			~Camera() { Close(); };
		public:
			bool Create(
				unsigned short& x_size, unsigned short& y_size,
				int& x_pos, int& y_pos
			);
			bool Init(bool& isMouseLock);
			bool Run();
			bool Close();
			void Move();
		public:
			//void CameraFunc();
			void ResetCameraPos() {
				posx = 0; posy = 0; posz = 0;
				yaw = 0; ptc = 0;
				dxx = 0; dxz = 0; dyy = 0;
			}
		};
	}
}

