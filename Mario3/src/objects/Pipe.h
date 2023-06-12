#pragma once

#include "GameObject.h"
#include "configs/Pipe.h"

class CPipe : public CGameObject
{
protected:
	int plant_type;

public:
	CPipe(float x, float y) : CGameObject(x, y) {};

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
