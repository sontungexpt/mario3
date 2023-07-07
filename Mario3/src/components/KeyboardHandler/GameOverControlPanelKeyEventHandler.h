#pragma once
#include "components/Scene/Scene.h"

class CGameOverControlPanelKeyEventHandler : public CSceneKeyHandler
{
public:

	void KeyState(BYTE* states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	CGameOverControlPanelKeyEventHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
