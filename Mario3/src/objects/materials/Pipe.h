#pragma once

#include "objects/GameObject.h"
#include "configs/Pipe110000.h"

class CPipe : public CGameObject
{
protected:
	int plant_type;

public:
	CPipe(float x, float y) : CGameObject(x, y) {
		state = PIPE_SHORT_STATE;
	};

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};