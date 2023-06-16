#pragma once
#include "debug.h"

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/Leaf303000.h"

class CLeaf : public CItem
{
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);
	int start_x;
	int start_y;
	BOOLEAN is_falling;

public:
	CLeaf() : CItem() {
		is_falling = FALSE;
	}
	CLeaf(float x, float y) : CItem(x, y) {
		is_falling = FALSE;
		start_x = x;
		start_y = y;
		SetState(LEAF_STATE_FLY);
	};
	CLeaf(float x, float y, int state) : CItem(x, y, state) {
		start_y = y;
		start_x = x;
		is_falling = FALSE;
	};

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsCollidable() { return is_collidable; }

	void Fly() { SetState(LEAF_STATE_FLY); }
};
