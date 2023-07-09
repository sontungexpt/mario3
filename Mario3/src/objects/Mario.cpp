﻿#include <algorithm>
#include "debug.h"

#include "components/Collision/Collision.h"
#include "scenes/PlayScene.h"

#include "Mario.h"
#include "MarioAttackingZone.h"
#include "Game.h"
#include "Platform.h"

#include "monsters/Goomba.h"
#include "monsters/plants/Plant.h"
#include "monsters/Koopa.h"

#include "items/Bullet.h"
#include "items/Coin.h"
#include "items/Mushroom.h"

#include "materials/Portal.h"
#include "materials/Door.h"
#include "materials/EffectManager.h"
#include "materials/bricks/BreakableBrick.h"
#include "materials/bricks/QuestionBrick.h"

#include "configs/monsters/Gommba600000.h"
#include "configs/materials/QuestionBrick100000.h"
#include "configs/core/SceneIds.h"

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	// monster
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);

	// items
	else if (dynamic_cast<CItem*>(e->obj))
		OnCollisionWithItem(e);

	// materials
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CBreakableBrick*>(e->obj))
		OnCollisionWithBreakableBrick(e);
	else if (dynamic_cast<CEnterablePipe*>(e->obj))
		OnCollisionWithEnterablePipe(e);

	// collide in y dimension and the object is a blocking object like platform
	if (e->IsCollidedInYDimension() && e->obj->IsBlocking())
	{
		if (e->IsCollidedFromTop())
		{
			is_on_platform = TRUE;
		}
		vy = 0;
	}
	if (e->IsCollidedInXDimension() && e->obj->IsBlocking())
	{
		vx = 0;
	}
}

// collision with monster
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (!koopa->IsDefend())
	{
		if (e->IsCollidedFromTop())
		{
			CEffectManager::Gennerate(koopa, POINT_100);
			CGameData::GetInstance()->IncreasePointBy(100);

			koopa->Defend();
			JumpDeflect();
		}
		else
		{
			Die();
		}
		return;
	}

	// koopa is defend
	// koopa is kicked by mario then it can kill any thing
	// on the road include mario and another monster
	// exclude that mario is collide on top koopa
	if (koopa->IsMarioKicked())
	{
		if (e->IsCollidedFromTop())
		{
			CEffectManager::Gennerate(koopa, POINT_100);
			CGameData::GetInstance()->IncreasePointBy(100);

			JumpDeflect();
			return;
		}
		Die();
		return;
	}

	// is not kicked, check if mario is want to hold koopa
	if (!is_sitting && is_want_holding_koopa)
	{
		weapon_monster = koopa;
		((CKoopa*)weapon_monster)->BeHold();
		return;
	}

	koopa->BeKick();
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	Die();
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit
	if (e->IsCollidedFromTop())
	{
		if (!goomba->IsDead())
		{
			CEffectManager::Gennerate(goomba, POINT_100);
			CGameData::GetInstance()->IncreasePointBy(100);

			goomba->Die();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (!goomba->IsDead())
		{
			this->Die();
		}
	}
}

// collision with items
void CMario::OnCollisionWithItem(LPCOLLISIONEVENT e)
{
	CItem* item = dynamic_cast<CItem*>(e->obj);

	item->BeCollected();
}

// collision with materials
void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (questionBrick->GetIsUnbox()) return; // if question brick is unbox, return immediately

	// not unbox, check collision
	if (e->IsCollidedFromBottom())
	{
		questionBrick->Bounce();
	}
}

void CMario::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
	if (e->IsCollidedFromBottom())
	{
		CBreakableBrick* breakable_brick = dynamic_cast<CBreakableBrick*>(e->obj);
		breakable_brick->Bounce();
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* portal = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(portal->GetSceneId());
}

