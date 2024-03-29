﻿#include "Game.h"
#include "debug.h"
#include "components/Scene/Scene.h"
#include "scenes/PlayScene.h"

#include "configs/monsters/Monster.h"

#include "Koopa.h"
#include "Goomba.h"

#include "objects/Mario.h"
#include "objects/Platform.h"
#include "objects/materials/bricks/QuestionBrick.h"
#include "objects/materials/bricks/BreakableBrick.h"

void CKoopa::OnCollisionWithMonster(LPCOLLISIONEVENT e)
{
	// if the koopa is kicked by mario, then it will kill every goomba it touch
	if (is_defend && is_mario_kicked)
	{
		CMonster* monster = dynamic_cast<CMonster*>(e->obj);
		monster->BeKickedByKoopa();
		return;
	}
	CMonster::OnCollisionWithMonster(e);
}

void CKoopa::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	if (!is_defend || !is_mario_kicked) return;

	// if the koopa is kicked by mario, then when it touch question brick
	// question brick will create item
	CBreakableBrick* breakable_brick = dynamic_cast<CBreakableBrick*>(e->obj);
	breakable_brick->Break();
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if (!is_defend || !is_mario_kicked) return;

	// if the koopa is kicked by mario, then when it touch question brick
	// question brick will create item
	CQuestionBrick* question_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	question_brick->Bounce();
}

void CKoopa::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	if (mario->IsHitting() && e->IsCollidedInXDimension())
	{
		BeHitByMarioTail();
		return;
	}

	if (!is_defend && !is_mario_holding && !e->IsCollidedFromBottom())
		mario->Die();
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CQuestionBrick*>(e->obj))
	{
		OnCollisionWithQuestionBrick(e);
	}

	if (dynamic_cast<CBreakableBrick*>(e->obj))
	{
		OnCollisionWithBreakableBrick(e);
	}

	if (e->IsCollidedFromTop() && e->obj->IsBlocking())
	{
		if (dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CBrick*>(e->obj))
		{
			float l, t, r, b;
			e->obj->GetBoundingBox(l, t, r, b);
			limit_x_negative = l;
			limit_x_positive = r;
			is_on_platform = TRUE;
		}
		if ((is_kicked_by_koopa || is_mario_hitted) && is_defend && !is_mario_kicked)
		{
			vx = 0;
		}
	}

	// this code will update vx = -vx when collide with something
	CMonster::OnCollisionWith(e);
}

void CKoopa::Reset() {
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
	case KOOPA_STATE_COMEBACK:
		if (is_mario_holding)
		{
			LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			CMario* mario = (CMario*)scene->GetPlayer();
			x = mario->GetNx() >= 0 ? x + 3 : x - 3;
			y = mario->GetTop() - KOOPA_BBOX_HEIGHT / 2 - 3;
		}
		else
		{
			y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
		}
		break;
	default:
		break;
	}
	is_defend = FALSE;
	is_comeback = FALSE;
	is_mario_kicked = FALSE;
	is_mario_holding = FALSE;
	mario_speed_when_kicked = 0;
	defend_time_start = -1;
	comeback_time_start = -1;

	// adjust position after change to new state

	SetState(MONSTER_STATE_WALKING_LEFT);
};

