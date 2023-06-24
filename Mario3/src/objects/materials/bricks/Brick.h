#pragma once
#include "objects/GameObject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	virtual void Render() {};
	virtual void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
};