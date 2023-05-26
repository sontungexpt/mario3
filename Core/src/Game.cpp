#include "Game.h"

namespace core {
	Game* Game::instance = nullptr;

	/// <summary>
	/// Initialize DirectX,
	/// Create a Direct3D device for rendering within the window
	/// Initial Sprite library for rendering 2D images
	/// </summary>
	/// <param name="hwnd">Application window handle</param>
	void Game::Init(HWND hwnd)
	{
		// retrieve client area width & height so that we can create backbuffer height & width accordingly
		RECT rect;
		GetClientRect(hwnd, &rect);

		//make sure that the entire client area of the window is covered by the back buffer.
		back_buffer_width_ = rect.right + 1;
		back_buffer_height_ = rect.bottom + 1;

		// Create & clear the DXGI_SWAP_CHAIN_DESC structure
		DXGI_SWAP_CHAIN_DESC swap_chain_desc;
		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

		// Fill in the needed values
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.BufferDesc.Width = back_buffer_width_;
		swap_chain_desc.BufferDesc.Height = back_buffer_height_;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.OutputWindow = hwnd;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.Windowed = TRUE;

		// Create the D3D device and the swap chain
		HRESULT hresult = D3D10CreateDeviceAndSwapChain(
			nullptr,
			D3D10_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			D3D10_SDK_VERSION,
			&swap_chain_desc,
			&swap_chain_ptr_,
			&device_ptr_
		);

		if (hresult != S_OK)
		{
			DebugOut((wchar_t*)L"[ERROR] D3D10CreateDeviceAndSwapChain has failed %s %d", _W(__FILE__), __LINE__);
			return;
		}

		// Get the back buffer from the swapchain
		ID3D10Texture2D* back_buffer_ptr;
		hresult = swap_chain_ptr_->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&back_buffer_ptr);
		if (hresult != S_OK)
		{
			DebugOut((wchar_t*)L"[ERROR] pSwapChain->GetBuffer has failed %s %d", _W(__FILE__), __LINE__);
			return;
		}

		// create the render target view
		hresult = device_ptr_->CreateRenderTargetView(back_buffer_ptr, nullptr, &render_target_view_ptr_);

		back_buffer_ptr->Release();

		if (hresult != S_OK)
		{
			DebugOut((wchar_t*)L"[ERROR] CreateRenderTargetView has failed %s %d", _W(__FILE__), __LINE__);
			return;
		}

		// set the render target
		device_ptr_->OMSetRenderTargets(1, &render_target_view_ptr_, nullptr);

		// create and set the viewport
		D3D10_VIEWPORT view_port;
		view_port.Width = back_buffer_width_;
		view_port.Height = back_buffer_height_;
		view_port.MinDepth = 0.0f;
		view_port.MaxDepth = 1.0f;
		view_port.TopLeftX = 0;
		view_port.TopLeftY = 0;
		device_ptr_->RSSetViewports(1, &view_port);

		// create the sprite object to handle sprite drawing
		hresult = D3DX10CreateSprite(device_ptr_, 0, &sprite_);

		if (hresult != S_OK)
		{
			DebugOut((wchar_t*)L"[ERROR] D3DX10CreateSprite has failed %s %d", _W(__FILE__), __LINE__);
			return;
		}

		D3DXMATRIX mat_projection;

		// Create the projection matrix using the values in the viewport
		D3DXMatrixOrthoOffCenterLH(&mat_projection,
			(float)view_port.TopLeftX,
			(float)view_port.Width,
			(float)view_port.TopLeftY,
			(float)view_port.Height,
			0.1f,
			10);
		hresult = sprite_->SetProjectionTransform(&mat_projection);

		// Initialize the blend state for alpha drawing
		D3D10_BLEND_DESC state_desc;
		ZeroMemory(&state_desc, sizeof(D3D10_BLEND_DESC));
		state_desc.AlphaToCoverageEnable = FALSE;
		state_desc.BlendEnable[0] = TRUE;
		state_desc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
		state_desc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
		state_desc.BlendOp = D3D10_BLEND_OP_ADD;
		state_desc.SrcBlendAlpha = D3D10_BLEND_ZERO;
		state_desc.DestBlendAlpha = D3D10_BLEND_ZERO;
		state_desc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
		state_desc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
		device_ptr_->CreateBlendState(&state_desc, &plend_state_alpha_ptr_);

