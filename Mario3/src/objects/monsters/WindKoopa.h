#pragma once

#include "Koopa.h"
#include "configs/monsters/Koopa601000.h"

class CWindKoopa : public CKoopa
{
private:
	BOOLEAN has_wind;
	ULONGLONG time_jump_start;

	int GetAniIdRed();
	int GetAniIdGreen();

public:
	CWindKoopa(float x, float y, int color = KOOPA_RED, BOOLEAN is_limit_moving_space = TRUE)
		: CKoopa(x, y, color, is_limit_moving_space), has_wind(TRUE), time_jump_start(0)
	{
		SetState(MONSTER_STATE_FLY_LEFT);
	};

	//core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);

	//collision
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// reset to default state
	void Defend();
	void BeKickedByKoopa();
	void BeHitByMarioTail();
};
