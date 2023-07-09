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

	CMushroom(float x = 0, float y = 0, int state = UNKNOWN_STATE)
		:CItem(x, y, MUSHROOM_GRAVITY, state)
	{
		SetState(state);
	};

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void SetState(int state);

	virtual void Walk() { SetState(MUSHROOM_STATE_WALKING); }
	virtual void BeCollected();
};
