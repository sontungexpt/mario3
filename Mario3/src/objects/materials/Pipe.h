#pragma once
#include "scenes/PlayScene.h"
#include "objects/GameObject.h"
#include "configs/materials/Pipe10100.h"
#include "objects/monsters/Plant.h"

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

			// create plant
			float plant_x = (x + GetWidth() / 2 - PLANT_BBOX_WIDTH / 2);
			float plant_y = y + 3;

			CPlant* plant = (CPlant*)scene->AddObject(new CPlant(plant_x, plant_y, PLANT_STATE_DOWN));
		}
	};

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
