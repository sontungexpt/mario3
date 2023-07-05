#include "scenes/PlayScene.h"

#include "PlantShooter.h"
#include "objects/Mario.h"
#include "objects/items/Bullet.h"
#include "objects/materials/Pipe.h"

void CPlantShooter::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (is_deleted) return; // notthing to get
	switch (type)
	{
	case PLANT_SHOOTER_RED:
		left = x - PLANT_SHOOTER_BBOX_WIDTH / 2;
		top = y - PLANT_SHOOTER_BBOX_HEIGHT_RED / 2;
		right = left + PLANT_SHOOTER_BBOX_WIDTH;
		bottom = top + PLANT_SHOOTER_BBOX_HEIGHT_RED;
		break;
	case PLANT_SHOOTER_GREEN:
		left = x - PLANT_SHOOTER_BBOX_WIDTH / 2;
		top = y - PLANT_SHOOTER_BBOX_HEIGHT_GREEN / 2;
		right = left + PLANT_SHOOTER_BBOX_WIDTH;
		bottom = top + PLANT_SHOOTER_BBOX_HEIGHT_GREEN;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled type %d at CPlantShooter::GetBoundingBox\n", type);
		break;
	}
}

void CPlantShooter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (is_disabled_up_down) return;

	if (!IsInCamera()) return;

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	if (mario->IsDead()) return; // if mario dead, plant not need to update

	CPlant::Update(dt, coObjects);

	if (is_upping && y <= min_y) {
		if (!is_shooted)// just one bullet per state up
		{
			// if plant is up and not shooted, then reload bullet
			if (time_reload_bullet_start <= 0)
			{
				time_reload_bullet_start = GetTickCount64();
			}
			else
			{
				// after finished reloading bullet, then shoot bullet
				if (GetTickCount64() - time_reload_bullet_start > TIME_RELOAD_BULLET) {
					float bullet_y = CompareYWithMario() == 1 ? GetTop() + 10 : GetTop() + 4;
					float bullet_x = CompareXWithMario() == 1 ? x - GetWidth() / 2 - 2 : x + GetWidth() / 2 + 2;

					CBullet* bullet = (CBullet*)scene->AddObject(new CBullet(bullet_x, bullet_y));

					bullet->Shoot(mario->GetX(), mario->GetY());
					is_shooted = TRUE;
					time_reload_bullet_start = 0;
				}
			}
		}
	}
}

void CPlantShooter::Render()
{
	if (is_disabled_up_down) return;

	if (is_deleted) return; // notthing to render
	if (!IsInCamera()) return; // lazy load

	int aniId = -1;

	switch (type)
	{
	case PLANT_SHOOTER_RED:
		aniId = GetAniIdRed();
		break;
	case PLANT_SHOOTER_GREEN:
		aniId = GetAniIdGreen();
		break;
	default:
		DebugOut(L"[ERROR] Unhandled type %d at CPlantShooter::Render\n", type);
		return;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

int CPlantShooter::GetAniIdRed()
{
	int aniId = -1;
	switch (state)
	{
	case PLANT_STATE_UP:
	case PLANT_STATE_DOWN:
		if (CompareXWithMario() == 1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_RED_PLANT_SHOOTER_LEFT_NOT_SHOOT_UNDER;
			else //plant under right with mario
				aniId = ID_ANI_RED_PLANT_SHOOTER_LEFT_NOT_SHOOT_TOP;
		}
		// plant top left with mario
		else if (CompareXWithMario() == -1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_RED_PLANT_SHOOTER_RIGHT_NOT_SHOOT_UNDER;
			else // plant under left with mario
				aniId = ID_ANI_RED_PLANT_SHOOTER_RIGHT_NOT_SHOOT_TOP;
		}
		break;
	default:
		DebugOut(L"[ERROR] Unhandled state %d at CPlantShooter::GetAniIdRed\n", state);
		break;
	}
	return aniId;
}

int CPlantShooter::GetAniIdGreen()
{
	int aniId = -1;
	switch (state)
	{
	case PLANT_STATE_UP:
	case PLANT_STATE_DOWN:
		if (CompareXWithMario() == 1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_GREEN_PLANT_SHOOTER_LEFT_NOT_SHOOT_UNDER;
			else //plant under right with mario
				aniId = ID_ANI_GREEN_PLANT_SHOOTER_LEFT_NOT_SHOOT_TOP;
		}
		// plant top left with mario
		else if (CompareXWithMario() == -1)
		{
			if (CompareYWithMario() == 1)
				aniId = ID_ANI_GREEN_PLANT_SHOOTER_RIGHT_NOT_SHOOT_UNDER;
			else // plant under left with mario
				aniId = ID_ANI_GREEN_PLANT_SHOOTER_RIGHT_NOT_SHOOT_TOP;
		}
		break;
	default:
		DebugOut(L"[ERROR] Unhandled state %d at CPlantShooter::GetAniIdRed\n", state);
		break;
	}
	return aniId;
}

void CPlantShooter::SetState(int state)
{
	switch (state) {
	case PLANT_STATE_UP:
		is_shooted = FALSE;
		time_reload_bullet_start = 0;
		break;
	case PLANT_STATE_DOWN:
		is_shooted = FALSE;
		time_reload_bullet_start = 0;
		break;
	}
	CPlant::SetState(state);
}