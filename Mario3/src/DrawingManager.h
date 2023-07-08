#pragma once
#include "configs/materials/Hud103000.h"
#include "configs/Mario.h"

#include <string>

using namespace std;

class CDrawingManager
{
	static int GetAniIdChar(char number);
	static int GetAniIdIcon(string icon);
	static int GetAniIdNumber(int number);

public:
	CDrawingManager() {}

	~CDrawingManager() {}

	static void RenderOverlay(float alpha = 0.6f);
	static void RenderBlackBackground(float x, float y, float length, float height);
	static void RenderBlueFrame(float x, float y, int number_cell_with, int number_cell_height);
	static void RenderIcon(string icon, float left, float top);
	static void RenderNumber(int number, float left, float top, int min_char = 0);
	static void RenderString(string str, float left, float top);
};

typedef CDrawingManager* LPFONTMANAGER;