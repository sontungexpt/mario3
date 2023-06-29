#pragma once

#include "components/Texture/Texture.h"
#include "Game.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
	int GetLeft() { return left; }
	int GetTop() { return top; }
	int GetRight() { return right; }
	int GetBottom() { return bottom; }
	int GetId() { return id; }
	LPTEXTURE GetTexture() { return texture; }
};

typedef CSprite* LPSPRITE;