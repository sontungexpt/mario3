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
	int state;
	int is_blocking;
	int is_collidable;
	bool is_deleted;

	// x and y is the center of the object
	float x;
	float y;

	float start_x;
	float start_y;

	// moving speed
	float vx;
	float vy;

	float max_vx;
	float max_vy;

	// acceleration
	float ax;
	float ay;

	virtual void ResetPositionIfOutOfWidthScreen(float& curr_x, float& curr_y);

public:
	float GetWidth();
	float GetHeight();

	// position
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	float GetX() { return x; }
	float GetY() { return y; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }

	// this function is return the coordinateX of Ox of the sprite
	// Ox have dimension from left to right and same  with top edge
	float GetOxAtTopLeft() {
		float left, top, right, bottom;
		GetBoundingBox(left, top, right, bottom);
		return left;
	}

	// this function is return the coordinateY Oy of the sprite
	// Oy have dimension from top to bottom and same with left edge
	float GetOyAtTopRight() {
		float left, top, right, bottom;
		GetBoundingBox(left, top, right, bottom);
		return top;
	}

	// velocity
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }
	virtual void AdjustPos() {}; // adjust height when change animation render

	// delete
	virtual void Delete() { is_deleted = true; }
	bool IsDeleted() { return is_deleted; }

#pragma region CONSTRUCTOR_DESTRUCTOR
	CGameObject();
	CGameObject(float x, float y) :CGameObject()
	{
		this->x = x;
		this->y = y;
		this->start_x = x;
		this->start_y = y;
	}
	CGameObject(float x, float y, int  state) :CGameObject(x, y)
	{
		SetState(state);
	}
	CGameObject(float x, float y, float v0x, float v0y) :CGameObject(x, y)
	{
		this->vx = v0x;
		this->vy = v0y;
	}
	~CGameObject() {}

#pragma endregion
	// core
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr) {};
	void RenderBoundingBox();

	BOOLEAN IsInCamera(); // use for lazy load

	// call this function when you want to change object's state
	virtual void SetState(int state) { this->state = state; };
	int GetState() { return state; }

#pragma region COLLISION

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return is_blocking; }
	void SetIsBlocking(int is_blocking) { this->is_blocking = is_blocking; }

	// Collision ON or OFF ? This can change depending on object's state. For example: die
	void SetIsCollidable(int is_colliable) { this->is_collidable = is_colliable; }
	virtual int IsCollidable() { return is_collidable; };
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	static bool IsDeleted(const LPGAMEOBJECT& o) { return o->is_deleted; }

#pragma endregion
};