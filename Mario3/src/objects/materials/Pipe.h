#pragma once
#include "scenes/PlayScene.h"
#include "objects/GameObject.h"

#include "objects/monsters/plants/PlantShooter.h"
#include "objects/monsters/plants/CarnivorousPlant.h"

#include "configs/materials/Pipe10100.h"

class CPipe : public CGameObject
{
protected:
	//int plant_type;
	CPlant* plant;

	void CreatePlant(int plant_type)
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		float plant_x = x;
		// y + 1 to make plant y alway > pipe y then it will never be collide with pipe and it can move down
		float plant_y;

		switch (plant_type)
		{
		case PLANT_NOTHING:
			return;
		case PLANT_SHOOTER:
			plant_y = y - (GetHeight() - PLANT_SHOOTER_BBOX_HEIGHT) / 2 + 1;
			plant = (CPlantShooter*)scene->AddObject(new CPlantShooter(plant_x, plant_y, PLANT_STATE_DOWN));
			break;
		case PLANT_CARNIVOROUS:
			plant_y = y - (GetHeight() - CARNIVOROUS_PLANT_BBOX_HEIGHT) / 2 + 1;
			plant = (CCarnivorousPlant*)scene->AddObject(new CCarnivorousPlant(plant_x, plant_y, PLANT_STATE_DOWN));
			break;
		default:
			return;
		}
	}

public:
	CPipe(float x, float y, int state = PIPE_STATE_LONG, int plant_type = PLANT_NOTHING) : CGameObject(x, y) {
		this->state = state;
		plant = nullptr;
		CreatePlant(plant_type);
	};
	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

	void Render();
	//void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
