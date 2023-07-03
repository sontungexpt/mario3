#include "Hud.h"
#include "scenes/PlayScene.h"

#include "objects/Mario.h"
#include "GameData.h"
#include "FontManager.h"

void CHud::Update(DWORD dt)
{
}

void CHud::RenderHudBackground()
{
	/*CSprites* s = CSprites::GetInstance();
	LPSPRITE big_sprite = s->Get(ID_SPRITE_HUD_BACKGROUND);
	int big_sprite_width = big_sprite->GetRight() - big_sprite->GetLeft();
	int big_sprite_height = big_sprite->GetBottom() - big_sprite->GetTop();

	int number_cell_width = big_sprite_width / 16;
	int number_cell_height = big_sprite_height / 16;

	int element_id = ID_ANI_HUD_BACKGROUND;

	int drawed_width = 0;
	int drawed_height = 0;

	for (int i = 0; i < number_cell_height; i++)
	{
		drawed_width = 0;
		for (int j = 0; j < number_cell_width; j++)
		{
			element_id += 1;
			drawed_width += 16;

			int width_to_draw = big_sprite_width >= drawed_width ? 16 : big_sprite_width - big_sprite->GetLeft() + j * 16;
			int height_to_draw = big_sprite_height >= drawed_height ? 16 : big_sprite_height - big_sprite->GetTop() + i * 16;

			big_sprite->GetTexture();

			s->Add(element_id, big_sprite->GetLeft() + j * 16, big_sprite->GetTop() + i * 16, big_sprite->GetLeft() + j * 16 + width_to_draw, big_sprite->GetTop() + i * 16 + height_to_draw, big_sprite->GetTexture());
			s->Get(element_id)->Draw(x - big_sprite_width / 2 + j * 16 + 16 / 2, y - big_sprite_height / 2 + i * 16);
		}
		drawed_height += 16;
	}*/

	CAnimations::GetInstance()->Get(ID_ANI_HUD_BACKGROUND)->Render(x, y);
}

void CHud::RenderMarioRemainingLife()
{
	float start_x = GetLeft() + 44;
	float start_y = GetTop() + 15;

	float life_icon_x = GetLeft() + HUD_LIFE_BBOX_WIDTH / 2 + 14;
	float life_icon_y = GetTop() + HUD_LIFE_BBOX_HEIGHT / 2 + 13;

	CFontManager::RenderIcon("life", life_icon_x, life_icon_y);
	CFontManager::RenderIcon("X", life_icon_x + HUD_LIFE_BBOX_WIDTH / 2 + HUD_X_ICON_BBOX_WIDTH / 2 + 3, life_icon_y + 1.0f);
	CFontManager::RenderNumber(CGameData::GetInstance()->GetLife(), start_x, start_y);
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

	CFontManager::RenderNumber(CGameData::GetInstance()->GetPoint(), start_x, start_y, 6);
}

void CHud::RenderWorldNumber()
{
	float start_x = GetLeft() + 56;
	float start_y = GetTop() + 5;

	CFontManager::RenderString("WORLD", start_x - HUD_CHAR_BBOX_WIDTH * 5 - 4, start_y - 2);
	CFontManager::RenderNumber(CGameData::GetInstance()->GetEntryDoorLevel(), start_x, start_y);
}

void CHud::RenderPlayerCoin()
{
	float coin_x = GetLeft() + 143;
	float coin_y = GetTop() + 5;

	float dolar_icon_y = GetTop() + 7;

	CFontManager::RenderIcon("dolar", coin_x - HUD_CHAR_BBOX_WIDTH - 3, dolar_icon_y);
	CFontManager::RenderNumber(CGameData::GetInstance()->GetCoin(), coin_x, coin_y);
}

void CHud::RenderMarioRemainingTime()
{
	float start_x = GetLeft() + 137;
	float start_y = GetTop() + 15;

	float clock_icon_y = GetTop() + 19.5f;
	CFontManager::RenderIcon("clock", start_x - HUD_CHAR_BBOX_WIDTH - 3, clock_icon_y);
	CFontManager::RenderNumber((int)CGameData::GetInstance()->GetRemainTime(), start_x, start_y, 3);
}

void CHud::RenderFrame(float left, float top, int width, int height)
{
	// draw top left corner
	//render top edge
	for (int i = 0; i < height; i++)
	{
		float y_icon = top + i * HUD_CHAR_BBOX_HEIGHT;
		for (int j = 0; j < width; j++)
		{
			float x_icon = left + j * HUD_CHAR_BBOX_WIDTH;

			if (i == 0 && j == 0)
				CAnimations::GetInstance()->Get(ID_ANI_TOP_LEFT_CORNER_ICON)->Render(x_icon, y_icon);
			else if (i == 0 && j == width - 1)
				CAnimations::GetInstance()->Get(ID_ANI_TOP_RIGHT_CORNER_ICON)->Render(x_icon, y_icon);
			else if (i == height - 1 && j == 0)
				CAnimations::GetInstance()->Get(ID_ANI_BOTTOM_LEFT_CORNER_ICON)->Render(x_icon, y_icon);
			else if (i == height - 1 && j == width - 1)
				CAnimations::GetInstance()->Get(ID_ANI_BOTTOM_RIGHT_CORNER_ICON)->Render(x_icon, y_icon);
			else
			{
				if (i == 0 || i == width - 1)
				{
					if (i == 0)
						CAnimations::GetInstance()->Get(ID_ANI_HORIZONTAL_EDGE_ICON)->Render(x_icon, y_icon - HUD_HORIZONTAL_EDGE_ICON_BBOX_HEIGHT / 2);
					else
						CAnimations::GetInstance()->Get(ID_ANI_HORIZONTAL_EDGE_ICON)->Render(x_icon, y_icon + HUD_CHAR_BBOX_HEIGHT + HUD_HORIZONTAL_EDGE_ICON_BBOX_HEIGHT / 2);
				}
				/*	else if (j == 0 || j == height - 1)
					{
						if (j == 0)
							CAnimations::GetInstance()->Get(ID_ANI_VERTICAL_EDGE_ICON)->Render(x_icon - HUD_CHAR_BBOX_WIDTH / 2, y_icon);
						else
							CAnimations::GetInstance()->Get(ID_ANI_VERTICAL_EDGE_ICON)->Render(x_icon + HUD_CHAR_BBOX_WIDTH / 2, y_icon);
					}*/
			}
		}
		//CAnimations::GetInstance()->Get(ID_ANI_HORIZONTAL_EDGE_ICON)->Render(left + HUD_CHAR_BBOX_WIDTH + i * 16, top);
	}

	/*Cursor.GoToXY(new Coord(origin.x + 1, origin.y));
	for (int i = 0; i < width; i++)
		Console.Write('_');
	Cursor.GoToXY(new Coord(origin.x + 1, origin.y + height / 2));
	for (int i = 0; i < width; i++)
		Console.Write('_');
	for (int i = 0; i < height / 2; i++)
	{
		Cursor.GoToXY(new Coord(origin.x, origin.y + 1 + i));
		Console.Write((char)124);
	}
	for (int i = 0; i < height / 2; i++)
	{
		Cursor.GoToXY(new Coord(origin.x + width + 1, origin.y + 1 + i));
		Console.Write((char)124);
	}*/
}

void CHud::Render()
{
	//RenderFrame(x, y - 50, 5, 3);

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