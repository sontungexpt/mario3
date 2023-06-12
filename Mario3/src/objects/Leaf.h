#pragma once
#include "GameObject.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"

#define ID_ANI_LEAF_LEFT 11002
#define ID_ANI_LEAF_RIGHT 11003

#define	LEAF_WIDTH 10
#define LEAF_BBOX_WIDTH 18
#define LEAF_BBOX_HEIGHT 16
#define LEAF_STATE_FALL 100
#define LEAF_STATE_FLY 200

#define MAX_VY 0.02f
class CLeaf : public CGameObject
{
	float ax;
	float ay;
	bool isOutBrick;
	bool isOnPlatForm;
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	CLeaf(float x, float y, int state);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual bool IsItem() { return 1; }
};
