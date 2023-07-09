#pragma once
#include "Plant.h"
#include "configs/monsters/CarnivorousPlant603000.h"

class CCarnivorousPlant : public CPlant
{
private:

public:

	CCarnivorousPlant(float x, float y, int state = PLANT_STATE_DOWN)
		:CPlant(x, y, state, CARNIVOROUS_PLANT_TIME_OUT_UP_STATE, CARNIVOROUS_PLANT_TIME_OUT_DOWN_STATE)
	{
		min_y = start_y - CARNIVOROUS_PLANT_BBOX_HEIGHT;
		max_y = start_y + CARNIVOROUS_PLANT_BBOX_HEIGHT;
	};

	// core
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
