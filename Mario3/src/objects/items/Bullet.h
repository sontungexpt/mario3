#pragma once
#include "Item.h"
#include "configs/items/Bullet302000.h"

class CBullet :public CItem
{
protected:
	float target_x;
	float target_y;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e) {};

public:
	CBullet(float x, float y) : CItem(x, y) {
		ay = BULLET_GRAVITY;
	};
	CBullet(float x, float y, float target_x, float target_y) : CItem(x, y) {
		this->target_x = target_x;
		this->target_y = target_y;

		// in future may be we will calculate to have the exactly speed in vx and vy to improve bullet accuracy
		// but now we just use the dèault speed and shoot the bullet with tan(alpha) = y/x

		vx = CalulateVx(target_x, target_y);
		vy = CalulateVy(target_x, target_y);
	};

	void Render();
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	float CalulateVx(float target_x, float target_y) {
		float distance_x = target_x - x;
		float distance_y = target_y - y;

		float alpha = atan(fabs(distance_y) / fabs(distance_x));

		float v_x = BULLET_SPEED * cos(alpha); // v>0 because 0< alpha < 90 degree

		return distance_x >= 0 ? v_x : -v_x;
	}

	float CalulateVy(float target_x, float target_y) {
		float distance_x = target_x - x;
		float distance_y = target_y - y;

		float alpha = atan(fabs(distance_y) / fabs(distance_x));

		float v_y = BULLET_SPEED * sin(alpha); // v>0 because 0< alpha < 90 degree

		return distance_y > 0 ? v_y : -v_y;
	}

	int IsCollidable() { return is_collidable; }
	int IsBlocking() { return 1; }
	void Shoot(float target_x, float target_y) {
		this->target_x = target_x;
		this->target_y = target_y;

		// in future may be we will calculate to have the exactly speed in vx and vy to improve bullet accuracy
		// but now we just use the dèault speed and shoot the bullet with tan(alpha) = y/x
		SetState(BULLET_STATE_SHOOT);
	}

	//void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	//void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	//void OnCollisionWithPlantEnemy(LPCOLLISIONEVENT e);
	//void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
