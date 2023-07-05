#pragma once
#include "scenes/PlayScene.h"
#include "objects/GameObject.h"

#include "objects/monsters/plants/PlantShooter.h"
#include "objects/monsters/plants/CarnivorousPlant.h"

#include "configs/materials/Pipe101000.h"

class CPipe : public CGameObject
{
protected:
	CPlant* plant;
	int hidden_map_id;

	void CreatePlant(int plant_type);

public:
	CPipe(float x, float y, int state = PIPE_STATE_LONG, int plant_type = PIPE_PLANT_NOTHING, int hidden_map_id = INT_MAX) : CGameObject(x, y) {
		this->state = state;
		this->hidden_map_id = hidden_map_id;
		plant = nullptr;
		CreatePlant(plant_type);
	};

	~CPipe()
	{
		if (plant)
			delete plant;
		plant = nullptr;
	}

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; }

	void Render();
	//void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	CPlant* GetPlant() { return plant; }
	BOOLEAN CanEnterHiddenMap() { return hidden_map_id != INT_MAX; }
	void EnterHiddenMap();
};

typedef CPipe* LPPIPE;
