#pragma once

#include "configs/monsters/Koopa601000.h"
#include "Koopa.h"

class CWindKoopa : public CKoopa
{
private:
	BOOLEAN has_wind;
	ULONGLONG time_jump_start;

	void SetState(int state);
	int GetAniIdRed();
	int GetAniIdGreen();
public:
	CWindKoopa(float x, float y, int color = KOOPA_RED) : CKoopa(x, y, color) {
		// always move to mario in the first time
		has_wind = TRUE;
		time_jump_start = 0;
		SetState(MONSTER_STATE_FLY_LEFT);
	};

	//core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//collision
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// reset to default state
	void Defend();
};
