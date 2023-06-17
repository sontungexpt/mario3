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

		max_speed = -1; // no limit speed
		vx = MONSTER_WALKING_SPEED;
		// TODO: need to create new class for moving object
		// This is a temporary solution

		dead_time = 0; // the time when monster die
		dead = FALSE; // is dead or not

		is_enemy = TRUE;
	};

protected:
	float ax;
	float ay;
	float max_speed;

	BOOLEAN dead; // is dead or not
	ULONGLONG dead_time; // time die
	BOOLEAN is_enemy; // is enemy with mario or not
	float disapear_time; // time to disappear after dead

	virtual void AdjustHeight() = 0; // adjust height when change animation render
public:

	CMonster(float x, float y, float disapear_time = MONSTER_DISAPPEAR_TIME) : CGameObject(x, y)
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

	virtual void LimitSpeed(float speed) { max_speed = speed; };
	virtual void SetIdle() { vx = 0; vy = 0; ax = 0; };

	// core
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	virtual int IsCollidable() { return 1; };
	virtual void SetState(int state);
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
	void Die() { SetState(MONSTER_STATE_DIE); }
};

typedef  CMonster* LPCMONSTER;