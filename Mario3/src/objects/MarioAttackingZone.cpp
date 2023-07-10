#include "MarioAttackingZone.h"
#include "Mario.h"

#include "monsters/Monster.h"
#include "scenes/PlayScene.h"

void CMarioAttackingZone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}

void CMarioAttackingZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioAttackingZone::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMonster*>(e->obj))
	{
		OnCollisionWithMonster(e);
	}
}
void CMarioAttackingZone::OnCollisionWithMonster(LPCOLLISIONEVENT e)
{
	LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());

	if (mario && mario->IsHitting())
	{
		CMonster* monster = dynamic_cast<CMonster*>(e->obj);
		monster->Delete();
	}
}