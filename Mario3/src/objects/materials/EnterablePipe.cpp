#include "EnterablePipe.h"
#include "GameData.h"

void CEnterablePipe::EnterHiddenMap()
{
	CGame* game = CGame::GetInstance();
	CGameData::GetInstance()->SetCurrentSceneId(scene_id);
	game->SetSwitchSceneWaitingTime(500);
	game->InitiateSwitchScene(scene_id);
}