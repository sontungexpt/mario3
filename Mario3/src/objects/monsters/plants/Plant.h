#pragma once
#include "objects/monsters/Monster.h"
#include "configs/monsters/Plant.h"

class CPlant : public CMonster
{
protected:
	BOOLEAN is_upping;
	BOOLEAN is_downing;

	// disable up down when player is entering hidden map
	BOOLEAN is_disabled_up_down;

	// because in game y dimension is reversed so min_y y the position of top of plant when it is up

	// need to be init in child class
	float min_y;
	float max_y;

	ULONGLONG time_down_start;
	ULONGLONG time_up_start;

	ULONGLONG time_out_up_state;
	ULONGLONG time_out_down_state;

	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	virtual void Init(float y) {
		ay = 0; // no gravity
		ax = 0;

		vx = 0; // no walk
		vy = PLANT_SPEED_UP_DOWN; // move up and down

		is_upping = FALSE;
		is_downing = FALSE;
		is_disabled_up_down = FALSE;

		time_down_start = 0;
		time_up_start = 0;

		time_out_up_state = PLANT_TIME_OUT_UP_STATE;
		time_out_down_state = PLANT_TIME_OUT_DOWN_STATE;
	};

public:
	CPlant(float x, float y) : CMonster(x, y) {
		Init(y);
	};

	CPlant(float x, float y, int state) :CMonster(x, y, state) {
		Init(y);
	};

	// core
	virtual void SetDisabledUpDown(BOOLEAN is_disabled_up_down)
	{
		this->is_disabled_up_down = is_disabled_up_down;
	};
	BOOLEAN IsDisabledUpDown() { return is_disabled_up_down; };

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void SetState(int state);

	void SetMinY(float min_y) { this->min_y = min_y; };
	void SetMaxY(float max_y) { this->max_y = max_y; };
};
