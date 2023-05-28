#include "Brick.h"

namespace core {
	void Brick::Render()
	{
		Animations* animations = Animations::GetInstance();
		animations->Get(idrc::ID_ANI_BRICK)->Render(x_, y_);
	}

	void Brick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x_ - BRICK_BBOX_WIDTH / 2;
		top = y_ - BRICK_BBOX_HEIGHT / 2;
		right = left + BRICK_BBOX_WIDTH;
		bottom = top + BRICK_BBOX_HEIGHT;
	}
}