#pragma once
#include "debug.h"
#include "objects/GameObject.h"
#include "configs/Effect.h"

using namespace std;

class CEffect : public CGameObject
{
	ULONGLONG appear_time_start;
	int type;

public:
	CEffect(float x, float y) : CGameObject(x, y) {
		vy = EFFECT_SPEED_Y;
		appear_time_start = 0;
	}

	CEffect(float x, float y, int type) : CGameObject(x, y) {
		vy = EFFECT_SPEED_Y;
		this->type = type;
		SetState(EFFECT_STATE_APPEAR);
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};