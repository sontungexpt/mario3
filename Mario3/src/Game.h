#pragma once

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800

#include <string>
#include <dinput.h>
#include <unordered_map>
#include "components/Texture/Texture.h"
#include "components/KeyboardHandler/KeyEventHandler.h"
#include "components/Scene/Scene.h"
#include "DrawingManager.h"
#include "configs/Game.h"

using namespace std;

class CGame
{
	static CGame* __instance;
	BOOLEAN is_paused = FALSE;
	ULONGLONG switch_scene_time_start = 0;
	int switch_scene_waiting_time = SCENE_SWITCH_WAITING_TIME;

	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D10RenderTargetView* pRenderTargetView = nullptr;
	ID3D10BlendState* pBlendStateAlpha = nullptr;			// To store alpha blending state

	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????

	LPDIRECTINPUT8       di;		// The DirectInput object
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	HINSTANCE hInstance;

	ID3D10SamplerState* pPointSamplerState;

	unordered_map<int, LPSCENE> scenes;
	int current_scene = INT_MIN;
	int next_scene = INT_MIN;
	BOOLEAN is_in_transition_scene = FALSE;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
	void _ParseSection_TEXTURES(string line);

	D3DXCOLOR background_color = D3DXCOLOR(156.0f / 255, 252.0f / 255, 240.0f / 255, 255.0f);
public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	// rect : if nullptr, the whole texture will be drawn
	//        if NOT nullptr, only draw that portion of the texture
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = nullptr, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha, sprite_width, sprite_height);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	// Keyboard related functions
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }

	ID3D10Device* GetDirect3DDevice() { return pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return pRenderTargetView; }

	ID3DX10Sprite* GetSpriteHandler() { return spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }
	int GetNextScene() { return next_scene; }
	BOOLEAN IsInTransitionScene() { return is_in_transition_scene; }

	static CGame* GetInstance();

	void SetPointSamplerState();

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
	float GetCamXPos() { return cam_x; }
	float GetCamYPos() { return cam_y; }

	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void AddScene(int id, LPSCENE scene) { scenes[id] = scene; };
	void RemoveScene(int id) { scenes.erase(id); }

	void Load(LPCWSTR gameFile);
	void SwitchScene();
	void InitiateSwitchScene(int scene_id);
	void SetSwitchSceneWaitingTime(int time) { switch_scene_waiting_time = time; }

	BOOLEAN IsPaused() { return is_paused; }
	void RenderPause() {
		if (is_paused)
		{
			CDrawingManager::RenderOverlay();
			CDrawingManager::RenderString(
				"PAUSE",
				cam_x + backBufferWidth / 2 - HUD_CHAR_BBOX_WIDTH * 5 / 2,
				cam_y + backBufferHeight / 2 - HUD_CHAR_BBOX_HEIGHT / 2
			);
		}
	}
	void TogglePause() { is_paused = ~is_paused; }

	D3DXCOLOR GetBackgroundColor() { return background_color; }
	void SetBackgroundColor(float R, float G, float B, float A)
	{
		background_color = D3DXCOLOR(R / 255.0f, G / 255.0f, B / 255, A);
	}

	~CGame();
};
typedef CGame* LPGAME;
