#include "MarioAttackingZone.h"
#include "Mario.h"
#include "scenes/PlayScene.h"

void CMarioAttackingZone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario && mario->HasTail())
	{
		float temp_left, temp_top, temp_right, temp_bottom;
		mario->GetBoundingBox(temp_left, temp_top, temp_right, temp_bottom);

		if (mario->GetNx() >= 0)
		{
			left = temp_right;
			top = temp_top;
			right = left + width;
			bottom = top + height;
		}

		else
		{
			right = temp_left;
			top = temp_top;
			left = right - width;
			bottom = top + height;
		}
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}*/

	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}

void CMarioAttackingZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario && mario->HasTail())
	{
		float temp_left, temp_top, temp_right, temp_bottom;
		mario->GetBoundingBox(temp_left, temp_top, temp_right, temp_bottom);

		if (mario->GetNx() >= 0)
		{
			x = temp_right + width / 2;
			y = mario->GetY();
		}

		else
		{
			x = temp_left - width / 2;
			y = mario->GetY();
		}
	}*/
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
	CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario && mario->HasTail())
	{
		CMonster* monster = dynamic_cast<CMonster*>(e->obj);
		monster->Delete();
	}
}