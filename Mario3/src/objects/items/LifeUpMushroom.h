#pragma once
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "debug.h"

#include "configs/items/Mushroom301000.h"
#include "Mushroom.h"

class CLifeUpMushroom : public CMushroom {
private:
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

public:

	CLifeUpMushroom() :CMushroom()
	{
		ay = MUSHROOM_GRAVITY;
	};
	CLifeUpMushroom(float x, float y) :CMushroom(x, y)
	{
		ay = MUSHROOM_GRAVITY;
	};
	CLifeUpMushroom(float x, float y, int state) :CMushroom(x, y, state)
	{
		ay = MUSHROOM_GRAVITY;
	};

	void Render();
	void BeCollected();
};
