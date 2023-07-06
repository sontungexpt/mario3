#pragma once
#include "PlayScene.h"
#include "GameData.h"
#include "objects/GameOverControlPanel.h"
#include "components/KeyboardHandler/LevelMapKeyEventHandler.h"

class CLevelMapScene : public CPlayScene
{
private:
	float start_x;
	float start_y;

	LPGAMEOVER_CONTROL_PANEL game_over_control_panel;

	// to make the player move from the losed door to the previous door
	float prev_door_x;
	float prev_door_y;

	void RenderStartPoint();
	void _ParseSection_SETTINGS(string line);
	int CreatePlayer(float x, float y);
	void _ParseSection_OBJECTS(string line) override;

public:

	CLevelMapScene(int id, LPCWSTR filePath) : CPlayScene(id, filePath)
	{
		start_x = 0;
		start_y = 0;
		prev_door_x = 0;
		prev_door_y = 0;
		game_over_control_panel = nullptr;
		key_handler = new CLevelMapKeyHandler(this);
	};
	void Render();
	void UpdateGameOverPanel(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void RenderGameOverPanel();
	void Update(DWORD dt);
	void SetPlayerStartPos(float x, float y)
	{
		start_x = x;
		start_y = y;
	}
};

typedef CLevelMapScene* LPLEVELMAPSCENE;
