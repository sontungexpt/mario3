#pragma once

#include "configs/monsters/Koopa601000.h"
#include "Koopa.h"

class CWindKoopa : public CKoopa
{
private:
	BOOLEAN has_wind;
	ULONGLONG time_jump_start;

	void AdjustPos();

public:
	CWindKoopa(float x, float y) : CKoopa(x, y) {
		//mario_speed_when_kicked = 0.0f;
		//max_vx = KOOPA_MAX_SPEED;

		// always move to mario in the first time
		has_wind = TRUE;
		time_jump_start = 0;
		SetState(MONSTER_STATE_FLY);
	};

	//core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//collision
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// reset to default state
	void Reset();
	void Die();
};
