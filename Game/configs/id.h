#pragma once
#ifndef _ID_CONFIG_H_
#define _ID_CONFIG_H_

namespace configs {
	namespace id {
		// brick
		const int ID_ANI_BRICK = 10000;

		// mario
		const int ID_ANI_MARIO_IDLE_RIGHT = 400;
		const int ID_ANI_MARIO_IDLE_LEFT = 401;

		const int ID_ANI_MARIO_WALKING_RIGHT = 500;
		const int ID_ANI_MARIO_WALKING_LEFT = 501;

		const int ID_ANI_MARIO_RUNNING_RIGHT = 600;
		const int ID_ANI_MARIO_RUNNING_LEFT = 601;

		const int ID_ANI_MARIO_JUMP_WALK_RIGHT = 700;
		const int ID_ANI_MARIO_JUMP_WALK_LEFT = 701;

		const int ID_ANI_MARIO_JUMP_RUN_RIGHT = 800;
		const int ID_ANI_MARIO_JUMP_RUN_LEFT = 801;

		const int ID_ANI_MARIO_SIT_RIGHT = 900;
		const int ID_ANI_MARIO_SIT_LEFT = 901;

		const int ID_ANI_MARIO_BRACE_RIGHT = 1000;
		const int ID_ANI_MARIO_BRACE_LEFT = 1001;
	}
}

namespace idrc = configs::id;

#endif // !_ID_CONFIG_H_