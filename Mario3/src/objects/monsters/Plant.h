#pragma once
#include "Monster.h"
#include "configs/monsters/Plant602000.h"

class CPlant : public CMonster
{
private:
	BOOLEAN is_shooted;
	BOOLEAN is_upping;
	BOOLEAN is_downing;

	// because in game y dimension is reversed so min_y y the position of top of plant when it is up
	float min_y;
	float start_y;

	ULONGLONG time_down_start;
	ULONGLONG time_up_start;
	ULONGLONG time_reload_bullet_start;

	void Init(float y) {
		ay = 0; // no gravity
		ax = 0;

		vx = 0; // no walk
		vy = PLANT_SPEED_UP_DOWN; // move up and down

		is_shooted = FALSE;
		is_upping = FALSE;
		is_downing = FALSE;

		time_down_start = 0;
		time_up_start = 0;
		time_reload_bullet_start = 0;

		start_y = y;
		min_y = start_y - PLANT_BBOX_HEIGHT;
	};

public:
	CPlant(float x, float y) : CMonster(x, y) {
		Init(y);
	};

	CPlant(float x, float y, int state) :CMonster(x, y, state) {
		Init(y);
	};

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);
};
