#pragma once
#include <random>

#include "Item.h"
#include "configs/materials/BreakableBrick102000.h"

class CDebrisBrick : public CItem
{
private:
	ULONGLONG time_debris_splashing_start;

	default_random_engine debris_brick_speed;
	uniform_real_distribution<float> debris_brick_speed_generator;

	default_random_engine debris_brick_direction;
	uniform_int_distribution<int> debris_brick_direction_generator;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e) {};
	void SetState(int state);

public:
	CDebrisBrick(float x = 0, float y = 0, int state = DEBRIS_BRICK_STATE_SPLASHING)
		: CItem(x, y, state), time_debris_splashing_start(0),
		debris_brick_speed_generator(DEBRIS_BRICK_MIN_SPEED, DEBRIS_BRICK_MAX_SPEED),
		debris_brick_direction_generator(0, 1)
	{
		SetState(state);
	}

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	// action
	void Splash() { SetState(DEBRIS_BRICK_STATE_SPLASHING); }
};