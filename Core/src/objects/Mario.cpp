#include "Mario.h"

namespace core {
	void Mario::Update(DWORD dt)
	{
		x_ += vx_ * dt;
		y_ += vy_ * dt;

		// simple fall down
		vy_ += MARIO_GRAVITY * dt;

		vx_ += ax_ * dt;

		if (abs(vx_) > abs(maxvx_)) vx_ = maxvx_;

		DebugOutTitle(L"vx = %0.5f", vx_);

		// BAD & sinful platform collision handling, see next sample for correct collision handling
		if (y_ > GROUND_Y)
		{
			vy_ = 0; y_ = GROUND_Y;
		}

		// simple screen edge collision!!!
		if (vx_ > 0 && x_ > 290) x_ = 290;
		if (vx_ < 0 && x_ < 0) x_ = 0;
	}

	void Mario::Render()
	{
		Animations* animations = Animations::GetInstance();
		int aniId = -1;

		// Mario is still on air check, this will not work when Mario is just stand up
		if (y_ < GROUND_Y)
		{
			if (abs(ax_) == MARIO_ACCEL_RUN_X) // TODO: need to optimize this
			{
				if (navx_ >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (navx_ >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
			if (is_sitting_)
			{
				if (navx_ > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx_ == 0)
				{
					if (navx_ > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx_ > 0)
				{
					if (ax_ < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax_ == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax_ == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax_ > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax_ == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax_ == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}

		if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

		float d = 0;
		if (is_sitting_) d = MARIO_SIT_HEIGHT_ADJUST;

		animations->Get(aniId)->Render(x_, y_ + d);
	}

	void Mario::SetState(int state)
	{
		switch (state)
		{
		case MARIO_STATE_RUNNING_RIGHT:
			if (is_sitting_) break;
			maxvx_ = MARIO_RUNNING_SPEED;
			ax_ = MARIO_ACCEL_RUN_X;
			navx_ = 1;
			break;
		case MARIO_STATE_RUNNING_LEFT:
			if (is_sitting_) break;
			maxvx_ = -MARIO_RUNNING_SPEED;
			ax_ = -MARIO_ACCEL_RUN_X;
			navx_ = -1;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			if (is_sitting_) break;
			maxvx_ = MARIO_WALKING_SPEED;
			ax_ = MARIO_ACCEL_WALK_X;
			navx_ = 1;
			break;
		case MARIO_STATE_WALKING_LEFT:
			if (is_sitting_) break;
			maxvx_ = -MARIO_WALKING_SPEED;
			ax_ = -MARIO_ACCEL_WALK_X;
			navx_ = -1;
			break;
		case MARIO_STATE_JUMP:
			if (is_sitting_) break;
			if (y_ == GROUND_Y)
			{
				if (abs(this->vx_) == MARIO_RUNNING_SPEED)
					vy_ = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy_ = -MARIO_JUMP_SPEED_Y;
			}
			break;

		case MARIO_STATE_RELEASE_JUMP:
			if (vy_ < 0) vy_ += MARIO_JUMP_SPEED_Y / 2;
			break;

		case MARIO_STATE_SIT:
			if (y_ == GROUND_Y)
			{
				state = MARIO_STATE_IDLE;
				is_sitting_ = true;
				vx_ = 0; vy_ = 0;
				//y += MARIO_SIT_HEIGHT_ADJUST;
			}
			break;

		case MARIO_STATE_SIT_RELEASE:
			is_sitting_ = false;
			state = MARIO_STATE_IDLE;
			//y -= MARIO_SIT_HEIGHT_ADJUST;
			break;

		case MARIO_STATE_IDLE:
			ax_ = 0.0f;
			vx_ = 0.0f;
			break;
		}

		GameObject::SetState(state);
	}
}