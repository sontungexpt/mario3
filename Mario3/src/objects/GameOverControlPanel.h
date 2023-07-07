#pragma once
#include <string>
#include <iostream>
#include "GameObject.h"
#include "configs/GameOverControlPanel.h"
#include "configs/materials/Hud103000.h"

using namespace std;

class GameOverControlPanel : public CGameObject
{
	size_t current_choice_index;
	vector<string> choices =
	{
		"CONTINUE",
		"END"
	};

	int number_cell_width = 8;
	int number_cell_height = 4;

	// default position of the panel
	// can't be changed
	float left;
	float top;
	float left_choice;
	float top_choice;

	ULONGLONG create_time_start;

	BOOLEAN is_ready_to_show_mario;
	BOOLEAN is_ready_to_control;

public:
	GameOverControlPanel(float x, float y) : CGameObject(x, y)
	{
		left_choice = 0;
		top_choice = 0;
		current_choice_index = 0;
		is_ready_to_show_mario = FALSE;
		is_ready_to_control = FALSE;
		create_time_start = GetTickCount64();

		left = x - number_cell_width / 2.0f * HUD_FRAME_CELL_WIDTH;
		top = y - number_cell_height / 2.0f * HUD_FRAME_CELL_HEIGHT;
		left_choice = left + 50;
		top_choice = top + 28;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }

	void SetCurrentChoiceIndex(int index) { current_choice_index = index; }
	size_t GetCurrentChoiceIndex() { return current_choice_index; }

	void HandleChoice();
	void MoveSelectionDown();
	void MoveSelectionUp();
};

typedef GameOverControlPanel* LPGAMEOVER_CONTROL_PANEL;