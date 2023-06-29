#include "Hud.h"
#include "scenes/PlayScene.h"
#include "objects/Mario.h"

void CHud::Update(DWORD dt)
{
}

void CHud::RenderMarioRemainingLife()
{
}

void CHud::RenderArrowPower()
{
	float y_arrow = GetTop() + 7 + HUD_ARROW_BBOX_HEIGHT / 2;
	float x_start_arrow = GetLeft() + 55 + HUD_ARROW_BBOX_HEIGHT / 2;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	for (int i = 1; i <= mario->GetPower(); i++)
		CAnimations::GetInstance()->Get(ID_ANI_HUD_ARROW)->Render(x_start_arrow + (i - 1) * HUD_ARROW_BBOX_WIDTH, y_arrow);

	if (is_full_power_dark && GetTickCount64() - time_change_full_power_status_start > HUD_FULL_POWER_FLASHING_DURATION)
	{
		is_full_power_dark = FALSE;
		time_change_full_power_status_start = GetTickCount64();
	}

	if (is_full_power_dark)
		return;

	if (mario->IsFullPower() && GetTickCount64() - time_change_full_power_status_start > HUD_FULL_POWER_FLASHING_DURATION)
	{
		is_full_power_dark = TRUE;
		time_change_full_power_status_start = GetTickCount64();
	}

	if (mario->IsFullPower())
	{
		float y_full_power = GetTop() + 7 + HUD_FULL_POWER_HEIGHT / 2;
		float x_full_power = GetLeft() + 104 + HUD_FULL_POWER_WIDTH / 2;
		CAnimations::GetInstance()->Get(ID_ANI_FULL_POWER)->Render(x_full_power, y_full_power);
	}
}

void CHud::Render()
{
	//render background
	CAnimations::GetInstance()->Get(ID_ANI_HUD_BACKGROUND)->Render(x, y);

	RenderArrowPower();
	RenderMarioRemainingLife();
}

void CHud::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HUD_BACKGROUND_BBOX_WIDTH / 2;
	top = y - HUD_BACKGROUND_BBOX_HEIGHT / 2;
	right = left + HUD_BACKGROUND_BBOX_WIDTH;
	bottom = top + HUD_BACKGROUND_BBOX_HEIGHT;
}