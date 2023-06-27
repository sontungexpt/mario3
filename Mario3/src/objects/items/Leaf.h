#pragma once
#include "debug.h"

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/Leaf303000.h"

class CLeaf : public CItem
{
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	BOOLEAN is_falling;
	BOOLEAN is_moved_right;
	BOOLEAN is_moved_left;
	int nx;

public:
	CLeaf() : CItem() {
		nx = 0;
		is_falling = FALSE;
	}
	CLeaf(float x, float y) : CItem(x, y) {
		nx = 0;
		is_falling = FALSE;
		SetState(LEAF_STATE_FLY);
	};
	CLeaf(float x, float y, int state) : CItem(x, y, state) {
		nx = 0;
		is_falling = FALSE;
		is_moved_right = FALSE;
		is_moved_left = FALSE;
	};

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void BeCollected();

	int IsCollidable() { return 0; }

	void Fly() { SetState(LEAF_STATE_FLY); }
};
