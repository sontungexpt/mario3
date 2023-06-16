#include "scenes/PlayScene.h"

#include "Plant.h"
#include "objects/items/Bullet.h"
#include "objects/materials/Pipe.h"

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (isDeleted) return; // notthing to get

	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = left + PLANT_BBOX_WIDTH;
	bottom = top + PLANT_BBOX_HEIGHT;
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->IsDead()) return; // if mario dead, plant not need to update

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
			if (GetTickCount64() - time_up_start > TIME_OUT_UP_STATE) {
				SetState(PLANT_STATE_DOWN);
				return;
			}

			if (is_shooted) return; // just one bullet per state up

			// if plant is up and not shooted, then reload bullet
			if (time_reload_bullet_start <= 0)
			{
				time_reload_bullet_start = GetTickCount64();
				return;
			}

			// reloaded bullet

			// shoot bullet
			if (!is_shooted)
			{
				if (GetTickCount64() - time_reload_bullet_start > TIME_RELOAD_BULLET) {
					float bullet_y = y - 4;
					float bullet_x = CompareXWithMario() == 1 ? x - GetWidth() / 2 - 2 : x + GetWidth() / 2 + 2;

					CBullet* bullet = (CBullet*)scene->AddObject(new CBullet(bullet_x, bullet_y));

					bullet->Shoot(mario->GetX(), mario->GetY());
					is_shooted = TRUE;
					time_reload_bullet_start = 0;
				}
			}

			DebugOut(L"render");
		}
	}
	else // is downing
	{
		if (GetTickCount64() - time_down_start > TIME_OUT_DOWN_STATE) {
			SetState(PLANT_STATE_UP);
			return;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlant::Render()
{
	if (isDeleted) return; // notthing to render
	if (!IsInCamera()) return; // lazy load

	int aniId = -1;
	if (state == PLANT_STATE_UP || state == PLANT_STATE_DOWN)
	{
		if (CompareXWithMario() == 1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_PLANT_LEFT_NOT_SHOOT_UNDER;
			else //plant under right with mario
				aniId = ID_ANI_PLANT_LEFT_NOT_SHOOT_TOP;
		}
		// plant top left with mario
		else if (CompareXWithMario() == -1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_PLANT_RIGHT_NOT_SHOOT_UNDER;
			else // plant under left with mario
				aniId = ID_ANI_PLANT_RIGHT_NOT_SHOOT_TOP;
		}
	}
	else
	{
		DebugOut(L"[ERROR] Unhandled state at CPlant::Render %d\n", state);
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CPlant::SetState(int state)
{
	CMonster::SetState(state);
	switch (state) {
	case PLANT_STATE_UP:
		is_downing = FALSE;
		is_upping = TRUE;
		is_shooted = FALSE;
		time_up_start = GetTickCount64();
		time_down_start = 0;
		time_reload_bullet_start = 0;
		vy = -PLANT_SPEED_UP_DOWN;
		break;
	case PLANT_STATE_DOWN:
		is_upping = FALSE;
		is_downing = TRUE;
		is_shooted = FALSE;
		time_down_start = GetTickCount64();
		time_up_start = 0;
		time_reload_bullet_start = 0;
		vy = PLANT_SPEED_UP_DOWN;
		break;
	case MONSTER_STATE_DIE: // ovveride state die in monster class
		isDeleted = true;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled state at CPlant::SetState %d\n", state);
		break;
	}
}