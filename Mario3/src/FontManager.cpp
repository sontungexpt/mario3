#include "FontManager.h"
#include "components/Animation/Animations.h"

int CFontManager::GetAniIdChar(char char_)
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
	default:
		return -1;
	}
}

int CFontManager::GetAniIdIcon(string icon)
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
	return -1;
}

int CFontManager::GetAniIdNumber(int number)
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

void CFontManager::RenderIcon(string icon, float left, float top)
{
	int ani_id = GetAniIdIcon(icon);
	if (ani_id != -1)
		CAnimations::GetInstance()->Get(ani_id)->Render(left, top);
}

void CFontManager::RenderNumber(int number, float left, float top, int min_char)
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

void CFontManager::RenderString(string str, float left, float top)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}

	for (int i = 0; i < str.length(); i++)
	{
		int ani_id = GetAniIdChar(str[i]);
		if (ani_id != -1)
			CAnimations::GetInstance()->Get(ani_id)->Render(left + i * (HUD_CHAR_BBOX_WIDTH), top + HUD_CHAR_BBOX_HEIGHT / 2);
	}
}