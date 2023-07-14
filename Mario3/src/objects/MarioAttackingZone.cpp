#include "MarioAttackingZone.h"
#include "Mario.h"
#include "materials/bricks/BreakableBrick.h"

#include "monsters/Monster.h"
#include "scenes/PlayScene.h"

void CMarioAttackingZone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}

void CMarioAttackingZone::OnNoCollision(DWORD dt)
{
}

void CMarioAttackingZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (is_deleted) return;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioAttackingZone::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMonster*>(e->obj))
		OnCollisionWithMonster(e);
	else if (dynamic_cast<CBreakableBrick*>(e->obj))
		OnCollisiionWithCBreakableBrick(e);
}
void CMarioAttackingZone::OnCollisionWithMonster(LPCOLLISIONEVENT e)
{
	if (is_deleted) return;

	LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());

	if (mario && mario->IsHitting())
	{
		CMonster* monster = dynamic_cast<CMonster*>(e->obj);
		monster->Delete();
	}
}

void CMarioAttackingZone::OnCollisiionWithCBreakableBrick(LPCOLLISIONEVENT e)
{
	if (is_deleted) return;

	LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());

	if (mario && mario->IsHitting())
	{
		CBreakableBrick* breakable_brick = dynamic_cast<CBreakableBrick*>(e->obj);
		breakable_brick->BeMarioHit();
	}
}