#include "CarnivorousPlant.h"
#include "debug.h"

void CCarnivorousPlant::Render()
{
	if (is_deleted) return; // notthing to render

	int aniId = -1;
	switch (state)
	{
	case PLANT_STATE_DOWN:
	case PLANT_STATE_UP:
		aniId = CARNIVOROUS_PLANT_ANI_OPEN_CLOSE_MOUSE;
		break;
	default:
		DebugOut(L"[ERROR] Unhandled state %d at CCarnivorousPlant::Render\n", state);
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CCarnivorousPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (is_deleted) return; // notthing to get

	left = x - CARNIVOROUS_PLANT_BBOX_WIDTH / 2;
	top = y - CARNIVOROUS_PLANT_BBOX_HEIGHT / 2;
	right = left + CARNIVOROUS_PLANT_BBOX_WIDTH;
	bottom = top + CARNIVOROUS_PLANT_BBOX_HEIGHT;
}