#pragma once
#include <string>

#include "GameObject.h"
#include "configs/GameOverControlPanel.h"
#include "configs/materials/Hud103000.h"

using namespace std;

class GameOverControlPanel : public CGameObject
{
	string choices[2] = { "CONTINUE", "END" };
	int current_choice_index = 0;

	int number_cell_width = 8;
	int number_cell_height = 4;

	float left;
	float top;

	ULONGLONG time_start;

	BOOLEAN is_ready_to_show_mario;
	BOOLEAN is_ready_to_control;

	float left_choice;
	float top_choice;

public:
	GameOverControlPanel(float x, float y) : CGameObject(x, y)
	{
		left_choice = 0;
		top_choice = 0;
		is_ready_to_show_mario = FALSE;
		is_ready_to_control = FALSE;
		left = x - number_cell_width / 2.0f * HUD_FRAME_CELL_WIDTH;
		top = y - number_cell_height / 2.0f * HUD_FRAME_CELL_HEIGHT;
		left_choice = left + 50;
		top_choice = top + 28;
		time_start = GetTickCount64();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void SetState(int state);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }

	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
typedef GameOverControlPanel* LPGAMEOVER_CONTROL_PANEL;