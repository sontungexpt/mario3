#include <algorithm>
#include "debug.h"

#include "components/Collision/Collision.h"

#include "Mario.h"
#include "Game.h"

#include "monsters/Goomba.h"
#include "monsters/Koopa.h"
#include "monsters/Plant.h"

#include "items/Bullet.h"
#include "items/Coin.h"
#include "items/Mushroom.h"

#include "materials/Portal.h"
#include "materials/Door.h"
#include "materials/QuestionBrick.h"

#include "configs/monsters/Gommba600000.h"
#include "configs/materials/QuestionBrick100000.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// jump to hole
	if (y > SCREEN_HEIGHT)
	{
		DebugOut(L"Mario die\n");
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(max_vx)) vx = max_vx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - time_untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		time_untouchable_start = 0;
		untouchable = 0;
	}

	is_on_platform = FALSE;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

//void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	// jump to hole
//	if (y > SCREEN_HEIGHT)
//	{
//		DebugOut(L"Mario die\n");
//		return;
//	}
//
//	vy += ay * dt;
//	vx += ax * dt;
//
//	if (abs(vx) > abs(max_vx)) vx = max_vx;
//
//	// reset untouchable timer if untouchable time has passed
//	if (GetTickCount64() - time_untouchable_start > MARIO_UNTOUCHABLE_TIME)
//	{
//		time_untouchable_start = 0;
//		untouchable = 0;
//	}
//
//	is_on_platform = FALSE;
//
//	CCollision::GetInstance()->Process(this, dt, coObjects);
//}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CDoor*>(e->obj))
		OnCollisionWithDoor(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);

	if (e->IsCollidedInYDimension() && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->IsCollidedFromTop()) is_on_platform = true;
	}

	else if (e->IsCollidedInXDimension() && e->obj->IsBlocking())
	{
		vx = 0;
	}
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (e->IsCollidedFromTop())
	{
		if (!koopa->IsDefend())
		{
			koopa->Defend();
			this->JumpDeflect();
		}
	}
	else // hit by Goomba
	{
		if (!untouchable) // not untouchable -> can die
		{
			if (koopa->IsDefend() && !koopa->IsMarioKicked()) {
				koopa->BeKick(vx);
			}
		}
	}
}

void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);

	this->Die();
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);

	if (this->IsSmall())
		this->Zoom();
	mushroom->Delete();
}

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

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit
	if (e->IsCollidedFromTop())
	{
		if (!goomba->IsDead())
		{
			goomba->Die();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (!untouchable && !goomba->IsDead())
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	DebugOut(L"Collision with coin");
	if (e->IsCollidedInXDimension() || e->IsCollidedInYDimension())
	{
		e->obj->Delete();
		coin++;
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithDoor(LPCOLLISIONEVENT e) {
	CDoor* door = (CDoor*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(door->GetSceneId());
}

int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!is_on_platform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
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
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

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
		if (is_sitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
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
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) {
		aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	LPANIMATION ani = animations->Get(aniId);

	ResetPositionIfOutOfScreen(x, y);

	if (ani != NULL)
		ani->Render(x, y);

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed!
	if (this->IsDead()) return;

	switch (state)
	{
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
	{
		if (is_sitting) break;
		max_vx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	}
	case MARIO_STATE_JUMP:
		if (is_sitting) break;
		if (is_on_platform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (is_on_platform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			is_sitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (is_sitting)
		{
			is_sitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}
//void CMario::SetState(int state)
//{
//	// DIE is the end state, cannot be changed!
//	if (this->IsDead()) return;
//
//	switch (state)
//	{
//	case MARIO_STATE_RUNNING_RIGHT:
//		if (is_sitting) break;
//		ax = MARIO_ACCEL_RUN_X;
//		nx = 1;
//		break;
//	case MARIO_STATE_RUNNING_LEFT:
//		if (is_sitting) break;
//		ax = -MARIO_ACCEL_RUN_X;
//		nx = -1;
//		break;
//	case MARIO_STATE_WALKING_RIGHT:
//		if (is_sitting) break;
//		ax = MARIO_ACCEL_WALK_X;
//		nx = 1;
//		break;
//	case MARIO_STATE_WALKING_LEFT:
//	{
//		if (is_sitting) break;
//		ax = -MARIO_ACCEL_WALK_X;
//		nx = -1;
//		break;
//	}
//	case MARIO_STATE_JUMP:
//		if (is_sitting) break;
//		if (is_on_platform)
//		{
//			if (abs(this->vx) == MARIO_RUNNING_SPEED)
//				vy = -MARIO_JUMP_RUN_SPEED_Y;
//			else
//				vy = -MARIO_JUMP_SPEED_Y;
//		}
//		break;
//
//	case MARIO_STATE_RELEASE_JUMP:
//		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
//		break;
//
//	case MARIO_STATE_SIT:
//		if (is_on_platform && level != MARIO_LEVEL_SMALL)
//		{
//			state = MARIO_STATE_IDLE;
//			is_sitting = true;
//			ax = 0.0f;
//			vx = 0.0f;
//			y += MARIO_SIT_HEIGHT_ADJUST;
//		}
//		break;
//
//	case MARIO_STATE_SIT_RELEASE:
//		if (is_sitting)
//		{
//			is_sitting = false;
//			state = MARIO_STATE_IDLE;
//			y -= MARIO_SIT_HEIGHT_ADJUST;
//		}
//		break;
//
//	case MARIO_STATE_IDLE:
//		ax = 0.0f;
//		vx = 0.0f;
//		break;
//	case MARIO_STATE_DIE:
//		vx = 0;
//		ax = 0;
//		dead = TRUE;
//		vy = -MARIO_JUMP_DEFLECT_SPEED; //Mario jump deflect when die
//		break;
//	}
//
//	CGameObject::SetState(state);
//}
void CMario::Die()
{
	if (this->IsBig())
	{
		this->Shrink();
		StartUntouchable();
		return;
	}
	SetState(MARIO_STATE_DIE);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (is_sitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
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
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}