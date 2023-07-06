#include "GameOverControlPanel.h"
#include "GameData.h"

void GameOverControlPanel::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!is_ready_to_show_mario && GetTickCount64() - time_start > TIME_TO_SHOW_MARIO)
	{
		is_ready_to_show_mario = TRUE;
	}
	if (!is_ready_to_control && GetTickCount64() - time_start > TIME_TO_SHOW_ARROW)
	{
		is_ready_to_control = TRUE;
	}
}

void GameOverControlPanel::SetState(int state)
{
	switch (state)
	{
	case GAME_OVER_CONTROL_PANEL_STATE_CONTINUE:
		CGameData::GetInstance()->CreateNewGame();
		break;
	case GAME_OVER_CONTROL_PANEL_STATE_END:
		break;
	}
}

void GameOverControlPanel::Render()
{
	CDrawingManager::RenderOverlay(0.4f);

	CDrawingManager::RenderBlueFrame(x, y, number_cell_width, number_cell_height);

	CDrawingManager::RenderString("MARIO", left + 10, top + 2);
	CDrawingManager::RenderString("GAME OVER!", x - 10.0f / 2 * HUD_CHAR_BBOX_WIDTH, top + 16);

	if (is_ready_to_show_mario)
		CDrawingManager::RenderIcon("MARIO DIE", left + 16, top + 40);

	CDrawingManager::RenderString("CONTINUE", left_choice, top_choice);
	CDrawingManager::RenderString("END", left_choice, top_choice + HUD_CHAR_BBOX_HEIGHT + 2);

	if (is_ready_to_control)
	{
		CDrawingManager::RenderIcon("RED ARROW", left_choice - 10, top_choice);
	}
}

void GameOverControlPanel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}