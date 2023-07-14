#include "Goomba.h"
#include "debug.h"
#include "scenes/PlayScene.h"
#include <GameData.h>

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

//void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	CMonster::OnCollisionWith(e); // use general collision for monster
//}

void CGoomba::Render()
{
	if (!IsInCamera()) return; // lazy load
	if (is_deleted) return;

	int aniId = -1; // default animation

	switch (state)
	{
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case MONSTER_STATE_BE_HITTED:
		aniId = ID_ANI_GOOMBA_BE_HIT;
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
	case GOOMBA_STATE_BE_HITTED:
		break;
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

	if (is_mario_hitted)
	{
		if (GetTickCount64() - time_hit_start > GOOMBA_DISAPPEAR_AFTER_HITTED)
			is_deleted = true;
	}
	else if (is_kicked_by_koopa)
	{
		if (GetTickCount64() - time_kick_start > GOOMBA_DISAPPEAR_AFTER_HITTED)
			is_deleted = true;
	}

	if (is_deleted) return;

	CMonster::Update(dt, co_objects);
}

void CGoomba::BeKickedByKoopa()
{
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	CGameData::GetInstance()->IncreasePointBy(100);
	SetState(MONSTER_STATE_BE_HITTED);
	is_kicked_by_koopa = TRUE;
	time_kick_start = GetTickCount64();
}

void CGoomba::BeHitByMarioTail()
{
	is_mario_hitted = TRUE;
	time_hit_start = GetTickCount64();
	SetState(MONSTER_STATE_BE_HITTED);
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	CGameData::GetInstance()->IncreasePointBy(100);
}