#pragma once
#include "PlayScene.h"

#include "components/KeyboardHandler/IntroKeyEventHandler.h"
#include <objects/IntroControlPanel.h>

class CIntroScene : public CPlayScene
{
private:

	LPINTRO_CONTROL_PANEL control_panel;

	float curtain_x;
	float curtain_y;

	void _ParseSection_OBJECTS(string line) override;

	void UpdateCamera();
	int UpdateControlPanel(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);

	void UpdateCurtain(DWORD dt);
	void RenderCurtain();

public:

	CIntroScene(int id, LPCWSTR filePath)
		: CPlayScene(id, filePath), curtain_x(0), curtain_y(0), control_panel(nullptr)
	{
		key_handler = new CIntroKeyHandler(this);
	};

	LPINTRO_CONTROL_PANEL GetControlPanel() { return control_panel; }
	void Render();
	void Update(DWORD dt);
	void Unload();
};

typedef CIntroScene* LPINTRO_SCENE;
