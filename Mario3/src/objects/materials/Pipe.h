#pragma once
#include "scenes/PlayScene.h"
#include "objects/GameObject.h"

#include "objects/monsters/Plant.h"
#include "configs/materials/Pipe10100.h"

class CPipe : public CGameObject
{
protected:
	int plant_type;

public:
	CPipe(float x, float y, int plant_type = PLANT_NOTHING) : CGameObject(x, y) {
		state = PIPE_SHORT_STATE;

		if (plant_type == PLANT_SHOOTER)
		{
			DebugOut(L"create plant");
			LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			//
			// y + 1 to make plant y alway > pipe y then it will never be collide with pipe and it can move down
			CPlant* plant = (CPlant*)scene->AddObject(new CPlant(x, y - (GetHeight() - PLANT_BBOX_HEIGHT) / 2 + 1, PLANT_STATE_DOWN));
		}
	};
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

	void Render();
	//void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
