#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <d3d10.h>
#include <d3dx10.h>

namespace core {
	class Texture
	{
	protected:
		ID3D10Texture2D* tex_;
		ID3D10ShaderResourceView* rsview_;
		int width_;
		int height_;

	public:
		Texture()
		{
			tex_ = nullptr;
			rsview_ = nullptr;
			width_ = -1;
			height_ = -1;
		}

		Texture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
		{
			tex_ = tex;
			rsview_ = rsview;

			D3D10_TEXTURE2D_DESC desc;
			tex_->GetDesc(&desc);
			width_ = desc.Width;
			height_ = desc.Height;
		}

		ID3D10ShaderResourceView* GetShaderResourceView() { return rsview_; }

		int GetWidth() { return width_; }
		int GetHeight() { return height_; }

		~Texture()
		{
			if (rsview_ != nullptr) rsview_->Release();
			if (tex_ != nullptr) tex_->Release();
		}
	};

	typedef Texture* LPTEXTURE;
}

#endif // !_TEXTURE_H_
