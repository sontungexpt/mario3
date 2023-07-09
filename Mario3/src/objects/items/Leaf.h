#pragma once
#include <random>

#include "debug.h"

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/Leaf303000.h"

class CLeaf : public CItem
{
	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	int nx;
	BOOLEAN is_falling;

	// Randomly generate upward wind
	uniform_int_distribution<int> upward_wind_chance_distribution;
	default_random_engine has_upward_wind;

	// Wind speed is also never fixed
	// so leaves fly at an unknown initial speed
	uniform_real_distribution<float> wind_speed_generator;
	default_random_engine wind_speed;

public:

	CLeaf(float x = 0, float y = 0, int state = LEAF_STATE_FLY)
		: CItem(x, y, state),
		upward_wind_chance_distribution(0, 9),
		wind_speed_generator(LEAF_MIN_WIN_SPEED, LEAF_MAX_WIN_SPEED),
		is_falling(false)
	{}

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void BeCollected();

	int IsCollidable() { return 0; }

	void Fly() { SetState(LEAF_STATE_FLY); }
};
