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

	CLifeUpMushroom(float x = 0, float y = 0, int state = UNKNOWN_STATE)
		:CMushroom(x, y, state)
	{};

	void Render();
	void BeCollected();
};
