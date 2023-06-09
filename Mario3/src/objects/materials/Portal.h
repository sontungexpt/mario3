#pragma once

#include "objects/GameObject.h"

class CPortal : public CGameObject
{
protected:
	int scene_id;	// target scene to switch to

	float width;
	float height;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr) {};
	virtual void RenderBoundingBox(void);

	int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }
};