void CKoopa::Render()
{
	if (!IsInCamera()) return;

	int aniId = -1;

	switch (color) {
	case KOOPA_GREEN:
		aniId = GetAniIdGreen();
		break;
	case KOOPA_RED:
		aniId = GetAniIdRed();
		break;
	}

	if (aniId == -1)
	{
		DebugOut(L"[ERROR] Can not handle state %d CKoopa::Render\n", aniId);
		return;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

int CKoopa::GetAniIdRed()
{
	switch (state) {
	case KOOPA_STATE_COMEBACK:
		return ID_ANI_KOOPA_RED_COMEBACK;
	case KOOPA_STATE_DEFEND:
	case KOOPA_STATE_IS_HOLDING:
		if (is_mario_hitted)
			return ID_ANI_KOOPA_RED_DEFEND_OVERTURNED;
		return ID_ANI_KOOPA_RED_DEFEND;
	case MONSTER_STATE_WALKING_LEFT:
		return ID_ANI_KOOPA_RED_WALKING_LEFT;
	case MONSTER_STATE_WALKING_RIGHT:
		return ID_ANI_KOOPA_RED_WALKING_RIGHT;
	case KOOPA_STATE_IS_KICKED:
		if (is_mario_hitted)
			return ID_ANI_KOOPA_RED_IS_KICKED_OVERTURNED;
		return ID_ANI_KOOPA_RED_IS_KICKED;
	default:
		return -1;
	}
}

int CKoopa::GetAniIdGreen()
{
	switch (state) {
	case KOOPA_STATE_COMEBACK:
		return ID_ANI_KOOPA_GREEN_COMEBACK;
	case KOOPA_STATE_DEFEND:
	case KOOPA_STATE_IS_HOLDING:
		if (is_mario_hitted)
			return ID_ANI_KOOPA_GREEN_DEFEND_OVERTURNED;
		return ID_ANI_KOOPA_GREEN_DEFEND;
	case MONSTER_STATE_WALKING_LEFT:
		return ID_ANI_KOOPA_GREEN_WALKING_LEFT;
	case MONSTER_STATE_WALKING_RIGHT:
		return ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
	case KOOPA_STATE_IS_KICKED:
		if (is_mario_hitted)
			return ID_ANI_KOOPA_GREEN_IS_KICKED_OVERTURNED;
		return ID_ANI_KOOPA_GREEN_IS_KICKED;
	default:
		return -1;
	}
}

void CKoopa::SetState(int state)
{
	// this line handle the different state for each monster
	CMonster::SetState(state);

	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		is_defend = TRUE;
		defend_time_start = GetTickCount64();
		SetIdle();
		break;
	case KOOPA_STATE_IS_KICKED:
	{
		is_comeback = FALSE;
		is_mario_holding = FALSE;
		is_mario_kicked = TRUE;
		is_defend = TRUE; // defend again if not completely comeback

		// if vx > 0, then mario kick it to right
		// if vx < 0, then mario kick it to left
		// if vx = 0, then mario kick it to the same direction

		LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
		if (mario)
		{
			vx = mario->GetVx();
			ax = mario->GetNx() >= 0 ?
				KOOPA_SLIDING_ACCELERATION :
				-KOOPA_SLIDING_ACCELERATION;
		}
	}
	break;
	case KOOPA_STATE_BẸ_JUMP_ON_AFTER_KICKED:
		is_comeback = FALSE;
		is_mario_holding = FALSE;
		is_mario_kicked = FALSE;
		is_defend = TRUE; // defend again if not completely comeback
		SetState(KOOPA_STATE_DEFEND);
		break;

	case KOOPA_STATE_COMEBACK:
		is_comeback = TRUE;
		comeback_time_start = GetTickCount64();
		SetIdle();
		break;
	case KOOPA_STATE_IS_HOLDING:
		if (is_defend && !is_mario_kicked)
		{
			is_mario_holding = TRUE;
			SetIdle();
		}
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CKoopa::SetState\n", state);
		break;
	}
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (is_defend) {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
	}
	else {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (RemoveWhenMoveToDangerousSpace()) return;
	if (!IsInCamera()) return;

	// koopa only comeback if it is not kicked by mario
	if (!is_mario_kicked && is_defend &&
		!is_mario_hitted && !is_kicked_by_koopa &&
		GetTickCount64() - defend_time_start > KOOPA_DEFEND_TIMEOUT)
	{
		if (!is_comeback)
		{
			// still in defend and try to comeback
			ComebackAfterDefend();
		}
		else
		{
			// completely comeback
			if (GetTickCount64() - comeback_time_start > KOOPA_COMBACK_TIMEOUT)
				Reset();
		}
	}

	if (is_mario_holding) {
		// adjust position of koopa when mario is holding it
		LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;

		if (mario && !mario->IsDead())
		{
			y = mario->GetY();
			x = mario->GetNx() >= 0 ?
				mario->GetRight() + GetWidth() / 2 :
				mario->GetLeft() - GetWidth() / 2;

			CCollision::GetInstance()->Process(this, dt, co_objects);
			return;
		}
	}

	if (!is_defend && is_on_platform)
	{
		// this part is make sure koopa only move on platform until be kicked
		if (is_limit_moving_space && x <= limit_x_negative)
			SetState(MONSTER_STATE_WALKING_RIGHT);
		if (is_limit_moving_space && x >= limit_x_positive)
			SetState(MONSTER_STATE_WALKING_LEFT);
	}

	if (!can_hit_again && GetTickCount64() - hit_time_start > KOOPA_HIT_TIMEOUT)
		can_hit_again = TRUE;

	is_on_platform = FALSE;

	vy += ay * dt;
	vx += ax * dt;

	if (max_vx > 0 && abs(vx) > max_vx)
	{
		vx = vx > 0 ? max_vx : -max_vx;
	}
	//if (is_on_platform && vy >= 0)
	//{
	//	vy -= ay * dt;
	//	y -= 0.600006f;
	//}

	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CKoopa::BeHold()
{
	SetState(KOOPA_STATE_IS_HOLDING);
}

void CKoopa::BeKickedByKoopa()
{
	if (!can_hit_again) return;

	if (is_kicked_by_koopa) {
		is_deleted = TRUE;
		dead = TRUE;
	}
	else
	{
		is_kicked_by_koopa = TRUE;
		SetState(KOOPA_STATE_DEFEND);
		CMonster::InitVWhenMarioHit();
	}
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	CGameData::GetInstance()->IncreasePointBy(100);
	can_hit_again = FALSE;
	hit_time_start = GetTickCount64();
}

void CKoopa::BeHitByMarioTail()
{
	if (!can_hit_again) return;
	if (is_mario_hitted) {
		is_deleted = TRUE;
		dead = TRUE;
	}
	else
	{
		is_mario_hitted = TRUE;
		SetState(KOOPA_STATE_DEFEND);
		CMonster::InitVWhenMarioHit();
	}
	CGameData::GetInstance()->IncreasePointBy(100);
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	can_hit_again = FALSE;
	hit_time_start = GetTickCount64();
}

void CKoopa::Defend()
{
	// adjust position before change to new state
	const float defend_height_diff = (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2.0f;
	if (state == MONSTER_STATE_WALKING_LEFT || state == MONSTER_STATE_WALKING_RIGHT) {
		y += defend_height_diff;
	}

	// new state
	SetState(KOOPA_STATE_DEFEND);
}