#include "Sprites.h"

namespace core {
	Sprites* Sprites::instance = nullptr;

	Sprites* Sprites::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Sprites();
		}
		return instance;
	}

	void Sprites::Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
	{
		LPSPRITE sprite = new Sprite(id, left, top, right, bottom, tex);
		sprites_[id] = sprite;
	}

	LPSPRITE Sprites::Get(int id)
	{
		return sprites_[id];
	}
}