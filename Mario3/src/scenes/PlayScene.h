#pragma once

#include "Game.h"
#include "components/Texture/Textures.h"
#include "components/Collision/Collision.h"
#include "components/Scene/Scene.h"
#include "objects/GameObject.h"

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right?
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;

	// this is the floor of screen
	// this mean it is the y of bottom of all objects
	// no object has y > this max_object_y
	LPGAMEOBJECT max_object_y;
	LPGAMEOBJECT max_object_x;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	virtual void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	void SetMaxCoordinate(LPGAMEOBJECT object)
	{
		if (max_object_x == nullptr && max_object_y == nullptr)
		{
			max_object_x = object;
			max_object_y = object;
			return;
		}

		if (object->GetRight() > max_object_x->GetRight())
			max_object_x = object;
		if (object->GetY() > max_object_y->GetY())
			max_object_y = object;
	}

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	LPGAMEOBJECT GetMaxObjectY() { return max_object_y; }
	LPGAMEOBJECT GetMaxObjectX() { return max_object_x; }

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	LPGAMEOBJECT AddObject(LPGAMEOBJECT obj);

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
