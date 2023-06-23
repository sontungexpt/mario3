#pragma once
#include "Plant.h"
#include "configs/monsters/Plant.h"
#include "configs/monsters/PlantShooter602000.h"

class CPlantShooter : public CPlant
{
protected:
	BOOLEAN is_shooted;
	int type;
	ULONGLONG time_reload_bullet_start;

	void Init(int type) {
		this->type = type;
		vy = PLANT_SPEED_UP_DOWN; // move up and down

		is_shooted = FALSE;

		time_reload_bullet_start = 0;
		if (type == PLANT_SHOOTER_GREEN)
			min_y = start_y - PLANT_SHOOTER_BBOX_HEIGHT_GREEN;
		else if (type == PLANT_SHOOTER_RED)
			min_y = start_y - PLANT_SHOOTER_BBOX_HEIGHT_RED;
	};

	void AdjustPos() {};
public:
	CPlantShooter(float x, float y) : CPlant(x, y) {
		Init(PLANT_SHOOTER_RED);
	};

	CPlantShooter(float x, float y, int state, int type = PLANT_SHOOTER_RED) :CPlant(x, y, state) {
		Init(type);
	};

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int GetAniIdRed();
	int GetAniIdGreen();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};
