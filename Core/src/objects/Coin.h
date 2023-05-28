#pragma once
#ifndef _COIN_H_
#define _COIN_H_

#include "GameObject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "configs/coin.h"

using namespace coinrc;

namespace core {
	class Coin : public GameObject {
	public:
		Coin(float x, float y) : GameObject(x, y) {}
		void Render();
		void Update(DWORD dt) {}
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		int IsBlocking() { return 0; }
	};
}

#endif // !_COIN_H_
