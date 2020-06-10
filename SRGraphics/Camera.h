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
		private:
			Debug* debug;
			//std::thread task;
		public:
			Camera(Debug*debug) {
				this->debug = debug;
				isCreate = false;
				isRun = false;
			};
			~Camera() { Close(); };
		public:
			bool Create();
			bool Init();
			bool Run();
			bool Close();
			void Move();
		private:
			//void CameraFunc();
			void ResetCameraPos() {
				posx = 0; posy = 0; posz = 0;
				yaw = 0; ptc = 0;
				dxx = 0; dxz = 0; dyy = 0;
			}
		};
	}
}

