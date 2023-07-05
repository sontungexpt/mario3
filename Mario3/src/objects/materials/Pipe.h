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
	int direction;
	int color;

	virtual void CreatePlant(int plant_type);
	virtual int GetAniIdGreenPipe();
	virtual int GetAniIdBlackPipe();

public:
	CPipe(
		float x,
		float y,
		int state = PIPE_STATE_LONG,
		int plant_type = PIPE_PLANT_NOTHING,
		int direction = PIPE_DIRECTION_UP,
		int color = PIPE_COLOR_GREEN
	) : CGameObject(x, y) {
		this->direction = direction;
		this->color = color;
		this->state = state;
		plant = nullptr;
		CreatePlant(plant_type);
	};

	~CPipe()
	{
		if (plant)
			delete plant;
		plant = nullptr;
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }

	int GetDirection() { return direction; }
	int GetColor() { return color; }

	virtual void Render();
	//void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual CPlant* GetPlant() { return plant; }
	virtual void SetPlant(CPlant* plant) { this->plant = plant; }
};

typedef CPipe* LPPIPE;
