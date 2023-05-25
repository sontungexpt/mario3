#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "configs/window.h"

#include "debug.h"
#include "Game.h"

using namespace core;

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}

	return 0;
}

HWND CreateGameWindow(HINSTANCE hinstance, int ncmd_show, int screen_width, int screen_height)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hinstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hinstance, windowrc::WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowrc::WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hwnd =
		CreateWindow(
			windowrc::WINDOW_CLASS_NAME,
			windowrc::WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			screen_width,
			screen_height,
			nullptr,
			nullptr,
			hinstance,
			nullptr);

	if (!hwnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hwnd, ncmd_show);
	UpdateWindow(hwnd);

	SetDebugWindow(hwnd);

	return hwnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frame_start = GetTickCount64();
	ULONGLONG tick_per_frame = 1000 / windowrc::MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frame_start;

		if (dt >= tick_per_frame)
		{
			frame_start = now;
		}
		else
			Sleep((DWORD)(tick_per_frame - dt));
	}

	return 1;
}

int WINAPI wWinMain(
	HINSTANCE   hinstance,
	HINSTANCE   hprev_instance,
	PWSTR       lpcmd_line,
	int         ncmd_show
)
{
	HWND hwnd = CreateGameWindow(hinstance, ncmd_show, windowrc::SCREEN_WIDTH, windowrc::SCREEN_HEIGHT);

	Game* game = Game::GetInstance();

	game->Init(hwnd);
	SetWindowPos(hwnd, 0, 0, 0, windowrc::SCREEN_WIDTH * 2, windowrc::SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}