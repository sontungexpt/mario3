#pragma once

#include "objects/GameObject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

// configs
#include "configs/items/Coin300000.h"

class CCoin : public CGameObject {
	float ax;
	float ay;

	BOOLEAN is_collected;

	float collect_y; // the axios of collect point

public:
	CCoin(float x, float y) : CGameObject(x, y) {
		ax = 0;
		ay = COIN_GRAVITY;
		is_collected = FALSE;
	}

	CCoin(float x, float y, int state) : CGameObject(x, y, state) {
		ax = 0;
		ay = COIN_GRAVITY;
		is_collected = FALSE;
	}

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	bool IsCollect() { return is_collected; }

	void Collect() {
		is_collected = TRUE;
	}

	void JumpOutQuestionBrick() { SetState(COIN_STATE_JUMP_OUT_QUESTION_BRICK); };
	void SetState(int state);
};