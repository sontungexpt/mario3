#pragma once

#include "Texture.h"
#include "Game.h"

using namespace core;

class Sprite
{
	// Sprite ID in the sprite database
	int id_;
	int left_;
	int top_;
	int right_;
	int bottom_;

	LPTEXTURE texture_;
	D3DX10_SPRITE sprite_;
	D3DXMATRIX mat_scaling_;

public:
	Sprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);
};

typedef Sprite* LPSPRITE;