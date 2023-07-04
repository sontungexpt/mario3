#pragma once
#include "PlayScene.h"
#include "GameData.h"
#include "components/KeyboardHandler/LevelMapKeyEventHandler.h"

class CHiddenMapScene : public CPlayScene
{
private:
	float start_x;
	float start_y;

	void _ParseSection_SETTINGS(string line);
	int CreatePlayer(float x, float y);
	void _ParseSection_OBJECTS(string line) override;

public:

	CHiddenMapScene(int id, LPCWSTR filePath) : CPlayScene(id, filePath)
	{
		start_x = 0;
		start_y = 0;
	};
	void Render();

	void Update(DWORD dt);
	void SetPlayerStartPos(float x, float y)
	{
		start_x = x;
		start_y = y;
	}
};

typedef CHiddenMapScene* LPHIDDENMAPSCENE;
