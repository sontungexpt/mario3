#include "debug.h"
#include "Monster.h"
#include "Goomba.h"
#include "objects/Mario.h"
#include "scenes/PlayScene.h"
#include "objects/Platform.h"
#include "objects/materials/EffectManager.h"
#include "GameData.h"

void CMonster::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMonster::OnCollisionWithMonster(LPCOLLISIONEVENT e)
{
	CMonster* monster_dest = dynamic_cast<CMonster*>(e->obj);
	if (!IsDead() && !monster_dest->IsDead())
	{
		if (e->IsCollidedInXDimension())
		{
			if (
				(
					state == MONSTER_STATE_WALKING_LEFT ||
					state == MONSTER_STATE_WALKING_RIGHT
					)
				&&
				(
					monster_dest->GetState() == MONSTER_STATE_WALKING_LEFT ||
					monster_dest->GetState() == MONSTER_STATE_WALKING_RIGHT
					)
				)
			{
				// move same direction >> same state >> diff velocity
				if (monster_dest->GetState() == state)
				{
					// objv > v change state of objv
					// objv < v change state of v
					if (fabs(monster_dest->GetVx()) > fabs(vx))
						monster_dest->SetState(-monster_dest->GetState());
					else SetState(-state);
				}
				// move diff direction
				else {
					SetState(-state);
					monster_dest->SetState(-monster_dest->GetState());
				}
			}
		}
	}
}

void CMonster::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	if (!e->IsCollidedFromBottom())
	{
		if (!mario->IsHitting())
			mario->Die();
	}
}

void CMonster::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	// this is dirty way to prevent the goomba is falling out of platform

	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (platform)
	{
		is_on_platform = TRUE;
	}
}

void CMonster::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithPlayer(e);
	else if (dynamic_cast<CMonster*>(e->obj))
		OnCollisionWithMonster(e);

	if (!e->obj->IsBlocking()) return;
	if (e->IsCollidedInYDimension())
	{
		vy = 0;
		if (e->IsCollidedFromTop())
		{
			OnCollisionWithPlatForm(e);
			is_on_platform = TRUE;
		}
	}

	// collide with blocking
	if (e->IsCollidedInXDimension())
	{
		// meet the blocking then change direction
		if (state == MONSTER_STATE_WALKING_LEFT ||
			state == MONSTER_STATE_WALKING_RIGHT
			)
		{
			SetState(-state);
		}
		else
		{
			vx = -vx;
			ax = -ax;
		}
	}
}

void CMonster::InitVWhenMarioHit()
{
	LPPLAYSCENE scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
	if (mario)
	{
		vx = mario->GetNx() >= 0 ?
			MONSTER_BE_HITTED_BY_MARIO_DEFLECT_VX :
			-MONSTER_BE_HITTED_BY_MARIO_DEFLECT_VX;
	}
	vy = -MONSTER_BE_HITTED_BY_MARIO_DEFLECT_SPEED;
	ay = GRAVITY;
	ax = 0;
}

void CMonster::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MONSTER_STATE_IDLE:
		vx = 0;
		vy = 0;
		ax = 0;
		break;
	case MONSTER_STATE_DIE:
		dead_time = GetTickCount64();
		dead = true;
		vx = 0;
		vy = 0;
		ax = 0;
		break;
	case MONSTER_STATE_WALKING_LEFT:
		// if you change v = 0 in some case then you want to reset it to default
		// by call SetState(MONSTER_STATE_WALKING_LEFT) then
		// this line will help you, if not has this line then the you need to change vx = something by self
		// if you use the custom velocity then you should to change it by self
		// this line just help you to reset the velocity to default state of monster abstract class
		vy = 0;
		vx = fabs(vx) > 0 ? -fabs(vx) : -MONSTER_WALKING_SPEED;
		ax = -fabs(ax);
		break;
	case MONSTER_STATE_BE_HITTED:
	{
		InitVWhenMarioHit();
		break;
	}
	case MONSTER_STATE_WALKING_RIGHT:
		// same as above
		vy = 0;
		vx = fabs(vx) > 0 ? fabs(vx) : MONSTER_WALKING_SPEED;
		ax = fabs(ax);
		break;
	default:
		DebugOut(L"[ERROR] Unhandled monster state %d in CMonster::SetState\n", state);
		break;
	}
}

int CMonster::RemoveWhenMoveToDangerousSpace()
{
	if (CGameObject::RemoveWhenMoveToDangerousSpace() == 1)
	{
		dead = TRUE;
		return 1;
	}
	return 0;
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (dead)
	{
		// dead and timeout >> delete
		if (GetTickCount64() - dead_time > disapear_time)
			is_deleted = true;
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if (max_vx > 0 && abs(vx) > max_vx)
		vx = vx > 0 ? max_vx : -max_vx;

	is_on_platform = FALSE;
	CCollision::GetInstance()->Process(this, dt, co_objects);
}

int CMonster::CompareYWithMario()
{
	if (is_deleted || dead) return -3; // plant is deleted
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario == nullptr) return -2;

	if (mario->GetY() < y) return -1; // plant under mario
	else if (mario->GetY() > y)	return 1; // plant on top mario
	else return 0; // plant and mario in same position
}

int CMonster::CompareXWithMario()
{
	if (is_deleted || dead) return -3; // plant is deleted
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (mario == nullptr) return -2;

	if (mario->GetX() < x) return 1; // plant right mario
	else if (mario->GetX() > x)	return -1; // plant left mario
	else return 0; // plant and mario in same position
}

void CMonster::BeKickedByKoopa()
{
	is_deleted = TRUE;
	is_kicked_by_koopa = TRUE;
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	CGameData::GetInstance()->IncreasePointBy(100);
}

void CMonster::BeHitByMarioTail()
{
	is_deleted = TRUE;
	is_mario_hitted = TRUE;
	CEffectManager::Gennerate(this, POINT_100, 0.0f);
	CGameData::GetInstance()->IncreasePointBy(100);
}