#pragma once
#include "Monster.h"

#include "objects/materials/EffectManager.h"

#include "configs/monsters/Gommba600000.h"

class CGoomba : public CMonster
{
protected:

public:

	CGoomba(float x, float y) :CMonster(x, y) {}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void SetState(int state);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void Die() { SetState(MONSTER_STATE_DIE); };
	virtual void BeKickedByKoopa();
};