#pragma once
#ifndef _BRICK_H_
#define _BRICK_H_

#include "Gameobject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "configs/brick.h"
#include "configs/id.h"

using namespace brickrc;

namespace core {
	class Brick : public GameObject
	{
		Brick(float x, float y) : GameObject(x, y) {}
		void Render();
		void Update(DWORD dt) {}
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	};
}

#endif // !_BRICK_H_
