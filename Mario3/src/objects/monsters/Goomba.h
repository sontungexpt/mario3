#pragma once
#include "objects/GameObject.h"
#include "objects/monsters/Monster.h"
#include "configs/monsters/Gommba600000.h"

class CGoomba : public CMonster
{
private:

	ULONGLONG die_start;

public:

	CGoomba(float x, float y) :CMonster(x, y) {
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
};