#include "Item.h"
#include "objects/Mario.h"
#include "objects/Platform.h"

void CItem::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	vx += ax * dt;
	vy += ay * dt;

	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CItem::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		OnCollisionWithPlayer(e);
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