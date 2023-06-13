#pragma once
#include "objects/GameObject.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "configs/All.h"
#include "debug.h"
#include "configs/Mushroom120000.h"

class CMushRoom : public CGameObject {
	float ax;
	float ay;
	float start_y;
	//int model;

public:
	CMushRoom(float x, float y);
	void Render();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual int IsCollidable() { return 1; }

	void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	virtual bool IsItem() { return 1; }
};
