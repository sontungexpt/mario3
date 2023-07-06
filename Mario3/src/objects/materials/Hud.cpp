#include "Hud.h"
#include "GameData.h"
#include "DrawingManager.h"
#include "objects/Mario.h"

#include "scenes/PlayScene.h"

void CHud::Update(DWORD dt)
{
	CGameData::GetInstance()->CountDownRemainTime();
}

void CHud::RenderHudBackground()
{
	CAnimations::GetInstance()->Get(ID_ANI_HUD_BACKGROUND)->Render(x, y);
}

void CHud::RenderMarioRemainingLife()
{
	float start_x = GetLeft() + 44;
	float start_y = GetTop() + 15;

	float life_icon_x = GetLeft() + HUD_LIFE_BBOX_WIDTH / 2 + 14;
	float life_icon_y = GetTop() + HUD_LIFE_BBOX_HEIGHT / 2 + 13;

	CDrawingManager::RenderIcon("life", life_icon_x, life_icon_y);
	CDrawingManager::RenderIcon("X", life_icon_x + HUD_LIFE_BBOX_WIDTH / 2 + HUD_X_ICON_BBOX_WIDTH / 2 + 3, life_icon_y + 1.0f);
	CDrawingManager::RenderNumber(CGameData::GetInstance()->GetLife(), start_x, start_y);
}

void CHud::RenderArrowPower()
{
	float y_arrow = GetTop() + 4 + HUD_ARROW_BBOX_HEIGHT / 2;
	float x_start_arrow = GetLeft() + 64 + HUD_ARROW_BBOX_HEIGHT / 2;

	float y_full_power = GetTop() + 4 + HUD_FULL_POWER_HEIGHT / 2;
	float x_full_power = GetLeft() + 113 + HUD_FULL_POWER_WIDTH / 2;

	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (!mario || mario->IsDead())
	{
		for (int i = 1; i <= MARIO_MAX_POWER; i++)
			CAnimations::GetInstance()->Get(ID_ANI_ARROW_ICON_BLACK)->Render(x_start_arrow + (i - 1) * HUD_ARROW_BBOX_WIDTH, y_arrow);
		CAnimations::GetInstance()->Get(ID_ANI_FULL_POWER_ICON_BLACK)->Render(x_full_power, y_full_power);
		return;
	}

	for (int i = 1; i <= mario->GetPower(); i++)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_ICON_WHITE)->Render(x_start_arrow + (i - 1) * HUD_ARROW_BBOX_WIDTH, y_arrow);
	for (int i = 1; i <= MARIO_MAX_POWER - mario->GetPower(); i++)
		CAnimations::GetInstance()->Get(ID_ANI_ARROW_ICON_BLACK)->Render(x_start_arrow + mario->GetPower() * HUD_ARROW_BBOX_WIDTH + (i - 1) * HUD_ARROW_BBOX_WIDTH, y_arrow);

	if (is_full_power_dark && GetTickCount64() - time_change_full_power_status_start > HUD_FULL_POWER_FLASHING_DURATION)
	{
		is_full_power_dark = FALSE;
		time_change_full_power_status_start = GetTickCount64();
	}

	CAnimations::GetInstance()->Get(ID_ANI_FULL_POWER_ICON_BLACK)->Render(x_full_power, y_full_power);

	// if full power is dark, don't render white full power icon
	if (is_full_power_dark) return;

	if (mario->IsFullPower() && GetTickCount64() - time_change_full_power_status_start > HUD_FULL_POWER_FLASHING_DURATION)
	{
		is_full_power_dark = TRUE;
		time_change_full_power_status_start = GetTickCount64();
	}

	if (mario->IsFullPower())
	{
		CAnimations::GetInstance()->Get(ID_ANI_FULL_POWER_ICON_WHITE)->Render(x_full_power, y_full_power);
	}
}

void CHud::RenderPlayerPoint()
{
	float start_x = GetLeft() + 69;
	float start_y = GetTop() + 15;

	CDrawingManager::RenderNumber(CGameData::GetInstance()->GetPoint(), start_x, start_y, 6);
}

void CHud::RenderWorldNumber()
{
	float start_x = GetLeft() + 56;
	float start_y = GetTop() + 5;

	CDrawingManager::RenderString("WORLD", start_x - HUD_CHAR_BBOX_WIDTH * 5 - 4, start_y - 2);
	CDrawingManager::RenderNumber(CGameData::GetInstance()->GetEntryDoorLevel(), start_x, start_y);
}

void CHud::RenderPlayerCoin()
{
	float coin_x = GetLeft() + 143;
	float coin_y = GetTop() + 5;

	float dolar_icon_y = GetTop() + 7;

	CDrawingManager::RenderIcon("dolar", coin_x - HUD_CHAR_BBOX_WIDTH - 3, dolar_icon_y);
	CDrawingManager::RenderNumber(CGameData::GetInstance()->GetCoin(), coin_x, coin_y);
}

void CHud::RenderMarioRemainingTime()
{
	float start_x = GetLeft() + 137;
	float start_y = GetTop() + 15;

	float clock_icon_y = GetTop() + 19.5f;
	CDrawingManager::RenderIcon("clock", start_x - HUD_CHAR_BBOX_WIDTH - 3, clock_icon_y);
	CDrawingManager::RenderNumber((int)CGameData::GetInstance()->GetRemainTime(), start_x, start_y, 3);
}

void CHud::Render()
{
	RenderHudBackground();
	RenderArrowPower();
	RenderMarioRemainingLife();
	RenderPlayerPoint();
	RenderPlayerCoin();
	RenderWorldNumber();
	RenderMarioRemainingTime();
}
void CHud::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HUD_BACKGROUND_BBOX_WIDTH / 2;
	top = y - HUD_BACKGROUND_BBOX_HEIGHT / 2;
	right = left + HUD_BACKGROUND_BBOX_WIDTH;
	bottom = top + HUD_BACKGROUND_BBOX_HEIGHT;
}