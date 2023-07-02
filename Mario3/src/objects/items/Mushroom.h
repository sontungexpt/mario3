#pragma once
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "debug.h"

#include "configs/items/Mushroom301000.h"
#include "Item.h"

class CMushroom : public CItem {
protected:
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

public:

	CMushroom() :CItem()
	{
		ay = MUSHROOM_GRAVITY;
	};
	CMushroom(float x, float y) :CItem(x, y)
	{
		ay = MUSHROOM_GRAVITY;
	};
	CMushroom(float x, float y, int state) :CItem(x, y, state)
	{
		ay = MUSHROOM_GRAVITY;
	};

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void SetState(int state);
	virtual void Walk() { SetState(MUSHROOM_STATE_WALKING); }
	virtual void BeCollected();
};
