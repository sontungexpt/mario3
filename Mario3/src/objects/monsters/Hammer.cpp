#include "Hammer.h"
#include <debug.h>

void CHammer::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (vx != 0 && fabs(x - start_x) > HAMMER_MOVING_MAX_X)
	{
		x = vx > 0 ? start_x + HAMMER_MOVING_MAX_X : start_x - HAMMER_MOVING_MAX_X;
		SetState(-state);
	}

	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CHammer::Render()
{
	int aniId = -1;
	switch (state)
	{
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_HAMMER_MOVE_LEFT;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_HAMMER_MOVE_RIGHT;
		break;
	default:
		DebugOut(L"[ERROR] CHammer::Render can not handle state %d\n", state);
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);
	if (ani != nullptr)
		ani->Render(x, y);
}

void CHammer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HAMMER_BBOX_WIDTH / 2;
	top = y - HAMMER_BBOX_HEIGHT / 2;
	right = left + HAMMER_BBOX_WIDTH;
	bottom = top + HAMMER_BBOX_HEIGHT;
}