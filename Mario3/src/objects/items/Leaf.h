#pragma once
#include "debug.h"

#include "Item.h"
#include "components/Animation/Animations.h"
#include "configs/items/Leaf303000.h"

class CLeaf : public CItem
{
public:
	CLeaf(float x, float y) : CItem(x, y) {};
	CLeaf(float x, float y, int state) : CItem(x, y, state) {};

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
