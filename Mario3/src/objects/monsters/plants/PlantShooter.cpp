#include "scenes/PlayScene.h"

#include "PlantShooter.h"
#include "objects/Mario.h"
#include "objects/items/Bullet.h"
#include "objects/materials/Pipe.h"

void CPlantShooter::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	switch (color)
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
		DebugOut(L"[ERROR] Unhandled type %d at CPlantShooter::GetBoundingBox\n", color);
		break;
	}
}

void CPlantShooter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsInCamera()) return;

	CPlant::Update(dt, coObjects);

	if (is_disabled_up_down) return;

	UpdateBullet(dt);
}
void CPlantShooter::UpdateBullet(DWORD dt)
{
	if (CanShootBullet()) {
		// if plant is up and not shooted, then reload bullet
		if (time_reload_bullet_start <= 0)
		{
			time_reload_bullet_start = GetTickCount64();
		}
		else
		{
			ShootBulletIfReady();
		}
	}
}

void CPlantShooter::ShootBulletIfReady()
{
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;

	if (!mario) return;

	if (GetTickCount64() - time_reload_bullet_start > TIME_RELOAD_BULLET) {
		float bullet_y = CompareYWithMario() == 1 ?
			GetTop() + 10 : GetTop() + 4;
		float bullet_x = CompareXWithMario() == 1 ?
			x - GetWidth() / 2 - 2 : x + GetWidth() / 2 + 2;

		CBullet* bullet = (CBullet*)scene->AddObject(new CBullet(bullet_x, bullet_y));

		bullet->Shoot(mario->GetX(), mario->GetY());
		is_shooted = TRUE;
		time_reload_bullet_start = 0;
	}
}

bool CPlantShooter::CanShootBullet()
{
	// is upping
	return direction_up_down <= 0 && y <= min_y && !is_shooted;
}

void CPlantShooter::Render()
{
	if (is_disabled_up_down) return;
	if (is_deleted) return; // notthing to render

	if (!IsInCamera()) return; // lazy load

	int aniId = -1;

	switch (color)
	{
	case PLANT_SHOOTER_RED:
		aniId = GetAniIdRed();
		break;
	case PLANT_SHOOTER_GREEN:
		aniId = GetAniIdGreen();
		break;
	default:
		DebugOut(L"[ERROR] Unhandled color %d at CPlantShooter::Render\n", color);
		return;
	}

	if (aniId == -1) return;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

int CPlantShooter::GetAniIdRed()
{
	switch (state)
	{
	case PLANT_STATE_UP:
	case PLANT_STATE_DOWN:
		if (CompareXWithMario() == 1)
		{
			if (CompareYWithMario() == 1)
				return ID_ANI_RED_PLANT_SHOOTER_LEFT_NOT_SHOOT_UNDER;
			else //plant under right with mario
				return ID_ANI_RED_PLANT_SHOOTER_LEFT_NOT_SHOOT_TOP;
		}
		// plant top left with mario
		else if (CompareXWithMario() == -1)
		{
			if (CompareYWithMario() == 1)
				return ID_ANI_RED_PLANT_SHOOTER_RIGHT_NOT_SHOOT_UNDER;
			else // plant under left with mario
				return ID_ANI_RED_PLANT_SHOOTER_RIGHT_NOT_SHOOT_TOP;
		}
		break;
	}
	return -1;
}

int CPlantShooter::GetAniIdGreen()
{
	switch (state)
	{
	case PLANT_STATE_UP:
	case PLANT_STATE_DOWN:
		if (CompareXWithMario() == 1)
		{
			if (CompareYWithMario() == 1)
				return ID_ANI_GREEN_PLANT_SHOOTER_LEFT_NOT_SHOOT_UNDER;
			else //plant under right with mario
				return ID_ANI_GREEN_PLANT_SHOOTER_LEFT_NOT_SHOOT_TOP;
		}
		// plant top left with mario
		else if (CompareXWithMario() == -1)
		{
			if (CompareYWithMario() == 1)
				return ID_ANI_GREEN_PLANT_SHOOTER_RIGHT_NOT_SHOOT_UNDER;
			else // plant under left with mario
				return ID_ANI_GREEN_PLANT_SHOOTER_RIGHT_NOT_SHOOT_TOP;
		}
		break;
	}
	return -1;
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