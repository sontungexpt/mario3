#pragma once

#include "Game.h"
#include "components/Texture/Textures.h"
#include "components/Scene/Scene.h"
#include "objects/GameObject.h"
#include "objects/materials/Brick.h"
#include "objects/Mario.h"
#include "objects/monsters/Goomba.h"
#include "components/Collision/Collision.h"

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right?
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	virtual void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	LPGAMEOBJECT AddObject(LPGAMEOBJECT obj);

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
