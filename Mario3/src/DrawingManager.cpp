﻿#include "debug.h"

#include "DrawingManager.h"
#include "components/Texture/Textures.h"
#include "components/Animation/Animations.h"

#include "configs/GameObject.h"
#include <d3dx9.h>

int CDrawingManager::GetAniIdChar(char char_)
{
	switch (char_)
	{
	case '0':
		return ID_ANI_CHAR_0;
	case '1':
		return ID_ANI_CHAR_1;
	case '2':
		return ID_ANI_CHAR_2;
	case '3':
		return ID_ANI_CHAR_3;
	case '4':
		return ID_ANI_CHAR_4;
	case '5':
		return ID_ANI_CHAR_5;
	case '6':
		return ID_ANI_CHAR_6;
	case '7':
		return ID_ANI_CHAR_7;
	case '8':
		return ID_ANI_CHAR_8;
	case '9':
		return ID_ANI_CHAR_9;
		// continue from char a to z
	case 'A':
		return ID_ANI_CHAR_A;
	case 'B':
		return ID_ANI_CHAR_B;
	case 'C':
		return ID_ANI_CHAR_C;
	case 'D':
		return ID_ANI_CHAR_D;
	case 'E':
		return ID_ANI_CHAR_E;
	case 'F':
		return ID_ANI_CHAR_F;
	case 'G':
		return ID_ANI_CHAR_G;
	case 'H':
		return ID_ANI_CHAR_H;
	case 'I':
		return ID_ANI_CHAR_I;
	case 'J':
		return ID_ANI_CHAR_J;
	case 'K':
		return ID_ANI_CHAR_K;
	case 'L':
		return ID_ANI_CHAR_L;
	case 'M':
		return ID_ANI_CHAR_M;
	case 'N':
		return ID_ANI_CHAR_N;
	case 'O':
		return ID_ANI_CHAR_O;
	case 'P':
		return ID_ANI_CHAR_P;
	case 'Q':
		return ID_ANI_CHAR_Q;
	case 'R':
		return ID_ANI_CHAR_R;
	case 'S':
		return ID_ANI_CHAR_S;
	case 'T':
		return ID_ANI_CHAR_T;
	case 'U':
		return ID_ANI_CHAR_U;
	case 'V':
		return ID_ANI_CHAR_V;
	case 'W':
		return ID_ANI_CHAR_W;
	case 'X':
		return ID_ANI_CHAR_X;
	case 'Y':
		return ID_ANI_CHAR_Y;
	case 'Z':
		return ID_ANI_CHAR_Z;
	case '!':
		return ID_ANI_CHAR_EXCLAMATION;
	case '@':
		return ID_ANI_CHAR_SHACKLE;
	default:
		return -1;
	}
}

int CDrawingManager::GetAniIdIcon(string icon)
{
	for (int i = 0; i < icon.length(); i++)
	{
		icon[i] = toupper(icon[i]);
	}

	if (icon == "CLOCK")
		return ID_ANI_CLOCK_ICON;
	else if (icon == "DOLAR")
		return ID_ANI_DOLAR_ICON;
	else if (icon == "LIFE")
		return ID_ANI_LIFE_ICON;
	else if (icon == "X")
		return ID_ANI_X_ICON;
	else if (icon == "MARIO DIE")
		return ID_ANI_MARIO_DIE;
	else if (icon == "MARIO LEVEL DIALOG")
		return ID_ANI_MARIO_LEVEL_MAP_SMALL_FORWARD;
	else if (icon == "RED ARROW")
		return ID_ANI_RED_ARROW_ICON;

	return -1;
}

int CDrawingManager::GetAniIdNumber(int number)
{
	switch (number)
	{
	case 0:
		return ID_ANI_CHAR_0;
	case 1:
		return ID_ANI_CHAR_1;
	case 2:
		return ID_ANI_CHAR_2;
	case 3:
		return ID_ANI_CHAR_3;
	case 4:
		return ID_ANI_CHAR_4;
	case 5:
		return ID_ANI_CHAR_5;
	case 6:
		return ID_ANI_CHAR_6;
	case 7:
		return ID_ANI_CHAR_7;
	case 8:
		return ID_ANI_CHAR_8;
	case 9:
		return ID_ANI_CHAR_9;
	default:
		return -1;
	}
}

void CDrawingManager::RenderOverlay(float alpha)
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float x = cx + CGame::GetInstance()->GetBackBufferWidth() / 2;
	float y = cy + CGame::GetInstance()->GetBackBufferHeight() / 2;

	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX_BLACK);

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)CGame::GetInstance()->GetBackBufferWidth();
	rect.bottom = (int)CGame::GetInstance()->GetBackBufferHeight();

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, alpha);
}

