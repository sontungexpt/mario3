#pragma once

#include "components/Scene/Scene.h"

class CLevelMapKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CLevelMapKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};