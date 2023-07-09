#pragma once

#include "GameObject.h"

class CPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell
	float cellWidth;
	float cellHeight;
	int spriteIdBegin;
	int spriteIdMiddle;
	int spriteIdEnd;
	int isColliableAllDirection;

public:

	CPlatform(
		float x, float y,
		float cell_width,
		float cell_height,
		int length,
		int sprite_id_begin,
		int sprite_id_middle,
		int sprite_id_end,
		int is_blocking = 0,
		int isColliableAllDirection = -1
	) :CGameObject(x, y),
		length(length),
		cellWidth(cell_width),
		cellHeight(cell_height),
		spriteIdBegin(sprite_id_begin),
		spriteIdMiddle(sprite_id_middle),
		spriteIdEnd(sprite_id_end),
		isColliableAllDirection(isColliableAllDirection)
	{
		this->is_blocking = is_blocking;
	}

	int IsDirectionColliable(float nx, float ny);

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CPlatform* LPPLATFORM;