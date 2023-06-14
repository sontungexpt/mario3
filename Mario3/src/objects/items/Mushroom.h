#pragma once
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "debug.h"

#include "configs/items/Mushroom301000.h"
#include "Item.h"

class CMushroom : public CItem {
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

public:

	CMushroom() :CItem() {};
	CMushroom(float x, float y) :CItem(x, y) {};
	CMushroom(float x, float y, int state) :CItem(x, y, state) {};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	int IsCollidable() { return 1; }

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
	void SetState(int state);
	void Walk() { SetState(MUSHROOM_STATE_WALKING); }
};
