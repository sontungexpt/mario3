#pragma once

#include "debug.h"
#include "GameObject.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

class CMarioAttackingZone : public CGameObject
{
	float width;
	float height;

	void OnCollisionWithMonster(LPCOLLISIONEVENT e);
	void OnCollisiionWithCBreakableBrick(LPCOLLISIONEVENT e);

public:

	CMarioAttackingZone(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
		: CGameObject(x, y), width(width), height(height)
	{}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	void Render() {
		RenderBoundingBox();
	}

	void SetHeight(float height) { this->height = height; }
	void SetWidth(float width) { this->width = width; }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state) {};

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

typedef CMarioAttackingZone* LPMARIO_ATTACKINGZONE;