#pragma once
#pragma once

#include "Monster.h"
#include "configs/monsters/Monster.h"
#include "configs/monsters/Hammer604000.h"

class CHammer : public CMonster
{
public:

	CHammer(float x, float y) : CMonster(x, y)
	{
		ax = 0;
		ay = 0;
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
};

typedef  CMonster* LPMONSTER;