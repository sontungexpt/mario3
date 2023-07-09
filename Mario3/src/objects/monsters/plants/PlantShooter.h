#pragma once
#include "Plant.h"
#include "configs/monsters/Plant.h"
#include "configs/monsters/PlantShooter602000.h"

class CPlantShooter : public CPlant
{
protected:
	int color;

	BOOLEAN is_shooted;
	ULONGLONG time_reload_bullet_start;

	void UpdateBullet(DWORD dt);
	void ShootBulletIfReady();
	bool CanShootBullet();

public:

	CPlantShooter(float x, float y, int state = PLANT_STATE_DOWN, int color = PLANT_SHOOTER_RED)
		:CPlant(x, y, state),
		color(color),
		time_reload_bullet_start(0),
		is_shooted(FALSE)
	{
		if (color == PLANT_SHOOTER_GREEN)
		{
			min_y = start_y - PLANT_SHOOTER_BBOX_HEIGHT_GREEN;
			max_y = start_y + PLANT_SHOOTER_BBOX_HEIGHT_GREEN;
		}
		else if (color == PLANT_SHOOTER_RED)
		{
			min_y = start_y - PLANT_SHOOTER_BBOX_HEIGHT_RED;
			max_y = start_y + PLANT_SHOOTER_BBOX_HEIGHT_RED;
		}
	};

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();
	int GetAniIdRed();
	int GetAniIdGreen();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};
