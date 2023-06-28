#pragma once
#include "objects/GameObject.h"

class CHud : public CGameObject
{
public:
	CHud(float x, float y) : CGameObject(x, y) {}
	void Update(DWORD dt) {}
	void DrawNumber(int n, float xTemp, float yTemp);
	void DrawCard(int n, float xTemp, float yTemp);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};
