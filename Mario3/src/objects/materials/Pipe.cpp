#include "Pipe.h"
#include "debug.h"
#include "scenes/PlayScene.h"

void CPipe::Render()
{
	if (!IsInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	switch (state)
	{
	case PIPE_STATE_SHORT:
		aniId = ID_ANI_PIPE_SHORT;
		break;
	case PIPE_STATE_LONG:
		aniId = ID_ANI_PIPE_LONG;
		break;
	default:
		DebugOut(L"[ERROR] No animation found CPipe::Render");
		return; // not in any animation
	}

	animations->Get(aniId)->Render(x, y);
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	switch (state)
	{
	case PIPE_STATE_SHORT:
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT_SHORT / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT_SHORT;
		break;
	case PIPE_STATE_LONG:
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT_LONG / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT_LONG;
		break;
	default:
		DebugOut(L"[ERROR FROM PIPE CLASS] No bounding box found");
		break;
	}
}