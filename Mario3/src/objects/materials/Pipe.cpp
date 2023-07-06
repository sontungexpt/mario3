#include "Pipe.h"
#include "debug.h"
#include "scenes/PlayScene.h"
#include <GameData.h>

void CPipe::CreatePlant(int plant_type)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float plant_x = x;
	// y + 1 to make plant y alway > pipe y then it will never be collide with pipe and it can move down
	float plant_y;

	switch (plant_type)
	{
	case PIPE_PLANT_NOTHING:
		return;
	case PIPE_PLANT_SHOOTER_RED:
		plant_y = y - (GetHeight() - PLANT_SHOOTER_BBOX_HEIGHT_RED) / 2 + 1;
		plant = (CPlantShooter*)scene->AddObject(new CPlantShooter(plant_x, plant_y, PLANT_STATE_DOWN, PLANT_SHOOTER_RED));
		break;
	case PIPE_PLANT_SHOOTER_GREEN:
		plant_y = y - (GetHeight() - PLANT_SHOOTER_BBOX_HEIGHT_GREEN) / 2 + 1;
		plant = (CPlantShooter*)scene->AddObject(new CPlantShooter(plant_x, plant_y, PLANT_STATE_DOWN, PLANT_SHOOTER_GREEN));
		break;
	case PIPE_PLANT_CARNIVOROUS:
		plant_y = y - (GetHeight() - CARNIVOROUS_PLANT_BBOX_HEIGHT) / 2 + 1;
		plant = (CCarnivorousPlant*)scene->AddObject(new CCarnivorousPlant(plant_x, plant_y, PLANT_STATE_DOWN));
		break;
	default:
		plant = nullptr;
		return;
	}
	if (plant)
		plant->SetMaxY(GetBottom() - plant->GetHeight() / 2);
}

int CPipe::GetAniIdGreenPipe()
{
	if (state == PIPE_STATE_SHORT)
	{
		if (direction == PIPE_DIRECTION_UP)
		{
			return ID_ANI_PIPE_SHORT_GREEN_UP;
		}
		else if (direction == PIPE_DIRECTION_DOWN)
		{
			return -1; // not implement yet
		}
	}
	else if (state = PIPE_STATE_LONG)
	{
		if (direction == PIPE_DIRECTION_UP)
		{
			return ID_ANI_PIPE_LONG_GREEN_UP;
		}
		else if (direction == PIPE_DIRECTION_DOWN)
		{
			return -1; // not implement yet
		}
	}

	return -1;
}

int CPipe::GetAniIdBlackPipe()
{
	if (state == PIPE_STATE_SHORT)
	{
		if (direction == PIPE_DIRECTION_UP)
		{
			return -1; // not implement yet
		}
		else if (direction == PIPE_DIRECTION_DOWN)
		{
			return ID_ANI_PIPE_SHORT_BLACK_DOWN;
		}
	}
	else if (state = PIPE_STATE_LONG)
	{
		if (direction == PIPE_DIRECTION_UP)
		{
			return -1; // not implement yet
		}
		else if (direction == PIPE_DIRECTION_DOWN)
		{
			return -1; // not implement yet
		}
	}

	return -1;
}

void CPipe::Render()
{
	if (!IsInCamera()) return;
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	switch (color)
	{
	case PIPE_COLOR_GREEN:
		aniId = GetAniIdGreenPipe();
		break;
	case PIPE_COLOR_BLACK:
		aniId = GetAniIdBlackPipe();
		break;
	default:
		DebugOut(L"[ERROR FROM PIPE CLASS] No color found");
		return;
	}

	if (aniId == -1)
	{
		DebugOut(L"[ERROR FROM PIPE CLASS] No animation id found");
		return;
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