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

	static void Gennerate(LPGAMEOBJECT ref_object, int type, float distance_from_top = 6);
	static void GennerateChangeScene();
};
