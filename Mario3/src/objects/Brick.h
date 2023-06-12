#pragma once

#include "GameObject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};