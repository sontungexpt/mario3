#pragma once
#include "Monster.h"

#include "objects/materials/EffectManager.h"

#include "configs/monsters/Gommba600000.h"

class CGoomba : public CMonster
{
protected:
	ULONGLONG time_hit_start;
	ULONGLONG time_kick_start;
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

public:

	CGoomba(float x, float y) :CMonster(x, y), time_hit_start(0), time_kick_start(0) {}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void Render();
	virtual void SetState(int state);

	virtual int IsCollidable() { return !dead && !is_mario_hitted && !is_kicked_by_koopa; }; // if dead, not collidable
	virtual int IsBlocking() { return 0; }

	virtual BOOLEAN IsDead() { return dead == TRUE || is_mario_hitted == TRUE || is_kicked_by_koopa == TRUE; }
	virtual void Die() { SetState(MONSTER_STATE_DIE); };
	virtual void BeKickedByKoopa();
	virtual void BeHitByMarioTail();
};