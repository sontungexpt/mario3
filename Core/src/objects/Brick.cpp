#include "Brick.h"

namespace core {
	void Brick::Render()
	{
		Animations* animations = Animations::GetInstance();
		animations->Get(idrc::ID_ANI_BRICK)->Render(x_, y_);
	}
}