#include "Item.h"
#include "objects/Mario.h"
#include "objects/Platform.h"

void CItem::OnNoCollision(DWORD dt)
{
	if (isDeleted) return;
	x += vx * dt;
	y += vy * dt;
};

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (isDeleted) return;

	if (!IsInCamera()) return;

	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, co_objects);
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

	if (e->IsCollidedInXDimension())
	{
		vx = -vx;
		ax = -ax;
	}
}