#pragma once

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/BreakableBrickSwitch304000.h"

class CBreakableBrickSwitch : public CItem {
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	float min_y;

public:
	CBreakableBrickSwitch(float x = 0, float y = 0, float min_y = 0.0f)
		:CItem(x, y, 0, UNKNOWN_STATE), min_y(min_y)
	{}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return state == BREAKABLE_BRICK_SWITCH_STATE_NORMAL; }
	int IsBlocking() { return 1; }

	void SetState(int state);
	void MoveOutBreakablerBrickSwitch();

	void BeCollected();
};