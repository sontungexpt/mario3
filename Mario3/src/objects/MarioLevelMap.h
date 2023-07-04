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

	// by pass block door rule when press 4
	BOOLEAN is_bypass_door_block_rule;

	float CalulateVx(float target_x, float target_y);
	float CalulateVy(float target_x, float target_y);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);

public:
	CMarioLevelMap(float x, float y) : CMario(x, y)
	{
		ax = 0;
		ay = 0;
		specical_target_x = -1;
		specical_target_y = -1;
		direction_hit_door = -1;
		is_stop_moving = TRUE;
		is_bypass_door_block_rule = FALSE;
		door = nullptr;
	}
	~CMarioLevelMap()
	{
		if (door)
			delete door;
		door = nullptr;
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

	void SetLevel(int level)
	{
		this->level = level;
		CGameData::GetInstance()->SetMarioLevel(level);
	}
	void EnterDoor() {
		if (is_stop_moving && door) {
			// mario just enter the door which is the next door
			// for example: mario is at door 1, he can enter door 2, but he can't enter door 3
			if (!is_bypass_door_block_rule &&
				door->GetDoorLevel() - 1 != CGameData::GetInstance()->GetMaxDoorLevelPassed())
			{
				return;
			}
			door->EnterDoor();
		}
	}

	void MoveToSpecialPos(float target_x, float target_y);
	void MoveToSpecialPosFrom(float x, float y, float special_posx, float special_posy);

	void ToggleByPassBlock() { is_bypass_door_block_rule = ~is_bypass_door_block_rule; }
	BOOLEAN IsBypassDoorBlockRule() { return is_bypass_door_block_rule; }

	BOOLEAN IsStopMoving() { return is_stop_moving; }
};
