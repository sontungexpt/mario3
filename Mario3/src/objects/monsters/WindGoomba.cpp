#include "WindGoomba.h"
#include "debug.h"
#include "objects/items/Item.h"
#include "objects/Platform.h"

void CWindGoomba::AdjustPos()
{
	switch (state)
	{
	case MONSTER_STATE_WALKING_RIGHT:
	case MONSTER_STATE_WALKING_LEFT:
		y -= (GOOMBA_BBOX_HEIGHT_FLY - GOOMBA_BBOX_HEIGHT) / 2;
		break;
	default:
		break;
	}
}

void CWindGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == MONSTER_STATE_FLY)
	{
		left = x - GOOMBA_BBOX_WIDTH_FLY / 2;
		top = y - GOOMBA_BBOX_HEIGHT_FLY / 2;
		right = left + GOOMBA_BBOX_WIDTH_FLY;
		bottom = top + GOOMBA_BBOX_HEIGHT_FLY;
		return;
	}

	CGoomba::GetBoundingBox(left, top, right, bottom);
}

void CWindGoomba::Render()
{
	if (is_deleted) return;
	if (!IsInCamera()) return;

	if (state == MONSTER_STATE_FLY)
	{
		CAnimations::GetInstance()->Get(ID_ANI_GOOMBA_FLY)->Render(x, y);
		return;
	}

	CGoomba::Render();
}

void CWindGoomba::SetState(int state)
{
	CGoomba::SetState(state);

	switch (state)
	{
	case MONSTER_STATE_FLY:
		time_jump_start = GetTickCount64();
		vx = CompareXWithMario() == 1 ? -fabs(vx) : fabs(vx);
		vy = -GOOMBA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;

	default:
		DebugOut(L"[ERROR] Unhandled monster state %d\n in Function CGoomba Set State", state);
		break;
	}
}

void CWindGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (is_deleted) return;
	if (!IsInCamera()) return;

	if (has_wind) // no wind no fly
	{
		// if it fall down from platform, then it can fly again
		if (is_on_platform && GetTickCount64() - time_jump_start > GOOMBA_TIME_FOR_EACH_FLY)
		{
			SetState(MONSTER_STATE_FLY);
		}
	}
	is_on_platform = FALSE;

	CMonster::Update(dt, co_objects);
}

void CWindGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMonster::OnCollisionWith(e);
}

void CWindGoomba::Die()
{
	if (has_wind) {
		has_wind = FALSE;
		if (vx > 0)
			SetState(MONSTER_STATE_WALKING_RIGHT);
		else
			SetState(MONSTER_STATE_WALKING_LEFT);
		ay = GRAVITY;
		AdjustPos();
		return;
	}
	CGoomba::Die();
}