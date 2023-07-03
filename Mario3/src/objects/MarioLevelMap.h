#pragma once

#include "debug.h"
#include "GameData.h"
#include "Game.h"

#include "Mario.h"
#include "materials/Door.h"
#include "configs/Mario.h"

class CMarioLevelMap : public CMario
{
private:
	CDoor* door;

	float specical_target_x;
	float specical_target_y;
	float distance_specical_x;
	float distance_specical_y;

	int direction_hit_door;
	BOOLEAN is_stop_moving;

	void OnCollisionWithDoor(LPCOLLISIONEVENT e);

public:
	CMarioLevelMap(float x, float y) : CMario(x, y)
	{
		door = nullptr;
		ax = 0;
		ay = 0;
		specical_target_x = -1;
		specical_target_y = -1;
		direction_hit_door = -1;
		is_stop_moving = TRUE;
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return state != MARIO_LEVEL_MAP_STATE_MOVING_SPECIAL_POS; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int level) { CGameData::GetInstance()->SetMarioLevel(level); }
	void EnterDoor() { if (door) door->EnterDoor(); }
	void MoveToSpecialPos(float target_x, float target_y);
	void MoveToSpecialPosFrom(float x, float y, float special_posx, float special_posy);

	float CalulateVx(float target_x, float target_y);

	float CalulateVy(float target_x, float target_y);
};
