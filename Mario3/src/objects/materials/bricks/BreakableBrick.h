#pragma once

#include "CreatableBrick.h"
#include "objects/items/Item.h"
#include "configs/materials/BreakableBrick102000.h"

class CBreakableBrick : public CCreatableBrick
{
private:
	BOOLEAN is_breaked;
	BOOLEAN is_blocked;

	float GetItemReferenceY(CItem* item) { return y; };
	float GetItemReferenceX(CItem* item) { return x; };

	void CreateItem();

public:

	CBreakableBrick(float x, float y, int item_type = BREAKABLE_BRICK_NONE) : CCreatableBrick(x, y, item_type) {
		is_breaked = FALSE;
		is_blocked = FALSE;
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
	};

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void Render();
	void SetState(int state);

	// collision

	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable() { return !is_breaked; }
	int IsBlocking() { return 1; }

	// this part is the other name to call SetState
	void Bounce() { SetState(BREAKABLE_BRICK_STATE_BOUNCE); }
	void Break() { SetState(BREAKABLE_BRICK_STATE_BREAK); }
};