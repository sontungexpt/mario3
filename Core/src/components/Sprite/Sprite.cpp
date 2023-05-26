#include "Sprite.h"

namespace core {
	Sprite::Sprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
	{
		id_ = id;
		left_ = left;
		top_ = top;
		right_ = right;
		bottom_ = bottom;
		texture_ = tex;

		// Set the sprites shader resource view
		sprite_.pTexture = tex->GetShaderResourceView();

		sprite_.TexCoord.x = left_ / (float)tex->GetWidth();
		sprite_.TexCoord.y = top_ / (float)tex->GetHeight();

		int sprite_width = (right_ - left_ + 1);
		int sprite_height = (bottom_ - top_ + 1);

		sprite_.TexSize.x = sprite_width / (float)tex->GetWidth();
		sprite_.TexSize.y = sprite_height / (float)tex->GetHeight();

		sprite_.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		sprite_.TextureIndex = 0;

		D3DXMatrixScaling(&mat_scaling_, (FLOAT)sprite_width, (FLOAT)sprite_height, 1.0f);
	}

	void Sprite::Draw(float x, float y)
	{
		Game* game = Game::GetInstance();

		D3DXMATRIX mat_translation;
		D3DXMatrixTranslation(&mat_translation, x, (game->GetBackBufferHeight() - y), 0.1f);
		this->sprite_.matWorld = (mat_scaling_ * mat_translation);

		game->GetSpriteHandler()->DrawSpritesImmediate(&sprite_, 1, 0, 0);
	}
}