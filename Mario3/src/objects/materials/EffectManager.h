#pragma once
#include "debug.h"
#include "objects/GameObject.h"
#include "Effect.h"
#include "configs/Effect.h"

using namespace std;

class CEffectManager
{
	static CEffectManager* instance;

public:
	CEffectManager() {}

	static CEffectManager* GetInstance();

	static LPGAMEOBJECT Gennerate(LPGAMEOBJECT ref_object, int type, float distance_from_top = 6);
	static LPGAMEOBJECT Gennerate(float ref_x, float ref_y, int type, int effect);
	static LPGAMEOBJECT GennerateChangeScene();
};
