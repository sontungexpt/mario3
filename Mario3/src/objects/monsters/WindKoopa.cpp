#include "debug.h"
#include "WindKoopa.h"

void CWindKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (has_wind) // no wind no fly
	{
		// if it fall down from platform, then it can fly again
		if (RemoveWhenMoveToDangerousSpace()) return;
		if (!IsInCamera()) return;

		if (is_on_platform && GetTickCount64() - time_jump_start > KOOPA_TIME_FOR_EACH_FLY)
		{
			if (vx > 0)
				SetState(MONSTER_STATE_FLY_RIGHT);
			else
				SetState(MONSTER_STATE_FLY_LEFT);
		}

		vy += ay * dt;
		vx += ax * dt;

		is_on_platform = FALSE;
		CCollision::GetInstance()->Process(this, dt, co_objects);
		return;
	}

	CKoopa::Update(dt, co_objects);
}

int CWindKoopa::GetAniIdRed()
{
	switch (state) {
	case MONSTER_STATE_FLY_RIGHT:
		return ID_ANI_KOOPA_RED_FLY_RIGHT;
	case MONSTER_STATE_FLY_LEFT:
		return ID_ANI_KOOPA_RED_FLY_LEFT;
	}
	return CKoopa::GetAniIdRed();
}

int CWindKoopa::GetAniIdGreen()
{
	switch (state) {
	case MONSTER_STATE_FLY_RIGHT:
		return ID_ANI_KOOPA_GREEN_FLY_RIGHT;
	case MONSTER_STATE_FLY_LEFT:
		return ID_ANI_KOOPA_GREEN_FLY_LEFT;
	}
	return CKoopa::GetAniIdGreen();
}

void CWindKoopa::Render()
{
	CKoopa::Render();
}

void CWindKoopa::SetState(int state)
{
	CKoopa::SetState(state);

	switch (state)
	{
	case MONSTER_STATE_FLY_LEFT:
		time_jump_start = GetTickCount64();
		vx = -MONSTER_WALKING_SPEED;
		vy = -KOOPA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;
	case MONSTER_STATE_FLY_RIGHT:
		time_jump_start = GetTickCount64();
		vx = MONSTER_WALKING_SPEED;
		vy = -KOOPA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CWindKoopa::SetState\n", state);
		break;
	}
}

void CWindKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case MONSTER_STATE_FLY_LEFT:
	case MONSTER_STATE_FLY_RIGHT:
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

		const float fly_height_diff = (KOOPA_BBOX_HEIGHT_FLY - KOOPA_BBOX_HEIGHT) / 2.0f;

		// adjust position before set state
		if (state == MONSTER_STATE_FLY_LEFT || state == MONSTER_STATE_FLY_RIGHT)
			y += fly_height_diff;

		// set state
		SetState(vx > 0 ? MONSTER_STATE_WALKING_RIGHT : MONSTER_STATE_WALKING_LEFT);

		ay = GRAVITY;
		return;
	}

	// if it has no wind, then it will be a normal koopa
	CKoopa::Defend();
}

void CWindKoopa::BeKickedByKoopa()
{
	has_wind = FALSE;
	CKoopa::BeKickedByKoopa();
}

void CWindKoopa::BeHitByMarioTail()
{
	has_wind = FALSE;
	CKoopa::BeHitByMarioTail();
}