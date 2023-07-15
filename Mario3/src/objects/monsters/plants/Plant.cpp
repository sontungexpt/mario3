#include "Plant.h"
#include "objects/items/Bullet.h"
#include "objects/materials/Pipe.h"
#include "objects/Mario.h"

void CPlant::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	if (mario->IsHitting() && e->IsCollidedInXDimension())
		BeHitByMarioTail();
	else
		mario->Die();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (is_disabled_up_down) return;

	UpdateVerticalPosition(dt);

	// check collision with other objects after update
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::UpdateVerticalPosition(DWORD dt)
{
	if (direction_up_down <= 0) // is upping
	{
		if (y > min_y) {
			vy = -PLANT_SPEED_UP_DOWN;
		}
		else {
			// move to min_y // that means the plant is finish create
			vy = 0;
			y = min_y;

			// time out up state of plant move to down state
			if (IsTimeOutUpState()) {
				SetState(PLANT_STATE_DOWN);
			}
		}
	}
	else // is downing
	{
		if (direction_up_down > 0 && IsTimeOutDownState()) {
			SetState(PLANT_STATE_UP);
		}
	}
}

BOOLEAN CPlant::IsTimeOutUpState()
{
	return GetTickCount64() - time_up_start > time_out_up_state;
}

BOOLEAN CPlant::IsTimeOutDownState()
{
	return GetTickCount64() - time_down_start > time_out_down_state;
}

void CPlant::SetState(int state)
{
	CMonster::SetState(state);
	switch (state) {
	case PLANT_STATE_UP:
		direction_up_down = -1; // upping
		time_up_start = GetTickCount64();
		time_down_start = 0;
		vy = -PLANT_SPEED_UP_DOWN;
		break;
	case PLANT_STATE_DOWN:
		direction_up_down = 1; // downing
		time_down_start = GetTickCount64();
		time_up_start = 0;
		vy = PLANT_SPEED_UP_DOWN;
		break;
	case MONSTER_STATE_DIE: // ovveride state die in monster class
		is_deleted = true;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled state at CPlant::SetState %d\n", state);
		break;
	}
}