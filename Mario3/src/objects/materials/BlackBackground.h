#pragma once
#include "debug.h"
#include "objects/GameObject.h"

using namespace std;

class CBlackBackground : public CGameObject
{
	float length;
	float height;

public:
	CBlackBackground(float x, float y, float length, float height) : CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	void Render();

	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
};