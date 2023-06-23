#include "Game.h"
#include "debug.h"
#include "components/Scene/Scene.h"
#include "scenes/PlayScene.h"

#include "configs/monsters/Monster.h"

#include "Koopa.h"
#include "Goomba.h"

#include "objects/Mario.h"
#include "objects/Platform.h"
#include "objects/materials/QuestionBrick.h"

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	// if the koopa is kicked by mario, then it will kill every goomba it touch
	if (is_defend && is_mario_kicked)
	{
		e->obj->Delete();
	}
}

void CKoopa::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if (!is_defend || !is_mario_kicked) return;

	// if the koopa is kicked by mario, then when it touch question brick
	// question brick will create item
	CQuestionBrick* question_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	question_brick->Bounce();
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		OnCollisionWithGoomba(e);
		return;
	}
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
	{
		OnCollisionWithQuestionBrick(e);
	}

	if (e->IsCollidedFromTop() && e->obj->IsBlocking())
	{
		CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
		if (platform)
		{
			float l, t, r, b;
			platform->GetBoundingBox(l, t, r, b);
			limit_x_negative = l;
			limit_x_positive = r;
			is_on_platform = TRUE;
		}
	}

	// this code will update vx = -vx when collide with something
	CMonster::OnCollisionWith(e);
}

void CKoopa::Reset() {
	is_defend = FALSE;
	is_comback = FALSE;
	is_mario_kicked = FALSE;
	is_mario_holding = FALSE;
	mario_speed_when_kicked = 0;
	defend_time = -1;
	comeback_time = -1;
	AdjustPos();
	SetState(MONSTER_STATE_WALKING_LEFT);
};

void CKoopa::AdjustPos() {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
		break;
	case KOOPA_STATE_COMEBACK:
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2;
		break;
	case KOOPA_STATE_IS_HOLDING:
	{
		if (mario)
		{
			if (mario->GetNx() >= 0) // mario is turn right
			{
				x = mario->GetX() + mario->GetWidth() / 2 + 1;
			}
			else {
				x = mario->GetX() - mario->GetWidth() / 2 - 1;
			}
			y = mario->GetY();
		}
	}
	break;
	default:
		break;
	}
}

void CKoopa::Render()
{
	if (!IsInCamera()) return;

	int aniId = -1;

	switch (type) {
	case KOOPA_GREEN:
		aniId = GetAniIdGreen();
		break;
	case KOOPA_RED:
		aniId = GetAniIdRed();
		break;
	default:
		DebugOut(L"[ERROR] Can not handle state %d CKoopa::Render\n", state);
		return;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

int CKoopa::GetAniIdRed()
{
	int aniId = -1;

	switch (state) {
	case KOOPA_STATE_COMEBACK:
		aniId = ID_ANI_KOOPA_RED_COMEBACK;
		break;
	case KOOPA_STATE_DEFEND:
		aniId = ID_ANI_KOOPA_RED_DEFEND;
		break;
	case KOOPA_STATE_IS_HOLDING:
		aniId = ID_ANI_KOOPA_RED_DEFEND;
		break;
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
		break;
	case KOOPA_STATE_IS_KICKED:
		aniId = ID_ANI_KOOPA_RED_IS_KICKED;
		break;
	default:
		DebugOut(L"[ERROR] Can not handle state %d CKoopa::Render\n", state);
		break;
	}

	return aniId;
}

int CKoopa::GetAniIdGreen()
{
	int aniId = -1;

	switch (state) {
	case KOOPA_STATE_COMEBACK:
		aniId = ID_ANI_KOOPA_GREEN_COMEBACK;
		break;
	case KOOPA_STATE_DEFEND:
		aniId = ID_ANI_KOOPA_GREEN_DEFEND;
		break;
	case KOOPA_STATE_IS_HOLDING:
		aniId = ID_ANI_KOOPA_GREEN_DEFEND;
		break;
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_KOOPA_GREEN_WALKING_LEFT;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
		break;
	case KOOPA_STATE_IS_KICKED:
		aniId = ID_ANI_KOOPA_GREEN_IS_KICKED;
		break;
	default:
		break;
	}

	return aniId;
}

void CKoopa::SetState(int state)
{
	CMonster::SetState(state);

	// this line handle the different state for each monster
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		is_defend = TRUE;
		defend_time = GetTickCount64();
		AdjustPos();
		SetIdle();
		break;
	case KOOPA_STATE_IS_KICKED:
	{
		is_mario_holding = FALSE;
		is_mario_kicked = TRUE;
		// defend again
		is_defend = TRUE;
		is_comback = FALSE;

		// if vx > 0, then mario kick it to right
		// if vx < 0, then mario kick it to left
		vx = mario_speed_when_kicked;
		// Get mario
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = (CMario*)scene->GetPlayer();

		ax = mario->GetNx() >= 0 ? KOOPA_SLIDING_ACCELERATION : -KOOPA_SLIDING_ACCELERATION;
	}
	break;
	case KOOPA_STATE_COMEBACK:
		comeback_time = GetTickCount64();
		is_comback = TRUE;
		SetIdle();
		break;
	case KOOPA_STATE_IS_HOLDING:
		if (is_defend && !is_mario_kicked)
		{
			SetIdle();
			is_mario_holding = TRUE;
		}
		break;
	}
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (is_deleted) return;

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
	if (!is_mario_kicked && is_defend &&
		GetTickCount64() - defend_time > KOOPA_DEFEND_TIMEOUT
		)
	{
		if (!is_comback)
		{
			// start comback
			// still in defend and try to comeback
			CombackAfterDefend();
		}
		else
		{
			// completely combeack
			if (GetTickCount64() - comeback_time > KOOPA_COMBACK_TIMEOUT)
				Reset();
		}
	}

	if (!is_defend && is_on_platform)
	{
		// this part is make sure koopa only move on platform until be kicked
		if (x <= limit_x_negative)
			SetState(MONSTER_STATE_WALKING_RIGHT);
		if (x >= limit_x_positive)
			SetState(MONSTER_STATE_WALKING_LEFT);
	}

	is_on_platform = FALSE;

	if (is_mario_holding) {
		AdjustPos();
		return;
	}

	CMonster::Update(dt, co_objects);
}