#include "Animations.h"

namespace core {
	Animations* Animations::instance = nullptr;

	Animations* Animations::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Animations();
		}
		return instance;
	}

	void Animations::Add(int id, LPANIMATION animation)
	{
		animations_[id] = animation;
	}

	LPANIMATION Animations::Get(int id)
	{
		return animations_[id];
	}
}