void CDrawingManager::RenderBlackBackground(float x, float y, float length, float height)
{
	if (length <= 0 || height <= 0) return;
	float xx = x;
	float yy = y;

	while (yy < y + height)
	{
		xx = x;
		while (xx < x + length)
		{
			D3DXVECTOR3 p(xx, yy, 0);
			RECT rect;
			LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX_BLACK);

			rect.left = 0;
			rect.top = 0;
			rect.right = (int)HUD_FRAME_CELL_WIDTH;
			rect.bottom = (int)HUD_FRAME_CELL_HEIGHT;

			float cx, cy;
			CGame::GetInstance()->GetCamPos(cx, cy);

			CGame::GetInstance()->Draw(xx - cx + HUD_FRAME_CELL_WIDTH / 2, yy - cy + HUD_FRAME_CELL_HEIGHT / 2, bbox, &rect, 1.0f, rect.right, rect.bottom);
			xx += HUD_FRAME_CELL_WIDTH;
		}
		yy += HUD_FRAME_CELL_HEIGHT;
	}
}

void CDrawingManager::RenderBlueFrame(float x, float y, int number_cell_with, int number_cell_height)
{
	float left = x - number_cell_with / 2.0f * HUD_FRAME_CELL_WIDTH;
	float top = y - number_cell_height / 2.0f * HUD_FRAME_CELL_HEIGHT;
	if (number_cell_height < 2 || number_cell_with < 2)
	{
		DebugOut(L"[ERROR] RenderFrame: number_cell_with or number_cell_height must be greater than 1\n");
		return;
	}

	CAnimations* animations = CAnimations::GetInstance();
	for (int index_height = 0; index_height < number_cell_height; index_height++)
	{
		for (int index_width = 0; index_width < number_cell_with; index_width++)
		{
			float xx = left + index_width * HUD_FRAME_CELL_WIDTH;
			float yy = top + index_height * HUD_FRAME_CELL_HEIGHT;

			// first row
			if (index_height == 0)
			{
				if (index_width == 0)
					animations->Get(ID_ANI_TOP_LEFT_CORNER_ICON)->Render(xx, yy);
				else if (index_width == number_cell_with - 1)
					animations->Get(ID_ANI_TOP_RIGHT_CORNER_ICON)->Render(xx, yy);
				else
					animations->Get(ID_ANI_HORIZONTAL_TOP_EDGE_ICON)->Render(xx, yy);
			}
			else if (index_height == number_cell_height - 1)
			{
				if (index_width == 0)
					animations->Get(ID_ANI_BOTTOM_LEFT_CORNER_ICON)->Render(xx, yy);
				else if (index_width == number_cell_with - 1)
					animations->Get(ID_ANI_BOTTOM_RIGHT_CORNER_ICON)->Render(xx, yy);
				else
					animations->Get(ID_ANI_HORIZONTAL_BOTTOM_EDGE_ICON)->Render(xx, yy);
			}
			else
			{
				if (index_width == 0)
					animations->Get(ID_ANI_VERTICAL_LEFT_EDGE_ICON)->Render(xx, yy);
				else if (index_width == number_cell_with - 1)
					animations->Get(ID_ANI_VERTICAL_RIGHT_EDGE_ICON)->Render(xx, yy);
				else
					animations->Get(ID_ANI_COLOR_ICON_BLUE)->Render(xx, yy);
			}
		}
	}
}

void CDrawingManager::RenderIcon(string icon, float left, float top)
{
	int ani_id = GetAniIdIcon(icon);
	if (ani_id != -1)
		CAnimations::GetInstance()->Get(ani_id)->Render(left, top);
}

void CDrawingManager::RenderNumber(int number, float left, float top, int min_char)
{
	string str = to_string(number);

	while (str.length() < min_char)
		str = "0" + str;

	for (int i = 0; i < str.length(); i++)
	{
		int ani_id = GetAniIdChar(str[i]);
		if (ani_id != -1)
			CAnimations::GetInstance()->Get(ani_id)->Render(left + i * (HUD_CHAR_BBOX_WIDTH), top + HUD_CHAR_BBOX_HEIGHT / 2);
	}
}

void CDrawingManager::RenderString(string str, float left, float top)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}

	for (int i = 0; i < str.length(); i++)
	{
		int ani_id = GetAniIdChar(str[i]);
		if (ani_id != -1)
		{
			if (48 <= (int)str[i] && (int)str[i] <= 57)// number
				CAnimations::GetInstance()->Get(ani_id)->Render(left + i * (HUD_CHAR_BBOX_WIDTH), top + HUD_CHAR_BBOX_HEIGHT / 2 + 1);
			else
				CAnimations::GetInstance()->Get(ani_id)->Render(left + i * (HUD_CHAR_BBOX_WIDTH), top + HUD_CHAR_BBOX_HEIGHT / 2);
		}
	}
}