#include "Item.h"
#include "objects/Mario.h"
#include "objects/Platform.h"

void CItem::OnNoCollision(DWORD dt)
{
	if (is_deleted) return;
	x += vx * dt;
	y += vy * dt;
};

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (is_deleted) return;

	vx += ax * dt;
	vy += ay * dt;

	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CItem::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		// not work now because the code dirty in the update function in playscene file
		OnCollisionWithPlayer(e);
		return;
	}

	if (!e->obj->IsBlocking()) return;

	if (e->IsCollidedInYDimension())
	{
		vy = 0;
	}

	if (e->IsCollidedInXDimension())
	{
		vx = -vx;
		ax = -ax;
	}
}