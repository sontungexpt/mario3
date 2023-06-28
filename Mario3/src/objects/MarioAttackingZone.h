#pragma once

#include "debug.h"
#include "GameObject.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "configs/Mario.h"
#include "objects/monsters/Monster.h"
//#include "Mario.h"
//#include "scenes/PlayScene.h"

class CMarioAttackingZone : public CGameObject
{
	float width;
	float height;

	void OnCollisionWithMonster(LPCOLLISIONEVENT e);

public:
	CMarioAttackingZone(float x, float y, float width, float height) : CGameObject(x, y)
	{
		this->width = width;
		this->height = height;
	}

	/*CMarioAttackingZone(float width) : CGameObject()
	{
		this->width = width;
		CMario* mario = (CMario*)((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		x = mario->GetRight() + width / 2;
		y = mario->GetY();
	}*/

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render() {
		RenderBoundingBox();
	}
	void SetHeight(float height) { this->height = height; }
	void SetWidth(float width) { this->width = width; }

	void SetState(int state) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt) {};

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void OnCollisionWith(LPCOLLISIONEVENT e);
};