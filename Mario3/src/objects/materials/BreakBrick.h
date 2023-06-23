#pragma once

#pragma once
#include "Brick.h"
#include "configs/materials/QuestionBrick100000.h"
#include "objects/items/Item.h"

class CBreakBrick : public CBrick
{
private:
	BOOLEAN is_breaked;

public:

	CBreakBrick(float x, float y) : CBrick(x, y)
	{
		is_breaked = FALSE;
	};

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void Render();
	void SetState(int state);

	// collision
	void OnNoCollision(DWORD dt);

	int IsCollidable() { return !is_breaked; };
	int IsBlocking() { return 1; };
};
