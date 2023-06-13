#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "components/Sprite/Sprites.h"
#include "components/Collision/Collision.h"

using namespace std;

class CGameObject
{
private:

protected:

	float x;
	float y;

	int state;

	float vx;
	float vy;

	int nx;

	bool isDeleted;

	virtual void ResetPositionIfOutOfScreen(float& curr_x, float& curr_y);

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	float GetWidth();
	float GetHeight();

	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }

	void RenderBoundingBox();
	BOOLEAN IsInCamera(); // use for lazy load

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;

	// call this function when you want to change object's state
	virtual void SetState(int state) { this->state = state; };

	// Collision ON or OFF ? This can change depending on object's state. For example: die
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }
};
