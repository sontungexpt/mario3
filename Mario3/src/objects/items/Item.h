#pragma once
#include "debug.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "objects/GameObject.h"
#include "configs/items/Mushroom301000.h"

class CItem : public CGameObject
{
protected:
	BOOLEAN is_collected;

	virtual void OnCollisionWithPlayer(LPCOLLISIONEVENT e) = 0;

public:

	CItem(float x, float y, int state)
		:CItem(x, y, 0, 0, 0, GRAVITY, -1, -1, state, 1, 0) {}

	CItem(float x, float y, float ay, int state)
		:CItem(x, y, 0, 0, 0, ay, -1, -1, state, 1, 0) {}

	CItem(float x = 0, float y = 0, float vx = 0, float vy = 0,
		float ax = 0, float ay = GRAVITY, float max_vx = -1, float max_vy = -1,
		int state = UNKNOWN_STATE, int is_collidable = 1, int is_blocking = 0)
		: CGameObject(x, y, vx, vy, ax, ay, max_vx, max_vy, state, is_collidable, is_blocking),
		is_collected(FALSE)
	{}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	BOOLEAN IsItem() { return TRUE; };
	BOOLEAN IsCollected() { return is_collected; };
	void SetIsCollected(BOOLEAN is_collected) { this->is_collected = is_collected; };
	virtual void BeCollected() { is_collected = TRUE; };
};
