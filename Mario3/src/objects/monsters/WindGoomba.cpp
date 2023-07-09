#include "WindGoomba.h"
#include "debug.h"
#include "objects/items/Item.h"
#include "objects/Platform.h"

void CWindGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (state)
	{
	case MONSTER_STATE_FLY_LEFT:
	case MONSTER_STATE_FLY_RIGHT:
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
	if (!IsInCamera()) return;

	switch (state)
	{
	case MONSTER_STATE_FLY_LEFT:
	case MONSTER_STATE_FLY_RIGHT:
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
	case MONSTER_STATE_FLY_LEFT:
		time_jump_start = GetTickCount64();
		vx = -MONSTER_WALKING_SPEED;
		vy = -GOOMBA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;
	case MONSTER_STATE_FLY_RIGHT:
		time_jump_start = GetTickCount64();
		vx = MONSTER_WALKING_SPEED;
		vy = -GOOMBA_FLY_SPEED_Y;
		ay = GRAVITY;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CWindGoomba::SetState\n", state);
		break;
	}
}

void CWindGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (has_wind) // no wind no fly
	{
		if (!IsInCamera()) return;
		if (RemoveWhenMoveToDangerousSpace()) return;
		// if it fall down from platform, then it can fly again
		if (is_on_platform && GetTickCount64() - time_jump_start > GOOMBA_TIME_FOR_EACH_FLY)
		{
			if (CompareXWithMario() == 1)
				SetState(MONSTER_STATE_FLY_LEFT);
			else
				SetState(MONSTER_STATE_FLY_RIGHT);
		}
		vy += ay * dt;
		vx += ax * dt;

		is_on_platform = FALSE;
		CCollision::GetInstance()->Process(this, dt, co_objects);
		return;
	}

	CGoomba::Update(dt, co_objects);
}

void CWindGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMonster::OnCollisionWith(e);
}

void CWindGoomba::Die()
{
	if (has_wind) {
		has_wind = FALSE;

		const float fly_height_diff = (GOOMBA_BBOX_HEIGHT_FLY - GOOMBA_BBOX_HEIGHT) / 2;

		// adjust position before set state
		if (state == MONSTER_STATE_FLY_LEFT || state == MONSTER_STATE_FLY_RIGHT)
			y += fly_height_diff;

		// set state
		SetState(vx > 0 ? MONSTER_STATE_WALKING_RIGHT : MONSTER_STATE_WALKING_LEFT);

		ay = GRAVITY;
		return;
	}

	// if it has no wind, then it will die like a normal goomba
	CGoomba::Die();
}