#pragma once
#include <iostream>
#include <Windows.h>
#include <d3dx10.h>
#include <direct.h>

using namespace std;

class WindowConfig
{
private:
	static wchar_t* GetCurrentDirectory();
public:
	// window game config
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
	static const int MAX_FRAME_RATE;

	static const wchar_t* WINDOW_TITLE;
	static const wchar_t* WINDOW_CLASS_NAME;
	static const D3DXCOLOR BACKGROUND_COLOR;

	static wchar_t* WINDOW_ICON_PATH;

	static wchar_t* GetIconPath();
};
