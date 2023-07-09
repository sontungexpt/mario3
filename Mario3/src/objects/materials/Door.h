#pragma once
#include "Game.h"
#include "GameData.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "objects/materials/Portal.h"
#include "objects/materials/EffectManager.h"

#include "configs/materials/Door105000.h"
#include "configs/Effect.h"

class CDoor : public CPortal
{
private:

	int door_level;

public:
	CDoor(float x, float y, int scene_id, int door_level) :
		CPortal(x, y, x + DOOR_BBOX_WIDTH, y + DOOR_BBOX_HEIGHT, scene_id),
		door_level(door_level)
	{
		if (door_level == DOOR_LEVEL_CASTLE)
			CEffectManager::Gennerate(
				GetRight() + HELP_LEVEL_MAP_BBOX_WIDTH / 2,
				GetTop() - HELP_LEVEL_MAP_BBOX_HEIGHT / 2,
				HELP_LEVEL_MAP,
				EFFECT_NONE
			);
	}

	BOOLEAN  IsPassed()
	{
		return CGameData::GetInstance()->GetMaxDoorLevelPassed() >= door_level;
	}
	int GetDoorLevel() { return door_level; }
	void EnterDoor();
	void Render();
};
