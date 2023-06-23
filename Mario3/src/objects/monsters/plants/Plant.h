#pragma once
#include "objects/monsters/Monster.h"
#include "configs/monsters/Plant.h"

class CPlant : public CMonster
{
protected:
	BOOLEAN is_upping;
	BOOLEAN is_downing;

	// because in game y dimension is reversed so min_y y the position of top of plant when it is up
	float min_y;

	ULONGLONG time_down_start;
	ULONGLONG time_up_start;

	virtual void Init(float y) {
		ay = 0; // no gravity
		ax = 0;

		vx = 0; // no walk
		vy = PLANT_SPEED_UP_DOWN; // move up and down

		is_upping = FALSE;
		is_downing = FALSE;

		time_down_start = 0;
		time_up_start = 0;
	};

	void AdjustPos() {};
public:
	CPlant(float x, float y) : CMonster(x, y) {
		Init(y);
	};

	CPlant(float x, float y, int state) :CMonster(x, y, state) {
		Init(y);
	};

	// core
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void SetState(int state);
};
