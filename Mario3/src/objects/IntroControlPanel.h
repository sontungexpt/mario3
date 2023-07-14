#pragma once
#include <string>
#include <iostream>
#include "GameObject.h"
#include "configs/materials/Hud103000.h"

using namespace std;

class CIntroControlPanel : public CGameObject
{
	size_t current_choice_index;
	vector<string> choices =
	{
		"1_PLAYER_GAME",
		"2_PLAYER_GAME"
	};

	int number_cell_width = 8;
	int number_cell_height = 4;

	// default position of the panel
	// can't be changed
	float left;
	float top;
	float left_choice;
	float top_choice;

public:
	CIntroControlPanel(float x, float y) :
		CGameObject(x, y)
	{
		current_choice_index = 0;
		left = x - number_cell_width / 2.0f * HUD_FRAME_CELL_WIDTH;
		top = y - number_cell_height / 2.0f * HUD_FRAME_CELL_HEIGHT;
		left_choice = left + 20;
		top_choice = top + 2;
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

typedef CIntroControlPanel* LPINTRO_CONTROL_PANEL;