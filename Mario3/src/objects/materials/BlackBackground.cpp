#include "BlackBackground.h"
#include "objects/Mario.h"
#include "DrawingManager.h"

void CBlackBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CBlackBackground::Render()
{
	CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario)
	{
		CDrawingManager::RenderBlackBackground(
			x,
			y,
			length,
			height
		);
	}
}

void CBlackBackground::SetState(int state)
{
}

void CBlackBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}