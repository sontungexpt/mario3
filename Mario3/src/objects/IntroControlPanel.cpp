#include "IntroControlPanel.h"
#include "GameData.h"
#include "Game.h"
#include "configs/core/SceneIds.h"
#include "DrawingManager.h"

void CIntroControlPanel::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
}

void CIntroControlPanel::SetState(int state)
{
}

void CIntroControlPanel::HandleChoice()
{
	switch (current_choice_index)
	{
	case 0: // continues
	{
		CGame* game = CGame::GetInstance();
		game->InitiateSwitchScene(ID_LEVEL_MAP_SCENE);
		CGameData::GetInstance()->CreateNewGame();
	}
	break;
	default:
		DebugOut(L"[ERROR] GameOverControlPanel::HandleChoice current_choice_index is invalid\n");
		break;
	}
}

void CIntroControlPanel::MoveSelectionDown()
{
	current_choice_index++;
	if (current_choice_index >= choices.size())
		current_choice_index = 0;
}

void CIntroControlPanel::MoveSelectionUp()
{
	if (current_choice_index > 0)
		current_choice_index--;
	else
		current_choice_index = choices.size() - 1;
}

void CIntroControlPanel::Render()
{
	for (unsigned int i = 0; i < choices.size(); i++)
	{
		CDrawingManager::RenderString(
			choices[i],
			left_choice,
			top_choice + i * (HUD_CHAR_BBOX_HEIGHT + 8)
		);
	}

	CDrawingManager::RenderString("@ 1998", left_choice, top_choice + 2 * (HUD_CHAR_BBOX_HEIGHT + 8));

	CDrawingManager::RenderIcon(
		"RED ARROW",
		left_choice - 15,
		top_choice + current_choice_index * (HUD_CHAR_BBOX_HEIGHT + 8) + HUD_CHAR_BBOX_HEIGHT / 2
	);
}

void CIntroControlPanel::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - number_cell_width / 2 * HUD_FRAME_CELL_WIDTH;
	top = y - number_cell_height / 2 * HUD_FRAME_CELL_HEIGHT;
	right = left + number_cell_width * HUD_FRAME_CELL_WIDTH;
	bottom = top + number_cell_height * HUD_FRAME_CELL_HEIGHT;
}