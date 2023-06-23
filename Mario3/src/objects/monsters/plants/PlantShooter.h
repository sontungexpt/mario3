#pragma once
#include "Plant.h"
#include "configs/monsters/Plant.h"
#include "configs/monsters/Plant602000.h"

class CPlantShooter : public CPlant
{
protected:
	BOOLEAN is_shooted;

	ULONGLONG time_reload_bullet_start;

	void Init() {
		vy = PLANT_SPEED_UP_DOWN; // move up and down

		is_shooted = FALSE;

		time_reload_bullet_start = 0;

		min_y = start_y - PLANT_SHOOTER_BBOX_HEIGHT;
	};

	void AdjustPos() {};
public:
	CPlantShooter(float x, float y) : CPlant(x, y) {
		Init();
	};

	CPlantShooter(float x, float y, int state) :CPlant(x, y, state) {
		Init();
	};

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};
