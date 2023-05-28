#include "Coin.h"

namespace core {
	void Coin::Render()
	{
		Animations* animations = Animations::GetInstance();
		animations->Get(ID_ANI_COIN)->Render(x_, y_);

		RenderBoundingBox();
	}

	void Coin::GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x_ - COIN_BBOX_WIDTH / 2;
		top = y_ - COIN_BBOX_HEIGHT / 2;
		right = left + COIN_BBOX_WIDTH;
		bottom = top + COIN_BBOX_HEIGHT;
	}
}