#include "Goomba.h"
#include "debug.h"

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (dead)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMonster::OnCollisionWith(e); // use general collision for monster
}

void CGoomba::Render()
{
	if (!IsInCamera()) return; // lazy load

	int aniId = -1; // default animation

	switch (state)
	{
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case MONSTER_STATE_DIE:
		aniId = ID_ANI_GOOMBA_DIE;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CGoomba::Render\n", state);
		break;
	}

	if (aniId == -1) return;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CGoomba::SetState(int state)
{
	// use general state for monster
	CMonster::SetState(state);

	// specific state for goomba
	switch (state)
	{
	case MONSTER_STATE_DIE:
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2; // adjust position
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CGoomba::SetState\n", state);
		break;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!IsInCamera()) return;
	if (RemoveWhenMoveToDangerousSpace()) return;
	CMonster::Update(dt, co_objects);
}