#pragma once
#include "PlayScene.h"
#include "GameData.h"
#include "components/KeyboardHandler/LevelMapKeyEventHandler.h"

#define START_SPRITE_ID	1001500

class CLevelMapScene : public CPlayScene
{
private:
	float start_x;
	float start_y;

	void RenderStartPoint();
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_OBJECTS(string line) override;

public:

	CLevelMapScene(int id, LPCWSTR filePath) : CPlayScene(id, filePath)
	{
		start_x = 0;
		start_y = 0;
		key_handler = new CLevelMapKeyHandler(this);
	};
	void Render();

	void Update(DWORD dt);
	void SetPlayerStart(float x, float y) { start_x = x; start_y = y; }
};

typedef CLevelMapScene* LPLEVELMAPSCENE;
