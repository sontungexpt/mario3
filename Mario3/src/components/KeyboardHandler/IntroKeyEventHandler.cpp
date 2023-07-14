#include "IntroKeyEventHandler.h"
#include "scenes/IntroScene.h"

void CIntroKeyHandler::KeyState(BYTE* states)
{
}

void CIntroKeyHandler::OnKeyDown(int KeyCode)
{
	LPINTRO_SCENE scene = dynamic_cast<LPINTRO_SCENE>(CGame::GetInstance()->GetCurrentScene());
	if (!scene) return;
	LPINTRO_CONTROL_PANEL intro_panel = scene->GetControlPanel();
	if (!intro_panel) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		intro_panel->MoveSelectionDown();
		break;
	case DIK_UP:
		intro_panel->MoveSelectionUp();
		break;
	case DIK_W:
		intro_panel->HandleChoice();
		break;
	default:
		break;
	}
}

void CIntroKeyHandler::OnKeyUp(int KeyCode)
{
}