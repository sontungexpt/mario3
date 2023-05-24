#pragma onc

#include "GameObject.h"

//#include "Animation.h"
//#include "Animations.h"

#define MARIO_WIDTH 14

class Brick : public GameObject {
public:
	Brick(float x, float y) : GameObject(x, y) {}

	void Render();
	void Update(DWORD dt) {}
};
