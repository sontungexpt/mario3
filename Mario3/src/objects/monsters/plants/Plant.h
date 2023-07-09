#pragma once
#include "objects/monsters/Monster.h"
#include "configs/monsters/Plant.h"

class CPlant : public CMonster
{
protected:

	int direction_up_down;

	// disable up down when player is entering hidden map
	BOOLEAN is_disabled_up_down;

	float min_y;
	float max_y;

	ULONGLONG time_down_start;
	ULONGLONG time_up_start;

	ULONGLONG time_out_up_state;
	ULONGLONG time_out_down_state;

	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e);
	virtual void UpdateVerticalPosition(DWORD dt);

	BOOLEAN IsTimeOutUpState();
	BOOLEAN IsTimeOutDownState();

public:

	CPlant(
		float x = 0, float y = 0, int state = PLANT_STATE_DOWN,
		ULONGLONG time_out_up_state = PLANT_TIME_OUT_UP_STATE,
		ULONGLONG time_out_down_state = PLANT_TIME_OUT_DOWN_STATE
	)
		: CMonster(x, y, 0, PLANT_SPEED_UP_DOWN, 0, 0),
		direction_up_down(1),
		min_y(0), max_y(0),
		is_disabled_up_down(FALSE),
		time_down_start(0), time_up_start(0),
		time_out_up_state(time_out_up_state),
		time_out_down_state(time_out_down_state)

	{
		SetState(state);
	};

	virtual void SetDisabledUpDown(BOOLEAN is_disabled_up_down) { this->is_disabled_up_down = is_disabled_up_down; };
	BOOLEAN IsDisabledUpDown() { return is_disabled_up_down; };

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void SetState(int state);

	void SetMinY(float min_y) { this->min_y = min_y; };
	void SetMaxY(float max_y) { this->max_y = max_y; };
};
