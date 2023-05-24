#include "WindowConfig.h"

const int WindowConfig::SCREEN_WIDTH = 400;
const int WindowConfig::SCREEN_HEIGHT = 240;
const int WindowConfig::MAX_FRAME_RATE = 60;

const wchar_t* WindowConfig::WINDOW_TITLE = L"Mario 3";
const wchar_t* WindowConfig::WINDOW_CLASS_NAME = L"Mario 3";
const D3DXCOLOR WindowConfig::BACKGROUND_COLOR;
wchar_t* WindowConfig::WINDOW_ICON_PATH = GetIconPath();

wchar_t* WindowConfig::GetCurrentDirectory() {
	char buffer[_MAX_PATH];
	if (_getcwd(buffer, _MAX_PATH) != NULL) {
		cout << buffer << endl;
		return (wchar_t*)buffer;
	}
	return NULL;
}

wchar_t* WindowConfig::GetIconPath() {
	//char buffer[MAX_PATH];
	//GetFullPathNameA("../WindowConfig.h", MAX_PATH, buffer, NULL);
	//return string(buffer);
	return GetCurrentDirectory();
}