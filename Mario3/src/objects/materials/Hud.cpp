#include "Hud.h"
#include <string>
#include "scenes/PlayScene.h"
#include "objects/Mario.h"
#include "GameData.h"

using namespace std;

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
	float start_x = GetLeft() + 36;
	float start_y = GetTop() + 15;
	RenderNumber(CGameData::GetInstance()->GetLife(), start_x, start_y);
}

void CHud::RenderPlayerPoint()
{
	float start_x = GetLeft() + 58;
	float start_y = GetTop() + 15;

	RenderNumber(CGameData::GetInstance()->GetPoint(), start_x, start_y, 6);
}

void CHud::RenderWorldNumber()
{
	float start_x = GetLeft() + 44;
	float start_y = GetTop() + 7;

	RenderNumber(CGameData::GetInstance()->GetWorld(), start_x, start_y);
}

void CHud::RenderPlayerCoin()
{
	float start_x = GetLeft() + 139;
	float start_y = GetTop() + 6;

	RenderNumber(CGameData::GetInstance()->GetCoin(), start_x, start_y);
}

int CHud::GetAniIdNumber(char number)
{
	switch (number)
	{
	case '0':
		return ID_ANI_NUMBER_0;
	case '1':
		return ID_ANI_NUMBER_1;
	case '2':
		return ID_ANI_NUMBER_2;
	case '3':
		return ID_ANI_NUMBER_3;
	case '4':
		return ID_ANI_NUMBER_4;
	case '5':
		return ID_ANI_NUMBER_5;
	case '6':
		return ID_ANI_NUMBER_6;
	case '7':
		return ID_ANI_NUMBER_7;
	case '8':
		return ID_ANI_NUMBER_8;
	case '9':
		return ID_ANI_NUMBER_9;
	default:
		return -1;
	}
}

int CHud::GetAniIdNumber(int number)
{
	switch (number)
	{
	case 0:
		return ID_ANI_NUMBER_0;
	case 1:
		return ID_ANI_NUMBER_1;
	case 2:
		return ID_ANI_NUMBER_2;
	case 3:
		return ID_ANI_NUMBER_3;
	case 4:
		return ID_ANI_NUMBER_4;
	case 5:
		return ID_ANI_NUMBER_5;
	case 6:
		return ID_ANI_NUMBER_6;
	case 7:
		return ID_ANI_NUMBER_7;
	case 8:
		return ID_ANI_NUMBER_8;
	case 9:
		return ID_ANI_NUMBER_9;
	default:
		return -1;
	}
}

void CHud::RenderNumber(int number, float left, float top, int min_char)
{
	string str = to_string(number);

	while (str.length() < min_char)
		str = "0" + str;

	for (int i = 0; i < str.length(); i++)
	{
		int ani_id = GetAniIdNumber(str[i]);
		if (ani_id != -1)
			CAnimations::GetInstance()->Get(ani_id)->Render(left + i * (HUD_NUMBER_BBOX_WIDTH + 1), top + HUD_NUMBER_BBOX_HEIGHT / 2);
	}
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
	//CAnimations::GetInstance()->Get(ID_ANI_HUD_BACKGROUND)->Render(x, y);
	RenderHudBackground();
	RenderArrowPower();
	RenderMarioRemainingLife();
	RenderPlayerPoint();
	RenderPlayerCoin();
	RenderWorldNumber();
}

void CHud::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - HUD_BACKGROUND_BBOX_WIDTH / 2;
	top = y - HUD_BACKGROUND_BBOX_HEIGHT / 2;
	right = left + HUD_BACKGROUND_BBOX_WIDTH;
	bottom = top + HUD_BACKGROUND_BBOX_HEIGHT;
}