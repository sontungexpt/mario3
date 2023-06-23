#pragma once
#include "objects/GameObject.h"

#include "configs/Game.h"
#include "configs/monsters/Monster.h"

class CMonster : public CGameObject
{
private:
	void Init() {
		ax = 0; // acceleration x
		ay = GRAVITY; // acceleration y

		vx = MONSTER_WALKING_SPEED;
		max_vx = -1; // no limit speed

		// TODO: need to create new class for moving object
		// This is a temporary solution

		dead_time = 0; // the time when monster die
		disapear_time = MONSTER_DISAPPEAR_TIME; // the time to disappear after dead

		dead = FALSE; // is dead or not
		is_enemy = TRUE;
		is_on_platform = FALSE;
	};

protected:
	float max_vx;

	BOOLEAN dead; // is dead or not
	BOOLEAN is_enemy; // is enemy with mario or not
	BOOLEAN is_on_platform; // is on platform or not

	ULONGLONG dead_time; // time die
	ULONGLONG disapear_time; // time to disappear after dead

	void OnCollisionWithMonster(LPCOLLISIONEVENT e);

public:

	CMonster(float x, float y, ULONGLONG disapear_time = MONSTER_DISAPPEAR_TIME) : CGameObject(x, y)
	{
		Init();

		this->disapear_time = disapear_time;

		// default is moving left
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	CMonster(float x, float y, int state) : CGameObject(x, y, state)
	{
		Init();
	};

	virtual void LimitSpeed(float speed) { max_vx = speed; };
	virtual void SetIdle() { vx = 0; vy = 0; ax = 0; };

	// core
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	virtual void SetState(int state);

	virtual int IsCollidable() { return !dead; }; // if dead, not collidable
	virtual int IsBlocking() { return 0; }

	// collision
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsEnemy() { return is_enemy; }
	virtual void SetIsEnemy(BOOLEAN is_enemy) { this->is_enemy = is_enemy; }

	/// <summary>
	/// Compare position y of plant with mario
	/// </summary>
	/// <returns>
	///		-1: monster under mario,
	///		 1: monster on top mario,
	///		 0: monster and mario in same position,
	///		-2: monster is null,
	///		-3: monster is deleted,
	/// </returns>
	int CompareYWithMario(); //1 if mario on top plant, -1 if mario underplant

	/// <summary>
	///	Compare position x of plant with mario
	/// </summary>
	/// <returns>
	///		-1: monster left mario,
	///		 1: monster right mario,
	///		 0: monster and mario in same position,
	///		-2: monster is null,
	///		-3: monster is deleted,
	/// </returns>
	int CompareXWithMario(); //1 if mario left to plant, -1 if mario right to plant

	// this part is a other name for the same state
	BOOLEAN IsDead() { return dead == TRUE; }
	virtual void Die() { SetState(MONSTER_STATE_DIE); }
};

typedef  CMonster* LPMONSTER;