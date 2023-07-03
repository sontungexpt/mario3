#pragma once
#include <string>
#include "configs/materials/Hud103000.h"

using namespace std;

class CFontManager
{
	static int GetAniIdChar(char number);
	static int GetAniIdIcon(string icon);
	static int GetAniIdNumber(int number);

public:
	CFontManager()
	{
	}

	~CFontManager()
	{
	}

	static void RenderIcon(string icon, float left, float top);
	static void RenderNumber(int number, float left, float top, int min_char = 0);
	static void RenderString(string str, float left, float top);
};

typedef CFontManager* LPFONTMANAGER;