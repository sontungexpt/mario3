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
protected:
	int is_blocking = 1;
	int is_collidable = 0;

	float x;
	float y;

	int state;

	// this part need to be refactor
	float vx;
	float vy;
	// end refactor

	int nx;

	bool isDeleted;

	virtual void ResetPositionIfOutOfScreen(float& curr_x, float& curr_y);

public:
	float GetWidth();
	float GetHeight();

	// position
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetXAtTopLeft() { return x - GetWidth() / 2; }
	float GetYAtTopRight() { return y - GetHeight() / 2; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }

	// velocity
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }

	// delete
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }

	// constructor & destructor
	CGameObject();
	CGameObject(float x, float y) :CGameObject()
	{
		this->x = x;
		this->y = y;
	}
	CGameObject(float x, float y, int  state) :CGameObject()
	{
		this->x = x;
		this->y = y;
		SetState(state);
	}
	CGameObject(float x, float y, float v0x, float v0y) :CGameObject()
	{
		this->x = x;
		this->y = y;
		this->vx = v0x;
		this->vy = v0y;
	}
	~CGameObject() {}

	// core
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	void RenderBoundingBox();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;

	BOOLEAN IsInCamera(); // use for lazy load

	// call this function when you want to change object's state
	virtual void SetState(int state) { this->state = state; };
	int GetState() { return this->state; }

	// Collision ON or OFF ? This can change depending on object's state. For example: die
	void SetIsColliable(int is_colliable) { this->is_collidable = is_colliable; }
	virtual int IsCollidable() { return is_collidable; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return is_blocking; }
	void SetIsBlocking(int is_blocking) { this->is_blocking = is_blocking; }

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->isDeleted; }
};
