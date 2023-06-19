#pragma once
#include "debug.h"

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/Leaf303000.h"

class CLeaf : public CItem
{
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	BOOLEAN is_falling;

public:
	CLeaf() : CItem() {
		is_falling = FALSE;
	}
	CLeaf(float x, float y) : CItem(x, y) {
		is_falling = FALSE;
		SetState(LEAF_STATE_FLY);
	};
	CLeaf(float x, float y, int state) : CItem(x, y, state) {
		is_falling = FALSE;
	};

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	int IsCollidable() { return 0; }

	void Fly() { SetState(LEAF_STATE_FLY); }
};
