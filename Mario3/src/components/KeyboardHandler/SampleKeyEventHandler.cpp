#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "objects/Mario.h"
#include "objects/materials/EnterablePipe.h"

#include "scenes/PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	LPGAME game = CGame::GetInstance();

	if (KeyCode == DIK_ESCAPE || KeyCode == DIK_W)
		game->TogglePause();

	// disable control key when pause game
	if (game->IsPaused())
		return;
	if (game->IsInTransitionScene())
		return;

	CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();
	if (!mario) return;

	switch (KeyCode)
	{
	case DIK_UP:
		if (dynamic_cast<LPENTERABLE_PIPE>(mario->GetPipe()))
		{
			if (mario->GetPipe()->GetDirection() == PIPE_DIRECTION_DOWN)
			{
				mario->SetState(MARIO_STATE_ENTER_PIPE);
			}
		}
		break;
	case DIK_DOWN:
		if (dynamic_cast<LPENTERABLE_PIPE>(mario->GetPipe()))
		{
			if (mario->GetPipe()->GetDirection() == PIPE_DIRECTION_UP)
			{
				mario->SetState(MARIO_STATE_ENTER_PIPE);
			}
		}
		else
			mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
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
	case DIK_8:
		game->InitiateSwitchScene(-1);
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
	LPGAME game = CGame::GetInstance();

	if (game->IsPaused())
		return;
	if (game->IsInTransitionScene())
		return;

	CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();
	if (!mario) return;

	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		if (mario->IsEnteringPipe()) break;
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
	LPGAME game = CGame::GetInstance();

	if (game->IsPaused())
		return;
	if (game->IsInTransitionScene())
		return;
	CMario* mario = (CMario*)((LPPLAYSCENE)game->GetCurrentScene())->GetPlayer();
	if (!mario) return;

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->StartPowerUp();
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
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
			mario->StartPowerUp();
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
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