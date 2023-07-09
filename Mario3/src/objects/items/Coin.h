#pragma once

#include "objects/GameObject.h"
#include "Item.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

// configs
#include "configs/items/Coin300000.h"

class CCoin : public CItem {
	float collect_y; // y when being collected

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e) {};

public:
	CCoin(float x = 0, float y = 0, int state = UNKNOWN_STATE)
		:CItem(x, y, 0, state) {}

	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void JumpOutQuestionBrick() { SetState(COIN_STATE_JUMP_OUT_QUESTION_BRICK); };
	void SetState(int state);

	void BeCollected();
};