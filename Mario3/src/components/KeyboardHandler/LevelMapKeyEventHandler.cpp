#include "LevelMapKeyEventHandler.h"
#include "Game.h"
#include "objects/MarioLevelMap.h"
#include "scenes/LevelMapScene.h"

void CLevelMapKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
		CGame::GetInstance()->TogglePause();

	// disable control key when pause game
	if (CGame::GetInstance()->IsPaused()) return;
	if (CGame::GetInstance()->IsInTransitionScene()) return;
	if (CGameData::GetInstance()->IsShowNewGameDialog()) return;

	CMarioLevelMap* mario = (CMarioLevelMap*)((LPLEVELMAPSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TAIL_SUIT);
		break;
	case DIK_4:
		mario->ToggleByPassBlock();
		break;
	case DIK_S:
		mario->EnterDoor();
		break;
	case DIK_A:

		break;
	case DIK_DOWN:
		mario->SetState(MARIO_LEVEL_MAP_STATE_MOVING_DOWN);
		break;
	case DIK_UP:
		mario->SetState(MARIO_LEVEL_MAP_STATE_MOVING_UP);
		break;
	case DIK_LEFT:
		mario->SetState(MARIO_LEVEL_MAP_STATE_MOVING_LEFT);
		break;
	case DIK_RIGHT:
		mario->SetState(MARIO_LEVEL_MAP_STATE_MOVING_RIGHT);
		break;
	default:
		break;
	}
}

void CLevelMapKeyHandler::OnKeyUp(int KeyCode)
{
}

void CLevelMapKeyHandler::KeyState(BYTE* states)
{
}