#pragma once
#include "Plant.h"
#include "configs/monsters/CarnivorousPlant603000.h"

class CCarnivorousPlant : public CPlant
{
private:
	void Init() {
		min_y = start_y - CARNIVOROUS_PLANT_BBOX_HEIGHT;
		time_out_up_state = CARNIVOROUS_PLANT_TIME_OUT_UP_STATE;
		time_out_down_state = CARNIVOROUS_PLANT_TIME_OUT_DOWN_STATE;
	};

	void AdjustPos() {};
public:
	CCarnivorousPlant(float x, float y) : CPlant(x, y) {
		Init();
	};

	CCarnivorousPlant(float x, float y, int state) :CPlant(x, y, state) {
		Init();
	};

	// core
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
