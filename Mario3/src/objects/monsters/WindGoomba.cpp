#include "WindGoomba.h"
#include "debug.h"

void CWindGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_FLY)
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
	if (!IsInCamera())
		return;
	if (isDeleted)
		return;

	CGoomba::Render();

	int aniId = -1;
	switch (state)
	{
	case GOOMBA_STATE_FLY:
		aniId = ID_ANI_GOOMBA_FLY;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d\n in Function CGoomba WIndGoomba Render", state);
		break;
	}

	if (aniId == -1) return;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CWindGoomba::SetState(int state)
{
	CGoomba::SetState(state);

	switch (state)
	{
	case GOOMBA_STATE_FLY:
		time_start = GetTickCount64();
		vx = CompareXWithMario() == 1 ? -fabs(vx) : fabs(vx);
		vy = -GOOMBA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;

	default:
		DebugOut(L"[ERROR] Unhandled monster state %d\n in Function CGoomba Set State", state);
		break;
	}
}

void CWindGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsInCamera())
		return;
	if (isDeleted)
		return;

	CMonster::Update(dt, coObjects);

	if (!has_wind) // no wind no fly
		return;

	// if  it fall down from platform, then it can fly again
	if (is_on_platform && GetTickCount64() - time_start > GOOMBA_TIME_FOR_EACH_FLY)
	{
		SetState(GOOMBA_STATE_FLY);
		is_on_platform = FALSE;
		return;
	}
}

void CWindGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMonster::OnCollisionWith(e);

	if (e->obj->IsBlocking())
	{
		is_on_platform = TRUE;
		ay = 0;
		vy = 0;
		return;
	}
}

void CWindGoomba::Die()
{
	if (has_wind) {
		CutWind();

		// adjust height at new state
		y -= GOOMBA_BBOX_HEIGHT_FLY - GOOMBA_BBOX_HEIGHT;
		if (vx > 0)
			SetState(MONSTER_STATE_WALKING_RIGHT);
		else
			SetState(MONSTER_STATE_WALKING_LEFT);
		return;
	}
	CGoomba::Die();
}