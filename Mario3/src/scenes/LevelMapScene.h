#pragma once
#include "PlayScene.h"
#include "objects/GameObject.h"
#include "components/Scene/Scene.h"

class CLevelMapScene : public CPlayScene
{
private:
	void _ParseSection_OBJECTS(string line) override;

public:
	CLevelMapScene(int id, LPCWSTR filePath) : CPlayScene(id, filePath) {};
};
