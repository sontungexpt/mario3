#pragma once
#include "PlayScene.h"
#include "GameData.h"
#include "objects/GameOverControlPanel.h"
#include "objects/materials/EffectManager.h"

#include "components/KeyboardHandler/GameOverControlPanelKeyEventHandler.h"
#include "components/KeyboardHandler/LevelMapKeyEventHandler.h"

class CLevelMapScene : public CPlayScene
{
private:
	CEffect* star_follow_mario_effect;
	BOOLEAN is_showed_follow_mario_effect;

	float start_x;
	float start_y;

	LPGAMEOVER_CONTROL_PANEL game_over_control_panel;

	// to make the player move from the losed door to the previous door
	float prev_door_x;
	float prev_door_y;

	void RenderStartPoint();
	void RenderNewGameDialog();

	int CreatePlayer(float x, float y);

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OBJECTS(string line) override;

	BOOLEAN IsShowNewGameDialog();

	int UpdateGameOverPanel(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	int UpdateShowNewGameDialog();
	void UpdateHud(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	void UpdateCamera();
	void SetPlayerStartPos(float x, float y)
	{
		start_x = x;
		start_y = y;
		prev_door_x = x;
		prev_door_y = y;
	}

public:

	CLevelMapScene(int id, LPCWSTR filePath) : CPlayScene(id, filePath)
	{
		SetPlayerStartPos(0, 0);
		game_over_control_panel = nullptr;
		star_follow_mario_effect = nullptr;
		is_showed_follow_mario_effect = FALSE;
		key_handler = new CLevelMapKeyHandler(this);
	};
	void Render();
	void Update(DWORD dt);
	void PurgeDeletedObjects();
	LPGAMEOBJECT AddObject(LPGAMEOBJECT obj);
	LPGAMEOBJECT AddObjectToFirst(LPGAMEOBJECT obj);

	LPGAMEOVER_CONTROL_PANEL GetGameOverControlPanel() { return game_over_control_panel; }
};

typedef CLevelMapScene* LPLEVELMAPSCENE;
