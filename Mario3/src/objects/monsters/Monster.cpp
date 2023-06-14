#include "debug.h"
#include "Monster.h"
#include "Goomba.h"

void CMonster::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMonster::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMonster*>(e->obj)) {
		// now the monster will be pushed away from the other monster
		// with the velocity of itself
		if (!dead)
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
						e->obj->GetState() == MONSTER_STATE_WALKING_LEFT ||
						e->obj->GetState() == MONSTER_STATE_WALKING_RIGHT
						)
					)
				{
					if (e->obj->GetState() == state)
					{
						// objv > v change state of objv
						// objv < v change state of v
						if (e->obj->GetVx() > vx) e->obj->SetState(-e->obj->GetState());
						else SetState(-state);
					}
					// move diff direction
					else {
						SetState(-state);
						e->obj->SetState(-e->obj->GetState());
					}
				}
			}
		}
	};

	if (!e->obj->IsBlocking()) return;

	if (e->IsCollidedInYDimension())
	{
		vy = 0;
	}

	if (e->IsCollidedInXDimension())
	{
		// meet the blocking then change direction
		if (state == MONSTER_STATE_WALKING_LEFT || state == MONSTER_STATE_WALKING_RIGHT)
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
		vx = fabs(vx) > 0 ? -fabs(vx) : -MONSTER_WALKING_SPEED;
		ax = -fabs(ax);
		break;
	case MONSTER_STATE_WALKING_RIGHT:
		// same as above
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
	if (x + GetWidth() <= 0)
	{
		dead = true;
		isDeleted = true;
		return;
	}
	// fall to to the hole >> delete
	if (y > SCREEN_HEIGHT)
	{
		dead = true;
		isDeleted = true;
		return;
	}

	// die >> delete
	if (dead && (GetTickCount64() - dead_time > disapear_time))
	{
		isDeleted = true;
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if (max_speed > 0 && abs(vx) > max_speed)
	{
		ax = 0;
		vx = vx > 0 ? max_speed : -max_speed;
	}

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}