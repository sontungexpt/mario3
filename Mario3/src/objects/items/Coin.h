#pragma once

#include "objects/GameObject.h"
#include "Item.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

// configs
#include "configs/items/Coin300000.h"

class CCoin : public CItem {
	float collect_y; // the axios of collect point

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e) {};
public:
	CCoin() : CItem() {
		ax = 0;
		ay = COIN_GRAVITY;
	}
	CCoin(float x, float y) : CItem(x, y) {
		ax = 0;
		ay = COIN_GRAVITY;
	}

	CCoin(float x, float y, int state) : CItem(x, y, state) {
		ax = 0;
		ay = COIN_GRAVITY;
	}

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void JumpOutQuestionBrick() { SetState(COIN_STATE_JUMP_OUT_QUESTION_BRICK); };
	void SetState(int state);
};