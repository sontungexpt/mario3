#pragma once
#include "PlayScene.h"
#include "GameData.h"
#include "components/KeyboardHandler/LevelMapKeyEventHandler.h"

class CLevelMapScene : public CPlayScene
{
private:
	float start_x;
	float start_y;

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
		key_handler = new CLevelMapKeyHandler(this);
	};
	void Render();

	void Update(DWORD dt);
	void SetPlayerStartPos(float x, float y)
	{
		start_x = x;
		start_y = y;
	}
};

typedef CLevelMapScene* LPLEVELMAPSCENE;
