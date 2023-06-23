#include "debug.h"
#include "WindKoopa.h"

void CWindKoopa::AdjustPos()
{
}

void CWindKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (is_deleted) return;
	if (!IsInCamera()) return;

	if (has_wind) // no wind no fly
	{
		// if it fall down from platform, then it can fly again
		if (is_on_platform && GetTickCount64() - time_jump_start > KOOPA_TIME_FOR_EACH_FLY)
		{
			SetState(MONSTER_STATE_FLY);
		}
	}
	is_on_platform = FALSE;

	CMonster::Update(dt, co_objects);
}

void CWindKoopa::Render()
{
	/*if (is_deleted) return;
	if (!IsInCamera()) return;

	if (state == MONSTER_STATE_FLY)
	{
		CAnimations::GetInstance()->Get(ID_ANI_KOOPA_GREEN_FLY)->Render(x, y);
		return;
	}*/

	CKoopa::Render();
}

void CWindKoopa::SetState(int state)
{
	CKoopa::SetState(state);

	switch (state)
	{
	case MONSTER_STATE_FLY:
		time_jump_start = GetTickCount64();
		vx = CompareXWithMario() == 1 ? -fabs(vx) : fabs(vx);
		vy = -KOOPA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;

	default:
		DebugOut(L"[ERROR] Unhandled monster state %d\n in Function CGoomba Set State", state);
		break;
	}
}

void CWindKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == MONSTER_STATE_FLY)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_FLY / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_FLY;
		return;
	}

	CKoopa::GetBoundingBox(left, top, right, bottom);
}

void CWindKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CKoopa::OnCollisionWith(e);
}

void CWindKoopa::Defend()
{
	if (has_wind) {
		has_wind = FALSE;
		if (vx > 0)
			SetState(MONSTER_STATE_WALKING_RIGHT);
		else
			SetState(MONSTER_STATE_WALKING_LEFT);
		ay = GRAVITY;

		y -= (KOOPA_BBOX_HEIGHT_FLY - KOOPA_BBOX_HEIGHT) / 2;
		return;
	}
	CKoopa::Defend();
}