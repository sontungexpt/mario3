#include "Door.h"
#include "debug.h"
#include "configs/GameData.h"
#include "objects/MarioLevelMap.h"
#include "scenes/PlayScene.h"

void CDoor::EnterDoor()
{
	//CMarioLevelMap* mario = (CMarioLevelMap*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//if (mario)
	//{
	//	if (
	//		!mario->IsBypassDoorBlockRule() &&
	//		door_level - 1 != CGameData::GetInstance()->GetMaxDoorLevelPassed()
	//		)
	//		return;
	//}

	CGameData::GetInstance()->SetIsLostALife(FALSE);
	CGameData::GetInstance()->SetEntryDoorLevel(door_level);
	CGame::GetInstance()->InitiateSwitchScene(scene_id);
}

void CDoor::Render() {
	int aniId = -1;

	if (IsPassed())
	{
		aniId = ID_ANI_DOOR_PASSED;
	}
	else
	{
		switch (door_level) {
		case DOOR_LEVEL_1:
			aniId = ID_ANI_DOOR_1;
			break;
		case DOOR_LEVEL_2:
			aniId = ID_ANI_DOOR_2;
			break;
		case DOOR_LEVEL_3:
			aniId = ID_ANI_DOOR_3;
			break;
		case DOOR_LEVEL_4:
			aniId = ID_ANI_DOOR_4;
			break;
		case DOOR_LEVEL_5:
			aniId = ID_ANI_DOOR_5;
			break;
		case DOOR_LEVEL_6:
			aniId = ID_ANI_DOOR_6;
			break;
		case DOOR_LEVEL_CASTLE:
			aniId = ID_ANI_DOOR_CASTLE;
			break;
		default:
			break;
		}
	}

	if (aniId == -1) {
		DebugOut(L"[ERROR] Door::Render has no animation id\n");
		return;
	}

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);

	if (ani != nullptr)
		ani->Render(x, y);
};