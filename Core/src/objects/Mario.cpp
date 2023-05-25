#include "Mario.h"

namespace core {
	void Mario::Update(DWORD dt)
	{
		x_ += vx_ * dt;

		int back_buffer_width = Game::GetInstance()->GetBackBufferWidth();

		if (x_ <= 0 || x_ >= back_buffer_width - mariorc::MARIO_WIDTH) {
			vx_ = -vx_;

			if (x_ <= 0)
			{
				x_ = 0;
			}
			else if (x_ >= back_buffer_width - mariorc::MARIO_WIDTH)
			{
				x_ = (float)(back_buffer_width - mariorc::MARIO_WIDTH);
			}
		}
	}
}