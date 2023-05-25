#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "Texture.h"
#include "debug.h"

namespace core {
	class Game {
		static Game* instance;

		// Window handle
		HWND hwnd_;

		// Backbuffer width & height
		int back_buffer_width_ = 0;
		int back_buffer_height_ = 0;

		// directX objects
		ID3D10Device* device_ptr_ = nullptr;
		IDXGISwapChain* swap_chain_ptr_ = nullptr;
		ID3D10RenderTargetView* render_target_view_ptr_ = nullptr;
		ID3D10BlendState* plend_state_alpha_ptr_ = nullptr;
		ID3DX10Sprite* sprite_ = NULL;
	public:
		~Game() {};
		// Init DirectX, Sprite Handler
		void Init(HWND hwnd);

		// Draw a portion or ALL the texture at position (x,y) on the screen
		// rect : if NULL, the whole texture will be drawn
		//        if NOT NULL, only draw that portion of the texture
		void Draw(float x, float y, LPTEXTURE tex, RECT* rect = nullptr);

		void Draw(float x, float y, LPTEXTURE tex, int left, int top, int right, int bottom);

		LPTEXTURE LoadTexture(LPCWSTR texture_path);

		ID3D10Device* GetDirect3DDevice() { return device_ptr_; }
		IDXGISwapChain* GetSwapChain() { return swap_chain_ptr_; }
		ID3D10RenderTargetView* GetRenderTargetView() { return render_target_view_ptr_; }
		ID3DX10Sprite* GetSpriteHandler() { return sprite_; }
		ID3D10BlendState* GetAlphaBlending() { return plend_state_alpha_ptr_; };

		int GetBackBufferWidth() { return back_buffer_width_; }
		int GetBackBufferHeight() { return back_buffer_height_; }
		static Game* GetInstance();
	};
}

#endif