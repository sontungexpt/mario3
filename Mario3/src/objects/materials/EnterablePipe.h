#pragma once
#include "Pipe.h"

#include "configs/materials/Pipe101000.h"

class CEnterablePipe : public CPipe
{
protected:
	int scene_id;

public:
	CEnterablePipe(
		float x,
		float y,
		int state = PIPE_STATE_LONG,
		int plant_type = PIPE_PLANT_NOTHING,
		int direction = PIPE_DIRECTION_UP,
		int color = PIPE_COLOR_GREEN,
		int scene_id = INT_MAX
	) : CPipe(x, y, state, plant_type, direction, color), scene_id(scene_id)
	{};

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

	void PlayerEntered();
};

typedef CEnterablePipe* LPENTERABLE_PIPE;
