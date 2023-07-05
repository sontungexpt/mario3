#include "Plant.h"
#include "objects/items/Bullet.h"
#include "objects/materials/Pipe.h"
#include "objects/Mario.h"

void CPlant::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	CMario* mario = dynamic_cast<CMario*>(e->obj);
	mario->Die();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (is_disabled_up_down) return;

	if (is_upping) {
		// make sure that the plant will moving after create
		if (y > min_y) {
			vy = -PLANT_SPEED_UP_DOWN;
		}
		else {
			// move to min_y // that means the plant is finish create
			vy = 0;
			y = min_y;

			// time out up state of plant move to down state
			if (GetTickCount64() - time_up_start > time_out_up_state) {
				SetState(PLANT_STATE_DOWN);
			}
		}
	}
	else // is downing
	{
		//if (y > max_y)
		//{
		//	vy = 0;
		//	y = max_y;
		//}
		if (GetTickCount64() - time_down_start > time_out_down_state) {
			SetState(PLANT_STATE_UP);
		}
	}

	// check collision with other objects after update
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::SetState(int state)
{
	CMonster::SetState(state);
	switch (state) {
	case PLANT_STATE_UP:
		is_downing = FALSE;
		is_upping = TRUE;
		time_up_start = GetTickCount64();
		time_down_start = 0;
		vy = -PLANT_SPEED_UP_DOWN;
		break;
	case PLANT_STATE_DOWN:
		is_upping = FALSE;
		is_downing = TRUE;
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