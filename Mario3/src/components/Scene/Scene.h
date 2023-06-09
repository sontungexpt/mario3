#pragma once

#include "components/KeyboardHandler/KeyEventHandler.h"

class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = nullptr;
	}

	int GetId() { return id; }
	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0; // each scene has its own load function
	virtual void Unload() = 0; // each scene has its own unload function
	virtual void Update(DWORD dt) = 0;	// each scene has its own update function
	virtual void Render() = 0; // each scene has its own render function
	virtual void RenderChangeSceneEffect() = 0;
};
typedef CScene* LPSCENE;

class CSceneKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;