#pragma once
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "debug.h"

#include "configs/items/Mushroom301000.h"
#include "objects/GameObject.h"

class CItem : public CGameObject
{
protected:
	BOOLEAN is_collected;

	// because in the future, we will have many features for item type
	// so we need to have a function to handle it
	// if we move this to mario, we will have to check for each item type and
	// i think it's not good
	// but now it not work because dirty code in update function in playscene file
	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e) = 0;

	void Init() {
		ax = 0;
		ay = GRAVITY;
		is_collected = FALSE;
	}
public:
	CItem() :CGameObject() {
		Init();
	};

	CItem(float x, float y) :CGameObject(x, y) {
		Init();
	};

	CItem(float x, float y, int state) :CGameObject(x, y, state) {
		Init();
	};

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	BOOLEAN IsItem() { return TRUE; };
	BOOLEAN IsCollected() { return is_collected; };
	void SetIsCollected(BOOLEAN is_collected) { this->is_collected = is_collected; };
	virtual void BeCollect() { is_collected = TRUE; };
};