void CMario::OnCollisionWithEnterablePipe(LPCOLLISIONEVENT e)
{
	LPENTERABLE_PIPE pipe_obj = dynamic_cast<LPENTERABLE_PIPE>(e->obj);
	if (pipe_obj->GetDirection() == PIPE_DIRECTION_DOWN)
	{
		if (e->IsCollidedFromBottom())
		{
			start_y = y;
			pipe = pipe_obj;
		}
	}
	else if (pipe_obj->GetDirection() == PIPE_DIRECTION_UP)
	{
		if (e->IsCollidedFromTop())
		{
			start_y = y;
			pipe = pipe_obj;
		}
	}
}

int CMario::GetAniIdWinScene()
{
	int aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	if (!is_on_platform)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
	}
	else
	{
		if (vx > 0)
			aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		else if (vx < 0)
			aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
	}

	return aniId;
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!is_on_platform)
	{
		if (fabs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (is_sitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (weapon_monster && ((CKoopa*)weapon_monster)->IsMarioHolding())
						aniId = ID_ANI_MARIO_SMALL_HOLDING_RUNNING_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (weapon_monster && ((CKoopa*)weapon_monster)->IsMarioHolding())
						aniId = ID_ANI_MARIO_SMALL_HOLDING_RUNNING_LEFT;
					else
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)

					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdWhenAppearanceChanging()
{
	int aniId = -1;
	if (!is_on_platform)
	{
		if (fabs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_APPEARANCE_CHANGING_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_APPEARANCE_CHANGING_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_APPEARANCE_CHANGING_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_APPEARANCE_CHANGING_LEFT;
		}
	}
	else
	{
		if (is_sitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_APPEARANCE_CHANGING_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_APPEARANCE_CHANGING_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_APPEARANCE_CHANGING_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_APPEARANCE_CHANGING_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_APPEARANCE_CHANGING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_APPEARANCE_CHANGING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_APPEARANCE_CHANGING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_APPEARANCE_CHANGING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_APPEARANCE_CHANGING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_APPEARANCE_CHANGING_LEFT;
			}
		}
	}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_APPEARANCE_CHANGING_RIGHT;

	return aniId;
}

int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!is_on_platform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (is_sitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (weapon_monster && ((CKoopa*)weapon_monster)->IsMarioHolding())
						aniId = ID_ANI_MARIO_HOLDING_RUNNING_RIGHT;
					else
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)

					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (weapon_monster && ((CKoopa*)weapon_monster)->IsMarioHolding())
						aniId = ID_ANI_MARIO_HOLDING_RUNNING_LEFT;
					else
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) {
		aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;

	if (!is_on_platform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)

				aniId = ID_ANI_TAIL_MARIO_FLY_RIGHT;
			else
				aniId = ID_ANI_TAIL_MARIO_FLY_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_TAIL_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_TAIL_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
	{
		if (is_sitting)
		{
			if (nx > 0)
				aniId = ID_ANI_TAIL_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_TAIL_MARIO_SIT_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_TAIL_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_TAIL_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_TAIL_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_TAIL_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_TAIL_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_TAIL_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_TAIL_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_TAIL_MARIO_WALKING_LEFT;
			}
		}
	}

	if (aniId == -1) {
		aniId = ID_ANI_TAIL_MARIO_IDLE_RIGHT;
	}
	return aniId;
}

int CMario::GetAniIdEnterOuterPipe()
{
	if (level == MARIO_LEVEL_TAIL_SUIT)
		return ID_ANI_MARIO_TAIL_FORWARD;
	else if (level == MARIO_LEVEL_SMALL)
		return ID_ANI_MARIO_SMALL_FORWARD;
	else if (level == MARIO_LEVEL_BIG)
		return ID_ANI_MARIO_BIG_FORWARD;
	return -1;
}

