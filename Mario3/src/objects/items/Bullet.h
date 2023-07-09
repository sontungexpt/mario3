#pragma once
#include "Item.h"
#include "configs/items/Bullet302000.h"

class CBullet :public CItem
{
protected:
	float target_x;
	float target_y;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);
	float CalculateVx(float target_x, float target_y);
	float CalculateVy(float target_x, float target_y);

public:

	CBullet(float x = 0, float y = 0, float target_x = 0, float target_y = 0)
		: CItem(x, y, BULLET_GRAVITY, UNKNOWN_STATE),
		target_x(target_x), target_y(target_y)
	{};

	void Render();
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }

	void Shoot(float target_x, float target_y);
	void BeCollected();
};
