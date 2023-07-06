#pragma once
#include <string>
#include "configs/materials/Hud103000.h"

using namespace std;

class CDrawingManager
{
	static int GetAniIdChar(char number);
	static int GetAniIdIcon(string icon);
	static int GetAniIdNumber(int number);

public:
	CDrawingManager()
	{
	}

	~CDrawingManager()
	{
	}

	static void RenderOverlay();
	static void RenderBlackBackground(float left, float top, int number_cell_with, int number_cell_height);
	static void RenderBlueFrame(float left, float top, int number_cell_with, int number_cell_height);
	static void RenderIcon(string icon, float left, float top);
	static void RenderNumber(int number, float left, float top, int min_char = 0);
	static void RenderString(string str, float left, float top);
};

typedef CDrawingManager* LPFONTMANAGER;