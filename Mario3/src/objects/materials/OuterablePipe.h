#pragma once
#include "Pipe.h"

#include "configs/materials/Pipe101000.h"
#include "GameData.h"

class COuterablePipe : public CPipe
{
protected:
	int scene_id;

public:
	COuterablePipe(
		float x,
		float y,
		int state = PIPE_STATE_LONG,
		int plant_type = PIPE_PLANT_NOTHING,
		int direction = PIPE_DIRECTION_UP,
		int color = PIPE_COLOR_GREEN,
		int scene_id = INT_MAX
	) : CPipe(x, y, state, plant_type, direction, color),
		scene_id(scene_id)
	{};

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

	BOOLEAN IsCurrentOutdoor()
	{
		CGameData* data = CGameData::GetInstance();
		return data->GetCurrentSceneId() != INT_MAX &&
			scene_id == data->GetCurrentSceneId();
	}
	void PlayerMovedOut();
};

typedef COuterablePipe* LPOUTERABLE_PIPE;
