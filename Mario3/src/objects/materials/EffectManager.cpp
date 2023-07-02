#include "EffectManager.h"
#include "scenes/PlayScene.h"

CEffectManager* CEffectManager::instance = nullptr;

CEffectManager* CEffectManager::GetInstance()
{
	if (instance == nullptr)
		instance = new CEffectManager();
	return instance;
}

LPGAMEOBJECT CEffectManager::Gennerate(LPGAMEOBJECT ref_object, int type, float distance_from_top)
{
	float ref_x = ref_object->GetX();
	float ref_y = 0.0f;
	switch (type)
	{
	case  POINT_100:
	case POINT_200:
	case POINT_400:
	case POINT_800:
	case POINT_1000:
	case POINT_2000:
	case POINT_4000:
	case POINT_8000:
	case LIFE_UP:
		ref_y = ref_object->GetTop() - POINT_BBOX_HEIGHT / 2 - distance_from_top;
		break;
	}

	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	return scene->AddObject(new CEffect(ref_x, ref_y, type));
}

LPGAMEOBJECT CEffectManager::Gennerate(float ref_x, float ref_y, int type, int effect)
{
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	return scene->AddObject(new CEffect(ref_x, ref_y, type, effect));
}

LPGAMEOBJECT CEffectManager::GennerateChangeScene()
{
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	float x = CGame::GetInstance()->GetCamXPos() + CGame::GetInstance()->GetBackBufferWidth() / 2;
	float y = CGame::GetInstance()->GetCamYPos() + CGame::GetInstance()->GetBackBufferHeight() / 2;

	return scene->AddObject(new CEffect(x, y, CHANGE_SCENE, EFFECT_CHANGE_SCREEN));
}