void CMario::Render()
{
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (state == MARIO_STATE_ENTER_PIPE || state == MARIO_STATE_OUTER_PIPE)
		aniId = GetAniIdEnterOuterPipe();
	else if (state == MARIO_STATE_WIN_SCENE)
		aniId = GetAniIdWinScene();
	else if (is_appearance_changing)
		aniId = GetAniIdWhenAppearanceChanging();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL_SUIT)
		aniId = GetAniIdTail();

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);
	if (ani != nullptr)
		ani->Render(x, y);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// time out -> die
	if (CGameData::GetInstance()->GetRemainTime() <= 0)
	{
		SetState(MARIO_STATE_DIE);
	}

	// jump to hole -> die
	if (y >= ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMaxObjectY()->GetY())
	{
		SetState(MARIO_STATE_DIE);
	}

	vy += ay * dt;
	vx += ax * dt;

	if (IsWinScene())
	{
		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}

	if (IsDead() || IsEnteringPipe() || IsOuteringPipe())
	{
		x += vx * dt;
		y += vy * dt;

		if (IsDead())
		{
			pipe = nullptr;
			return;
		}
		else if (dynamic_cast<LPENTERABLE_PIPE>(pipe))
		{
			if (pipe->GetDirection() == PIPE_DIRECTION_UP)
			{
				if (GetTop() > pipe->GetTop())
				{
					y = pipe->GetTop() + GetHeight() / 2 + 1;
					vy = 0;
					((LPENTERABLE_PIPE)pipe)->PlayerEntered();
				}
			}
			else if (pipe->GetDirection() == PIPE_DIRECTION_DOWN)
			{
				if (GetBottom() < pipe->GetBottom())
				{
					y = pipe->GetBottom() - GetHeight() / 2 - 1;
					vy = 0;
					((LPENTERABLE_PIPE)pipe)->PlayerEntered();
				}
			}
		}
		else if (dynamic_cast<LPOUTERABLE_PIPE>(pipe))
		{
			if (pipe->GetDirection() == PIPE_DIRECTION_UP)
			{
				if (GetBottom() < pipe->GetTop())
				{
					vy = 0;
					((LPOUTERABLE_PIPE)pipe)->PlayerMovedOut();
					if (pipe->GetPlant())
						pipe->GetPlant()->SetDisabledUpDown(FALSE);
					pipe = nullptr;
					StartUntouchable();
				}
			}
			else if (pipe->GetDirection() == PIPE_DIRECTION_DOWN)
			{
				if (GetTop() > pipe->GetBottom())
				{
					vy = 0;
					((LPOUTERABLE_PIPE)pipe)->PlayerMovedOut();
					if (pipe->GetPlant())
						pipe->GetPlant()->SetDisabledUpDown(FALSE);
					pipe = nullptr;
					StartUntouchable();
				}
			}
		}
		return;
	}

	// if is not entering pipe
	// if mario is out of enter pipe position, set pipe to null
	if (dynamic_cast<LPENTERABLE_PIPE>(pipe))
	{
		if (GetLeft() < pipe->GetLeft() || GetRight() > pipe->GetRight())
			pipe = nullptr;
		if (fabs(y - start_y) > ERROR_DISTANCE_ENTER_PIPE)
			pipe = nullptr;
	}

	if (weapon_monster && !is_want_holding_koopa)
	{
		CKoopa* koopa = (CKoopa*)weapon_monster;
		if (koopa->IsDefend() && !IsDead())
			koopa->BeKick();
		weapon_monster = nullptr;
	}

	// cannot exceed the allowed speed
	if (fabs(vx) > fabs(max_vx))
		vx = max_vx;
	//if (is_flying && fabs(vy) > fabs(max_vy))
	//	vy = max_vy;

	UpdatePower();

	ResetPositionIfOutOfWidthScreen(x, y);

	// reset untouchable timer if untouchable time has passed
	if (untouchable && GetTickCount64() - time_untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		time_untouchable_start = 0;
		untouchable = FALSE;
		is_appearance_changing = FALSE;
	}

	is_on_platform = FALSE;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed!
	if (IsWinScene()) return;

	if (IsDead()) return;

	// cannot change state when entering pipe or outering pipe
	if (IsEnteringPipe() || IsOuteringPipe()) return;

	switch (state)
	{
	case MARIO_STATE_ENTER_PIPE:
		// can not enter pipe if not touching pipe
		if (!dynamic_cast<LPENTERABLE_PIPE>(pipe)) return;
		if (pipe->GetPlant())
			pipe->GetPlant()->SetDisabledUpDown(TRUE);
		x = pipe->GetX();
		if (pipe->GetDirection() == PIPE_DIRECTION_UP)
			vy = MARIO_ENTER_PIPE_SPEED;
		else if (pipe->GetDirection() == PIPE_DIRECTION_DOWN)
			vy = -MARIO_ENTER_PIPE_SPEED;
		vx = 0;
		ay = 0;
		ax = 0;
		break;
	case MARIO_STATE_OUTER_PIPE:
		if (!dynamic_cast<LPOUTERABLE_PIPE>(pipe)) return;
		if (pipe->GetPlant())
			pipe->GetPlant()->SetDisabledUpDown(TRUE);
		x = pipe->GetX();
		if (pipe->GetDirection() == PIPE_DIRECTION_UP)
		{
			y = pipe->GetTop() + GetHeight() / 2 + 1;
			vy = -MARIO_ENTER_PIPE_SPEED;
		}
		else if (pipe->GetDirection() == PIPE_DIRECTION_DOWN)
		{
			y = pipe->GetBottom() - GetHeight() / 2 - 1;
			vy = MARIO_ENTER_PIPE_SPEED;
		}
		vx = 0;
		ay = 0;
		ax = 0;
		break;
	case MARIO_STATE_UNTOUCHABLE:
		untouchable = TRUE;
		time_untouchable_start = GetTickCount64();
		SetState(MARIO_STATE_IDLE);
		break;
	case MARIO_STATE_FLY:
		if (is_sitting) break;
		if (IsFullPower() && HasTail())
		{
			is_flying = TRUE;
			max_vx = MARIO_RUNNING_SPEED;
			max_vy = MARIO_FLYING_SPEED;
			vy -= MARIO_JUMP_SPEED_Y / 3 * 2.3f;
		}
	case MARIO_STATE_FLY_RELEASE:
		if (is_sitting) break;
		if (IsFullPower() && HasTail())
		{
		}
	case MARIO_STATE_RUNNING_RIGHT:
		if (is_sitting) break;
		max_vx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (is_sitting) break;
		max_vx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (is_sitting) break;
		max_vx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (is_sitting) break;
		max_vx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (is_sitting) break;
		if (is_on_platform)
		{
			if (abs(vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (is_on_platform) return;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;
	case MARIO_STATE_SIT:
		if (is_on_platform && level != MARIO_LEVEL_SMALL)
		{
			is_sitting = TRUE;
			vy = 0;
			y += MARIO_SIT_HEIGHT_ADJUST;
			SetState(MARIO_STATE_IDLE);
		}
		break;
	case MARIO_STATE_SIT_RELEASE:
		if (is_sitting)
		{
			is_sitting = FALSE;
			vy = 0;
			y -= MARIO_SIT_HEIGHT_ADJUST;
			SetState(MARIO_STATE_IDLE);
		}
		break;
	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_WIN_SCENE:
	{
		ax = 0;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		vy = 0;
		CGameData* data = CGameData::GetInstance();
		data->SetMaxDoorLevelPassed(data->GetEntryDoorLevel());
		CGame::GetInstance()->InitiateSwitchScene(ID_LEVEL_MAP_SCENE);
	}
	break;
	case MARIO_STATE_DIE:
	{
		ax = 0;
		vx = 0;
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		CGameData* data = CGameData::GetInstance();
		data->DecreaseLifeBy1();
		data->SetIsLostALife(TRUE);
		data->SetMarioLevel(MARIO_LEVEL_SMALL);
		CGame::GetInstance()->InitiateSwitchScene(ID_LEVEL_MAP_SCENE);
	}
	break;
	}
	CGameObject::SetState(state);
}

void CMario::Die()
{
	// cannot die when entering pipe
	if (IsWinScene() || IsEnteringPipe() || IsOuteringPipe()) return;

	// not untouchable -> can die
	if (!untouchable)
	{
		if (HasTail())
		{
			CutTail();
			return;
		}

		if (IsBig())
		{
			Shrink();
			return;
		}
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::GetBoundingBoxBig(float& left, float& top, float& right, float& bottom)
{
	if (is_sitting)
	{
		left = x - MARIO_BIG_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
	}
	else
	{
		left = x - MARIO_BIG_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
}

void CMario::GetBoundingBoxTail(float& left, float& top, float& right, float& bottom)
{
	if (nx >= 0)
	{
		if (is_sitting)
		{
			left = x + MARIO_BIG_TAIL_SUIT_BBOX_WIDTH / 2 - MARIO_BIG_BBOX_WIDTH;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x + MARIO_BIG_TAIL_SUIT_BBOX_WIDTH / 2 - MARIO_BIG_BBOX_WIDTH;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		if (is_sitting)
		{
			left = x - MARIO_BIG_TAIL_SUIT_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_TAIL_SUIT_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
}

void CMario::GetBoundingBoxSmall(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_SMALL_BBOX_WIDTH / 2;
	top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
	right = left + MARIO_SMALL_BBOX_WIDTH;
	bottom = top + MARIO_SMALL_BBOX_HEIGHT;
}

void CMario::UpdatePower()
{
	if (is_flying && GetTickCount64() - time_fly_start > MARIO_POWER_DURATION_FLY)
	{
		power = 0;
		time_fly_start = 0;
		is_flying = FALSE;
		return;
	}

	if (is_power_upping)
	{
		power = static_cast<int>(min((float)MARIO_MAX_POWER, fabs(vx) / MARIO_RUNNING_SPEED * (float)MARIO_MAX_POWER));
		// this line same with bottom

		//float ratio = vx / MARIO_RUNNING_SPEED;
		//if (ratio >= 1.0f)
		//{
		//	power = MARIO_MAX_POWER;
		//}
		//else if (ratio > 0.0f)
		//{
		//	// if the ratio is less than 1 but greater than 0,
		//	// calculate power based on the ratio and set it to a value between 0 and 5
		//	power = static_cast<int>(ratio * (float)MARIO_MAX_POWER);
		//}
		//else
		//{
		//	power = 0; // if the ratio is 0, set power to 0
		//}
	}
	else
	{
		if (GetTickCount64() - time_power_up_start > MARIO_TIME_OUT_POWER_UP)
		{
			power = power > 0 ? power - 1 : 0;
			time_power_up_start = power > 0 ? GetTickCount64() : 0;
		}
	}
	is_power_upping = FALSE;
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	// if mario is changing appearance, use the big bbox
	if (is_appearance_changing)
	{
		if (level == MARIO_LEVEL_TAIL_SUIT)
		{
			GetBoundingBoxTail(left, top, right, bottom);
			return;
		}
		GetBoundingBoxBig(left, top, right, bottom);
		return;
	}

	if (level == MARIO_LEVEL_TAIL_SUIT)
		GetBoundingBoxTail(left, top, right, bottom);
	else if (level == MARIO_LEVEL_BIG)
		GetBoundingBoxBig(left, top, right, bottom);
	else
		GetBoundingBoxSmall(left, top, right, bottom);
}

void CMario::SetLevel(int level)
{
	if (this->level == level) return; // nothing to change

	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2 + 1;
	}

	/*if (level == MARIO_LEVEL_TAIL_SUIT)
	{
		if (!attacking_zone)
		{
			LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
			float width_zone = MARIO_BIG_TAIL_SUIT_BBOX_WIDTH - MARIO_BIG_BBOX_WIDTH;

			attacking_zone = (CMarioAttackingZone*)scene->AddObject(
				new CMarioAttackingZone(GetRight() + width_zone / 2, y, width_zone, MARIO_BIG_BBOX_HEIGHT));
		}
	}*/
	/*else
	{
		if (attacking_zone)
		{
			attacking_zone->Delete();
			attacking_zone = nullptr;
		}
	}*/

	is_appearance_changing = TRUE;
	StartUntouchable();
	this->level = level;
	CGameData::GetInstance()->SetMarioLevel(level);
}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}