#pragma once
#include "PlayScene.h"

#include "components/KeyboardHandler/IntroKeyEventHandler.h"

class CIntroScene : public CPlayScene
{
private:
	float curtain_x;
	float curtain_y;

	void _ParseSection_OBJECTS(string line) override;

	void UpdateCamera();

	void UpdateCurtain(DWORD dt);
	void RenderCurtain();

public:

	CIntroScene(int id, LPCWSTR filePath)
		: CPlayScene(id, filePath), curtain_x(0), curtain_y(0)
	{
		key_handler = new CIntroKeyHandler(this);
	};

	void Render();
	void Update(DWORD dt);
	void Unload();
};

typedef CIntroScene* LPINTRO_SCENE;
