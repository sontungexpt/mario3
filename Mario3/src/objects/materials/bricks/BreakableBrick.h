#pragma once

#pragma once
#include "Brick.h"
#include "objects/items/Item.h"
#include "configs/materials/BreakableBrick101000.h"

class CBreakableBrick : public CBrick
{
private:
	BOOLEAN is_breaked;

public:

	CBreakableBrick(float x, float y) : CBrick(x, y)
	{
		is_breaked = FALSE;
	};

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void Render();
	void SetState(int state);

	// collision
	void OnNoCollision(DWORD dt);

	int IsCollidable() { return !is_breaked; };
	int IsBlocking() { return 1; };
};
