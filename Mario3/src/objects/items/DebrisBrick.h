#pragma once
#include "Item.h"
#include "configs/materials/BreakableBrick102000.h"

class CDebrisBrick : public CItem
{
private:
	ULONGLONG time_splasing_start = 0;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e) {};
	void SetState(int state);

public:

	CDebrisBrick() :CItem() { SetState(DEBRIS_BRICK_STATE_SPLASHING); };

	CDebrisBrick(float x, float y) : CItem(x, y) {
		SetState(DEBRIS_BRICK_STATE_SPLASHING);
	};

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	// action
	void Splash() { SetState(DEBRIS_BRICK_STATE_SPLASHING); }
};