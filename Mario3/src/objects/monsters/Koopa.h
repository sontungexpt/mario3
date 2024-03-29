﻿#pragma once

#include "configs/monsters/Koopa601000.h"
#include "Monster.h"

class CKoopa : public CMonster
{
protected:
	int color; // green or red

	ULONGLONG defend_time_start;
	ULONGLONG comeback_time_start;
	ULONGLONG hit_time_start;

	BOOLEAN is_defend;
	BOOLEAN is_comeback;
	BOOLEAN is_mario_kicked;
	BOOLEAN is_mario_holding;
	BOOLEAN is_limit_moving_space;
	BOOLEAN can_hit_again;

	float limit_x_positive;
	float limit_x_negative;

	float mario_speed_when_kicked;

	virtual void OnCollisionWithMonster(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

	// two ways collision with player
	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	virtual int GetAniIdRed();
	virtual int GetAniIdGreen();

	// reset to default state
	virtual void Reset();

public:
	CKoopa(float x, float y, int color = KOOPA_RED, BOOLEAN is_limit_moving_space = TRUE)
		: CMonster(x, y),
		color(color),
		is_defend(FALSE),
		is_comeback(FALSE),
		is_mario_kicked(FALSE),
		is_mario_holding(FALSE),
		can_hit_again(TRUE),
		is_limit_moving_space(is_limit_moving_space),
		mario_speed_when_kicked(0.0f),
		defend_time_start(-1),
		comeback_time_start(-1),
		hit_time_start(-1),
		limit_x_positive(0.0f),
		limit_x_negative(0.0f)

	{
		max_vx = KOOPA_MAX_SPEED;
		//SetState(MONSTER_STATE_WALKING_LEFT);
	};

	//core
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

	//collision
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	BOOLEAN IsDefend() { return is_defend; }
	virtual void Defend();
	virtual void ComebackAfterDefend() { SetState(KOOPA_STATE_COMEBACK); }

	virtual void BeHold();
	virtual void BeKick() { SetState(KOOPA_STATE_IS_KICKED); }

	BOOLEAN IsMarioKicked() { return is_mario_kicked; }
	BOOLEAN IsMarioHolding() { return is_mario_holding; }

	virtual void MoveRight() { SetState(MONSTER_STATE_WALKING_RIGHT); }
	virtual void MoveLeft() { SetState(MONSTER_STATE_WALKING_LEFT); }
	virtual void StopMovingX() { SetState(KOOPA_STATE_BẸ_JUMP_ON_AFTER_KICKED); }

	virtual void Die() { SetState(MONSTER_STATE_DIE); }
	virtual void BeKickedByKoopa();
	virtual void BeHitByMarioTail();
};
