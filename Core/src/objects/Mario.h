#pragma once
#ifndef _MARIO_h
#define _MARIO_h

#include "configs/mario.h"

#include "GameObject.h"
#include "Game.h"

namespace core {
	class Mario : public GameObject
	{
	private:
		bool is_sitting;
		float vx_;
		float vy_;

	public:

		Mario(float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f, LPTEXTURE texture = nullptr)
			: GameObject(x, y, texture), vx_(vx), vy_(vy) {}

		~Mario() {}

		void Update(DWORD dt);
		void Render();
	};
}

#endif // !_MARIO_h
