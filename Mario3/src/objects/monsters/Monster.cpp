#include "debug.h"
#include "Monster.h"

void CMonster::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMonster::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; // ignore collision with blocking object
	if (dynamic_cast<CMonster*>(e->obj)) return; // ignore collision with other monsters

	if (e->IsCollidedInYDimension())
	{
		vy = 0;
	}
	if (e->IsCollidedInXDimension())
	{
		vx = -vx;
	}
}

void CMonster::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MONSTER_STATE_DEAD:
		dead_time = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		ax = 0;
		break;
	case MONSTER_STATE_WALKING_LEFT:
		vx = -MONSTER_WALKING_SPEED;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		vx = MONSTER_WALKING_SPEED;
		break;
	default:
		break;
	}
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	//move out of screen >> delete
	if (x + GetWidth() <= 0)
	{
		dead = true;
		isDeleted = true;
		return;
	}
	// fall to to the hole >> delete
	if (y > SCREEN_HEIGHT)
	{
		dead = true;
		isDeleted = true;
		return;
	}

	// die >> delete
	if (dead && (GetTickCount64() - dead_time > disapear_time))
	{
		isDeleted = true;
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}