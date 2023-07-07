#include "GameOverControlPanelKeyEventHandler.h"
#include "Game.h"
#include "scenes/LevelMapScene.h"

void CGameOverControlPanelKeyEventHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
		CGame::GetInstance()->TogglePause();

	// disable control key when pause game
	if (CGame::GetInstance()->IsPaused())
		return;
	if (CGame::GetInstance()->IsInTransitionScene())
		return;

	LPLEVELMAPSCENE scene = (LPLEVELMAPSCENE)CGame::GetInstance()->GetCurrentScene();

	LPGAMEOVER_CONTROL_PANEL game_over_control_panel = scene->GetGameOverControlPanel();

	if (!game_over_control_panel) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		game_over_control_panel->MoveSelectionDown();
		break;
	case DIK_UP:
		game_over_control_panel->MoveSelectionUp();
		break;
	case DIK_W:
		game_over_control_panel->HandleChoice();
		break;
	default:
		break;
	}
}

void CGameOverControlPanelKeyEventHandler::KeyState(BYTE* states)
{
}

void CGameOverControlPanelKeyEventHandler::OnKeyUp(int KeyCode)
{
}