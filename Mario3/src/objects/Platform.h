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
	BOOLEAN canbe_step_on;

public:
	CPlatform(
		float x, float y,
		float cell_width,
		float cell_height,
		int length,
		int sprite_id_begin,
		int sprite_id_middle,
		int sprite_id_end,
		int canbe_step_on = 0
	) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->canbe_step_on = canbe_step_on;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return canbe_step_on; }
	BOOLEAN CanBeStepOn() { return canbe_step_on; }
};

typedef CPlatform* LPPLATFORM;