#pragma once

#pragma once
#include "Goomba.h"
#include "objects/monsters/Monster.h"
#include "configs/monsters/Gommba600000.h"

class CWindGoomba : public CGoomba
{
private:
	ULONGLONG time_jump_start;
	BOOLEAN has_wind;

public:

	CWindGoomba(float x, float y) :CGoomba(x, y) {
		has_wind = TRUE;
		time_jump_start = 0;
		SetState(MONSTER_STATE_FLY_LEFT);
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();

	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void OnCollisionWith(LPCOLLISIONEVENT e);

	BOOLEAN HasWind() { return has_wind; }
	void CutWind() { has_wind = FALSE; }
	void ReverseWind() { has_wind = TRUE; }
	void Die();
};