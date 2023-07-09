#pragma once
#include "debug.h"
#include "objects/GameObject.h"

using namespace std;

class CBlackBackground : public CGameObject
{
	float length;

public:
	CBlackBackground(float x, float y, float length)
		: CGameObject(x, y), length(length)
	{}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};