		DebugOut((wchar_t*)L"[INFO] InitDirectX has been successful\n");
		return;
	}

	/// <summary>
	/// Draw the whole texture or part of texture onto screen
	///	NOTE: This function is OBSOLTED in this example. Use Sprite::Render instead
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="tex"></param>
	/// <param name="rect"></param>
	void Game::Draw(float x, float y, LPTEXTURE tex, RECT* rect)
	{
		if (tex == nullptr) return;

		int sprite_width = 0;
		int sprite_height = 0;

		D3DX10_SPRITE sprite;

		// Set the sprite’s shader resource view
		sprite.pTexture = tex->GetShaderResourceView();

		if (rect == nullptr)
		{
			// top-left location in U,V coords
			sprite.TexCoord.x = 0;
			sprite.TexCoord.y = 0;

			// Determine the texture size in U,V coords
			sprite.TexSize.x = 1.0f;
			sprite.TexSize.y = 1.0f;

			sprite_width = tex->GetWidth();
			sprite_height = tex->GetHeight();
		}
		else
		{
			sprite.TexCoord.x = rect->left / (float)tex->GetWidth();
			sprite.TexCoord.y = rect->top / (float)tex->GetHeight();

			sprite_width = (rect->right - rect->left + 1);
			sprite_height = (rect->bottom - rect->top + 1);

			sprite.TexSize.x = sprite_width / (float)tex->GetWidth();
			sprite.TexSize.y = sprite_height / (float)tex->GetHeight();
		}

		// Set the texture index. Single textures will use 0
		sprite.TextureIndex = 0;

		// The color to apply to this sprite, full color applies white.
		sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// Build the rendering matrix based on sprite location
		// The translation matrix to be created
		D3DXMATRIX mat_translation;

		// Create the translation matrix
		D3DXMatrixTranslation(&mat_translation, x, (back_buffer_height_ - y), 0.1f);

		// Scale the sprite to its correct width and height
		// because by default, DirectX draws it with width = height = 1.0f
		D3DXMATRIX mat_scaling;
		D3DXMatrixScaling(&mat_scaling, (FLOAT)sprite_width, (FLOAT)sprite_height, 1.0f);

		// Setting the sprite’s position and size
		sprite.matWorld = (mat_scaling * mat_translation);

		sprite_->DrawSpritesImmediate(&sprite, 1, 0, 0);
	}

	void Game::Draw(float x, float y, LPTEXTURE tex, int left, int top, int right, int bottom)
	{
		RECT rect;
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
		this->Draw(x, y, tex, &rect);
	}

	/// <summary>
	/// Utility function to wrap D3DX10CreateTextureFromFileEx
	/// </summary>
	/// <param name="texturePath"></param>
	/// <returns></returns>
	LPTEXTURE Game::LoadTexture(LPCWSTR texture_path)
	{
		ID3D10Resource* resource_ptr = nullptr;
		ID3D10Texture2D* tex = nullptr;

		// Loads the texture into a temporary ID3D10Resource object
		HRESULT hr = D3DX10CreateTextureFromFile(device_ptr_,
			texture_path,
			nullptr, //&info,
			nullptr,
			&resource_ptr,
			nullptr);

		// Make sure the texture was loaded successfully
		if (FAILED(hr))
		{
			DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texture_path, hr);
			return nullptr;
		}

		// Translates the ID3D10Resource object into a ID3D10Texture2D object
		resource_ptr->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
		resource_ptr->Release();

		if (!tex) {
			DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
			return nullptr;
		}

		//
		// Create the Share Resource View for this texture
		//
		// Get the texture details
		D3D10_TEXTURE2D_DESC desc;
		tex->GetDesc(&desc);

		// Create a shader resource view of the texture
		D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

		// Clear out the shader resource view description structure
		ZeroMemory(&SRVDesc, sizeof(SRVDesc));

		// Set the texture format
		SRVDesc.Format = desc.Format;

		// Set the type of resource
		SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = desc.MipLevels;

		ID3D10ShaderResourceView* gSpriteTextureRV = nullptr;

		device_ptr_->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

		DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texture_path);

		return new Texture(tex, gSpriteTextureRV);
	}
	Game* Game::GetInstance()
	{
		if (instance == nullptr) instance = new Game();
		return instance;
	}
}