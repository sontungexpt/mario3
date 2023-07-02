#pragma once
#include "debug.h"
#include "objects/GameObject.h"
#include "configs/Effect.h"

using namespace std;

class CEffect : public CGameObject
{
	ULONGLONG appear_time_start;
	ULONGLONG increase_alpha_time_start;

	int type;
	int effect;
	float alpha;

public:
	CEffect(float x, float y) : CGameObject(x, y) {
		vy = EFFECT_SPEED_Y;
		appear_time_start = 0;
		increase_alpha_time_start = 0;
		effect = EFFECT_FADE_OUT;
		alpha = 0.0f;
	}

	CEffect(float x, float y, int type, int effect = EFFECT_FADE_OUT) : CGameObject(x, y) {
		this->type = type;
		this->effect = effect;
		alpha = 0.0f;
		increase_alpha_time_start = 0;
		vy = EFFECT_SPEED_Y;
		SetState(EFFECT_STATE_APPEAR);
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void RenderChangeScreenEffect();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	int GetType() { return type; }
	int GetEffect() { return effect; }
};