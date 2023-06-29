#pragma once
#include "objects/GameObject.h"
#include "objects/monsters/Monster.h"
#include "configs/monsters/Gommba600000.h"
#include <objects/materials/EffectManager.h>

class CGoomba : public CMonster
{
protected:

public:

	CGoomba(float x, float y) :CMonster(x, y) {}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);

	virtual void Die() { SetState(MONSTER_STATE_DIE); };

	void BeKickedByKoopa();
};