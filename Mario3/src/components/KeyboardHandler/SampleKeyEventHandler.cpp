#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "objects/Mario.h"
#include "scenes/PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
		CGame::GetInstance()->TogglePause();

	// disable control key when pause game
	if (CGame::GetInstance()->IsPaused())
		return;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		DebugOut(L"keydown");
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TAIL_SUIT);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		mario->WantHoldKoopa();
		break;
	case DIK_R: // reset
		//Reload();
		break;
	default:
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	// disable control key when pause game
	if (CGame::GetInstance()->IsPaused())
		return;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->WantKickKoopa();
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	// disable control key when pause game
	if (CGame::GetInstance()->IsPaused())
		return;

	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			mario->StartPowerUp();
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
			mario->StartPowerUp();
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
	}
}