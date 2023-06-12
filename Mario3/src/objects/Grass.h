#pragma once
#include "GameObject.h"

class CGrass : public CGameObject
{
public:
	CGrass(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
