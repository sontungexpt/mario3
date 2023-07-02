#pragma once
#include "Game.h"
#include "GameData.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "scenes/PlayScene.h"
#include "objects/GameObject.h"
#include "objects/materials/Portal.h"
#include "configs/materials/Door105000.h"
#include "objects/materials/EffectManager.h"

#include "configs/Effect.h"

class CDoor : public CPortal
{
private:

	int door_level;
	BOOLEAN is_want_entry;

	ULONGLONG entry_door_time_start;
	ULONGLONG castle_help_time_start;

public:
	CDoor(float x, float y, int scene_id, int door_level) : CPortal(x, y, x + DOOR_BBOX_WIDTH, y + DOOR_BBOX_HEIGHT, scene_id)
	{
		this->door_level = door_level;
		is_want_entry = FALSE;
		entry_door_time_start = 0;
		castle_help_time_start = 0;
		if (door_level == DOOR_LEVEL_CASTLE)
			CEffectManager::Gennerate(
				GetRight() + HELP_LEVEL_MAP_BBOX_WIDTH / 2,
				GetTop() - HELP_LEVEL_MAP_BBOX_HEIGHT / 2,
				HELP_LEVEL_MAP,
				EFFECT_NONE
			);
	}

	BOOLEAN  IsPassed() { return CGameData::GetInstance()->GetMaxDoorLevelPassed() >= door_level; }

	void EnterDoor();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void Render();
};
