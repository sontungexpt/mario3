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
	if (!is_defend) return;
	if (!is_mario_kicked) return;
	CQuestionBrick* question_brick = dynamic_cast<CQuestionBrick*>(e->obj);
	// if the koopa is kicked by mario, then when it touch question brick
	// question brick will create item
	question_brick->Bounce();
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		DebugOut(L"[INFO] KOOPA::OnCollisionWithPlayer\n");
		return;
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		OnCollisionWithGoomba(e);
		return;
	}
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
	{
		// collide with question brick then it can create new item
		OnCollisionWithQuestionBrick(e);
	};

	CMonster::OnCollisionWith(e); // this code will update vx = -vx when collide with something
}

void CKoopa::Reset() {
	is_defend = FALSE;
	is_comback = FALSE;
	is_mario_kicked = FALSE;
	is_mario_holding = FALSE;
	mario_speed_when_kicked = 0;
	defend_time = -1;
	comeback_time = -1;
	ax = 0;
	AdjustY();
	SetState(MONSTER_STATE_WALKING_LEFT);
};

void CKoopa::AdjustY() {
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2 - 1;
		break;
	case KOOPA_STATE_COMEBACK:
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DEFEND) / 2 + 1;
		break;
	case KOOPA_STATE_IS_HOLDING:
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = (CMario*)scene->GetPlayer();

		if (mario)
		{
			if (mario->GetNx() >= 0) // mario is turn right
			{
				x = mario->GetX() + mario->GetWidth() / 2 + 1;
			}
			else {
				x = mario->GetX() - mario->GetWidth() / 2 - 1;
			}
		}
	}

	break;
	}
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT; // default is walking left

	switch (state) {
	case KOOPA_STATE_DEFEND:
		aniId = ID_ANI_KOOPA_DEFEND;
		break;
	case KOOPA_STATE_IS_HOLDING:
		aniId = ID_ANI_KOOPA_DEFEND;
		break;
	case MONSTER_STATE_WALKING_LEFT:
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
		break;
	case KOOPA_STATE_IS_KICKED:
		aniId = ID_ANI_KOOPA_IS_KICKED;
		break;
	case KOOPA_STATE_COMEBACK:
		aniId = ID_ANI_KOOPA_COMEBACK;
		break;
	default:
		DebugOut(L"[ERROR] Can not handle state %d, ", state);
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CKoopa::SetState(int state)
{
	// this line handle the same state for many monster
	CMonster::SetState(state);

	// this line handle the different state for each monster
	switch (state)
	{
	case KOOPA_STATE_DEFEND:
		is_defend = TRUE;
		defend_time = GetTickCount64();
		AdjustY();
		SetIdle();
		break;
	case KOOPA_STATE_IS_KICKED:
		is_mario_holding = FALSE;
		is_mario_kicked = TRUE;
		// defend again
		defend_time = GetTickCount64();
		is_defend = TRUE;
		is_comback = FALSE;

		// if vx > 0, then mario kick it to right
		// if vx < 0, then mario kick it to left
		vx = mario_speed_when_kicked;
		ax = vx > 0 ? KOOPA_SLIDING_ACCELERATION : -KOOPA_SLIDING_ACCELERATION;
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
	if ((state == MONSTER_STATE_DIE) || (state == KOOPA_STATE_DEAD_UPSIDE)) return;

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

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (!IsInCamera()) return;

	if (is_defend && GetTickCount64() - defend_time > KOOPA_DEFEND_TIMEOUT)
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
	if (is_mario_holding) {
		AdjustY();
		return;
	}
	CMonster::Update(dt, coObjects);
}