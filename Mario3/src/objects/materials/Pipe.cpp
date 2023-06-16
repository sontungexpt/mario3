#include "Pipe.h"
#include "objects/monsters/Plant.h"
#include "scenes/PlayScene.h"

void CPipe::Render()
{
	if (!IsInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == PIPE_SHORT_STATE) aniId = ID_ANI_PIPE_SHORT;
	if (state == PIPE_LONG_STATE) aniId = ID_ANI_PIPE_LONG;

	if (aniId == -1)
	{
		DebugOut(L"[ERROR FROM PIPE CLASS] No animation found");
		return; // not in any animation
	}
	animations->Get(aniId)->Render(x, y);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == PIPE_SHORT_STATE) {
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT_LONG / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT_LONG;
	}
}