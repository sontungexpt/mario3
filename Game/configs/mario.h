#pragma once
#ifndef _MARIO_CONFIG_H_
#define _MARIO_CONFIG_H_

namespace configs {
	namespace mario {
		const float MARIO_VX = 0.1f;
		const float MARIO_WIDTH = 14.0f;

		const float MARIO_WALKING_SPEED = 0.1f;
		const float MARIO_RUNNING_SPEED = 0.2f;

		const float MARIO_ACCEL_WALK_X = 0.0005f;
		const float MARIO_ACCEL_RUN_X = 0.0007f;

		const float MARIO_JUMP_SPEED_Y = 0.5f;
		const float MARIO_JUMP_RUN_SPEED_Y = 0.6f;

		const float MARIO_GRAVITY = 0.002f;

		const float GROUND_Y = 160.0f;
		const float MARIO_SIT_HEIGHT_ADJUST = 4.0f;

		//state
		const int MARIO_STATE_IDLE = 0;
		const int MARIO_STATE_WALKING_RIGHT = 100;
		const int MARIO_STATE_WALKING_LEFT = 200;

		const int MARIO_STATE_JUMP = 300;
		const int MARIO_STATE_RELEASE_JUMP = 301;

		const int MARIO_STATE_RUNNING_RIGHT = 400;
		const int MARIO_STATE_RUNNING_LEFT = 500;

		const int MARIO_STATE_SIT = 600;
		const int MARIO_STATE_SIT_RELEASE = 601;
	}
}

namespace mariorc = configs::mario;

#endif // !_MARIO_CONFIG_H_