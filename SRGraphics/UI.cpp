#include "pch.h"
#include "UI.h"
#include "Window.h"

float SpaRcle::Graphics::UI::XPosCorrect() const {
	return x_pos * win->format->x_left_side_pos_magic_number / 2.20625f;;
}
