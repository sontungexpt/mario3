#include "Door.h"
#include "debug.h"
#include "Game.h"
#include "configs/GameData.h"

void CDoor::Render() {
	int aniId = ID_ANI_DOOR_0;
	CAnimations* animations = CAnimations::GetInstance();

	if (scene_id > 0) {
		switch (state) {
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
		case DOOR_LEVEl_0:
			aniId = ID_ANI_DOOR_0;
			break;
		default:
			break;
		}
	}
	else aniId = ID_ANI_DOOR_PASS;

	LPANIMATION ani = animations->Get(aniId);

	if (ani != nullptr)
		ani->Render(x, y);
	else
		DebugOut(L"can not render animation", aniId);
};