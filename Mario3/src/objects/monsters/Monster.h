#pragma once
#include "objects/GameObject.h"

#include "configs/Game.h"
#include "configs/monsters/Monster.h"

class CMonster : public CGameObject
{
protected:
	float ax;
	float ay;

	BOOLEAN dead; // is dead or not
	ULONGLONG dead_time; // time die
	BOOLEAN is_enemy; // is enemy with mario or not
	float disapear_time; // time to disappear after dead

public:
	CMonster(float x, float y, float disapear_time = MONSTER_DISAPPEAR_TIME) : CGameObject(x, y)
	{
		ax = 0; // acceleration x
		ay = GRAVITY; // acceleration y
		// TODO: need to create new class for moving object
		// This is a temporary solution

		dead_time = 0; // the time when monster die
		dead = FALSE; // is dead or not

		is_enemy = TRUE;

		this->disapear_time = disapear_time;
	};

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
	virtual int IsEnemy() { return is_enemy; }
};