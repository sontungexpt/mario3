#include "BreakableBrick.h"

void CBreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BREAKABLE_BRICK_BBOX_WIDTH / 2;
	top = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2;
	right = left + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = top + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
}

void CBreakableBrick::Render()
{
	if (!IsInCamera()) return; // lazy load

	//int aniId = ID_ANI_BREAKABLE_BRICK;
}

void CBreakableBrick::SetState(int state)
{
}

void CBreakableBrick::OnNoCollision(DWORD dt)
{
}