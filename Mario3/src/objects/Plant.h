#pragma once
#include "GameObject.h"
#include "configs/Plant.h"

class CPlant : public CGameObject
{
protected:
	float startY;
	float minY;
	bool isShoot = false;
	int model;
	bool isUpping, isDowning;
	ULONGLONG time_out_pipe;
	ULONGLONG time_shoot;
	ULONGLONG time_down_pipe;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int PositionYWithMario(); //1 if mario on top plant, -1 if mario underplant
	int PositionXWithMario(); //1 if mario left to plant, -1 if mario right to plant

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual int IsEnemy() { return 1; }

	virtual void OnNoCollision(DWORD dt);

public:

	CPlant(float x, float y, int model);
	virtual void SetState(int state);
	void SetModel(int model) { this->model = model; }
	int GetModel() { return model; }
};
