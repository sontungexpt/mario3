#pragma once

#ifndef _WINDOW_CONFIG_H_
#define _WINDOW_CONFIG_H_

#include <d3dx10.h>

namespace configs {
	namespace window {
		const wchar_t* WINDOW_CLASS_NAME = L"Mario 3";
		const wchar_t* WINDOW_TITLE = L"Mario 3";
		const wchar_t* WINDOW_ICON_PATH = L"assets/textures/brick.ico";
		const D3DXCOLOR BACKGROUND_COLOR = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);

		const int MAX_FRAME_RATE = 100;

		const int SCREEN_WIDTH = 320;
		const int SCREEN_HEIGHT = 240;
	}
}
namespace windowrc = configs::window;

#endif
