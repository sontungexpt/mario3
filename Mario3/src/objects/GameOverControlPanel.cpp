#include "debug.h"
#include "GameOverControlPanel.h"
#include "GameData.h"
#include "configs/core/SceneIds.h"

void GameOverControlPanel::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!is_ready_to_show_mario && GetTickCount64() - create_time_start > TIME_TO_SHOW_MARIO)
	{
		is_ready_to_show_mario = TRUE;
	}
	if (!is_ready_to_control && GetTickCount64() - create_time_start > TIME_TO_SHOW_ARROW)
	{
		is_ready_to_control = TRUE;
	}
}

void GameOverControlPanel::SetState(int state)
{
}

void GameOverControlPanel::HandleChoice()
{
	switch (current_choice_index)
	{
	case 0: // continue
		CGameData::GetInstance()->CreateNewGame();
		break;
	case 1: // end
		CGameData::GetInstance()->ClearOldData();
		CGame::GetInstance()->InitiateSwitchScene(ID_INTRO_SCENE);
		break;
	default:
		DebugOut(L"[ERROR] GameOverControlPanel::HandleChoice current_choice_index is invalid\n");
		break;
	}
}

void GameOverControlPanel::MoveSelectionDown()
{
	if (!is_ready_to_control) return;

	current_choice_index++;
	if (current_choice_index >= choices.size())
		current_choice_index = 0;
}

void GameOverControlPanel::MoveSelectionUp()
{
	if (!is_ready_to_control) return;

	if (current_choice_index > 0)
		current_choice_index--;
	else
		current_choice_index = choices.size() - 1;
}

void GameOverControlPanel::Render()
{
	CDrawingManager::RenderOverlay(0.4f);

	CDrawingManager::RenderBlueFrame(x, y, number_cell_width, number_cell_height);

	CDrawingManager::RenderString("MARIO", left + 10, top + 2);
	CDrawingManager::RenderString("GAME OVER!", x - 10.0f / 2 * HUD_CHAR_BBOX_WIDTH, top + 14);

	if (is_ready_to_show_mario)
		CDrawingManager::RenderIcon("MARIO DIE", left + 16, top + 38);

	for (unsigned int i = 0; i < choices.size(); i++)
	{
		CDrawingManager::RenderString(
			choices[i],
			left_choice,
			top_choice + i * (HUD_CHAR_BBOX_HEIGHT + 2)
		);
	}

	if (is_ready_to_control)
	{
		CDrawingManager::RenderIcon(
			"RED ARROW",
			left_choice - 15,
			top_choice + current_choice_index * (HUD_CHAR_BBOX_HEIGHT + 2) + HUD_CHAR_BBOX_HEIGHT / 2
		);
	}
}

void GameOverControlPanel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - number_cell_width / 2 * HUD_FRAME_CELL_WIDTH;
	top = y - number_cell_height / 2 * HUD_FRAME_CELL_HEIGHT;
	right = left + number_cell_width * HUD_FRAME_CELL_WIDTH;
	bottom = top + number_cell_height * HUD_FRAME_CELL_HEIGHT;
}