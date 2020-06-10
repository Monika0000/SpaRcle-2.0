#pragma once

namespace SpaRcle {
	namespace Graphics {
		class WindowEvents {
		public:
			/* [for wParam] */
			enum class MousePos {
				Workspace = 0, UpToolBar = 2, Icon = 3, Collapse = 8, Expand = 9,
				LeftSide = 10, RightSide = 11, UpSide = 12, DownSide = 15, Close = 20
			};

			/* [for msg] */
			enum class MouseClickInWorkspace {
				Left = 1, Right = 2, Middle = 16
			};

			/* [for msg] */
			enum class MouseClickInToolBar {
				Idle = 160, LeftDown = 161, LeftUp = 162
			};

			enum Event {
				Close, Collapse, Expand, Unknown
			};
			static Event GetEvent(int msg, int param) {
				if (msg == (int)MouseClickInToolBar::LeftDown && param == (int)MousePos::Close)
					return Event::Close;
				else { return Event::Unknown; }
			}
		private:
			WindowEvents() {};
			~WindowEvents() {};
		};
	}
}