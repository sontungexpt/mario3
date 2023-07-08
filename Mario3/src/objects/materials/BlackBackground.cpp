#include "BlackBackground.h"
#include "objects/Mario.h"
#include "DrawingManager.h"

void CBlackBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	y = cy;
}

void CBlackBackground::Render()
{
	CDrawingManager::RenderBlackBackground(
		x,
		y,
		length,
		(float)CGame::GetInstance()->GetBackBufferHeight()
	);
}

void CBlackBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + length;
	bottom = y + CGame::GetInstance()->GetBackBufferHeight();
}