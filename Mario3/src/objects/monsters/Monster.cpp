#include "debug.h"
#include "Monster.h"
#include "Goomba.h"
#include "objects/Mario.h"
#include "scenes/PlayScene.h"

void CMonster::OnNoCollision(DWORD dt)
{
	if (is_deleted) return;

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
			// move same direction >> same state >> diff velocity
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

void CMonster::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMonster*>(e->obj)) {
		OnCollisionWithMonster(e);
	}

	if (!e->obj->IsBlocking()) return;

	// collide with blocking
	if (e->IsCollidedInYDimension())
	{
		if (e->IsCollidedFromTop())
		{
			is_on_platform = TRUE;
		}
		vy = 0;
	}

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
	case MONSTER_STATE_WALKING_RIGHT:
		// same as above
		vy = 0;
		vx = fabs(vx) > 0 ? fabs(vx) : MONSTER_WALKING_SPEED;
		ax = fabs(ax);
		break;
	default:
		break;
	}
}

void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	//move out of screen >> delete
	if (x + GetWidth() / 2 <= 0)
	{
		dead = true;
		is_deleted = true;
		return;
	}

	// fall to to the hole >> delete
	if (y > SCREEN_HEIGHT)
	{
		dead = true;
		is_deleted = true;
		return;
	}

	// die >> delete
	if (dead && (GetTickCount64() - dead_time > disapear_time))
	{
		is_deleted = true;
		return;
	}

	if (dead) return;

	vy += ay * dt;
	vx += ax * dt;

	if (max_vx > 0 && abs(vx) > max_vx)
	{
		ax = 0;
		vx = vx > 0 ? max_vx : -max_vx;
	}

	is_on_platform = FALSE;

	CGameObject::Update(dt, co_objects);
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