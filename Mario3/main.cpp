#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "utils/debug.h"
#include "utils/Game.h"
#include "GameObjects/GameObject.h"
#include "configs/WindowConfig.h"

using namespace std;

#define TEXTURE_PATH_BRICK L"assets/brick.png"
#define TEXTURE_PATH_MARIO L"assets/mario.png"

#define TEXTURE_PATH_MISC L"assets/misc.png"

CMario* mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 100.0f
#define MARIO_START_VX 0.1f
#define MARIO_START_VY 0.1f

CBrick* brick;
#define BRICK_X 10.0f
#define BRICK_Y 120.0f

LPTEXTURE texMario = NULL;
LPTEXTURE texBrick = NULL;
LPTEXTURE texMisc = NULL;

//vector<LPGAMEOBJECT> objects;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	Game* game = Game::GetInstance();
	texBrick = game->LoadTexture(TEXTURE_PATH_BRICK);
	texMario = game->LoadTexture(TEXTURE_PATH_MARIO);
	texMisc = game->LoadTexture(TEXTURE_PATH_MISC);

	// Load a sprite sheet as a texture to try drawing a portion of a texture. See function Render
	//texMisc = game->LoadTexture(MISC_TEXTURE_PATH);

	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX, MARIO_START_VY, texMario);
	brick = new CBrick(BRICK_X, BRICK_Y, texBrick);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	/*
	for (int i=0;i<n;i++)
		objects[i]->Update(dt);
	*/

	mario->Update(dt);
	brick->Update(dt);

	//DebugOutTitle(L"01 - Skeleton %0.1f, %0.1f", mario->GetX(), mario->GetY());
}

/*
	Render a frame
*/
void Render()
{
	Game* g = Game::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, WindowConfig::BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();
		mario->Render();

		// Uncomment this line to see how to draw a porttion of a texture
		//g->Draw(10, 10, texMisc, 300, 117, 317, 134);
		//g->Draw(10, 10, texMario, 215, 120, 234, 137);

		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WindowConfig::WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WindowConfig::WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WindowConfig::WINDOW_CLASS_NAME,
			WindowConfig::WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / WindowConfig::MAX_FRAME_RATE;

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
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, WindowConfig::SCREEN_WIDTH, WindowConfig::SCREEN_HEIGHT);

	Game* game = Game::GetInstance();
	game->Init(hWnd);

	SetWindowPos(hWnd, 0, 0, 0, WindowConfig::SCREEN_WIDTH * 2, WindowConfig::SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}