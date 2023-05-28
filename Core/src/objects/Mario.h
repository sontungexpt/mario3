#pragma once
#ifndef _MARIO_H_
#define _MARIO_H_
#include <iostream>

#include "configs/id.h"
#include "configs/mario.h"

#include "components/Animation/Animations.h"
#include "GameObject.h"
#include "Game.h"
#include "debug.h"

using namespace mariorc;
using namespace idrc;

namespace core {
	class Mario : public GameObject
	{
	private:
		bool is_sitting_;
		float maxvx_;
		float ax_;

	public:

		Mario(float x, float y) : GameObject(x, y)
		{
			is_sitting_ = false;
			maxvx_ = 0.0f;
			ax_ = 0.0f;
		}

		~Mario() {}

		void Update(DWORD dt);
		void Render();
		void SetState(int state);
	};
}

#endif // !_MARIO_H_
