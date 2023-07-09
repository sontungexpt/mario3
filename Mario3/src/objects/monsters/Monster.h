#pragma once

#include "objects/GameObject.h"

#include "configs/Game.h"
#include "configs/monsters/Monster.h"

class CMonster : public CGameObject
{
protected:
	float max_vx;

	BOOLEAN dead; // is dead or not
	BOOLEAN is_enemy; // is enemy with mario or not
	BOOLEAN is_on_platform; // is on platform or not

	ULONGLONG dead_time; // time die
	ULONGLONG disapear_time; // time to disappear after dead

	virtual void OnCollisionWithMonster(LPCOLLISIONEVENT e);

	// two ways collision
	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);

	/// <summary>
	/// The monster will be died and deleted if move out of width screen or the monster jump to hole
	/// </summary>
	virtual int RemoveWhenMoveToDangerousSpace();
	virtual void SetIdle() { vx = 0; vy = 0; ax = 0; };

public:

	CMonster(float x = 0, float y = 0, ULONGLONG disapear_time = MONSTER_DISAPPEAR_TIME)
		: CGameObject(x, y, MONSTER_WALKING_SPEED, 0, 0, GRAVITY, -1, -1, MONSTER_STATE_WALKING_LEFT, 1, 0),
		dead_time(0), disapear_time(disapear_time),
		dead(FALSE), is_enemy(TRUE), is_on_platform(FALSE)
	{
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	CMonster(float x, float y, int state)
		:CMonster(x, y, GRAVITY, state)
	{};

	CMonster(float x, float y, float ay, int state = MONSTER_STATE_WALKING_LEFT)
		: CGameObject(x, y, MONSTER_WALKING_SPEED, 0, 0, ay, -1, -1, state, 1, 0),
		dead_time(0), disapear_time(MONSTER_DISAPPEAR_TIME),
		dead(FALSE), is_enemy(TRUE), is_on_platform(FALSE)
	{
		SetState(state);
	};

	virtual void LimitSpeed(float speed) { max_vx = speed; };

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

	virtual void BeKickedByKoopa();
};

typedef  CMonster* LPMONSTER;