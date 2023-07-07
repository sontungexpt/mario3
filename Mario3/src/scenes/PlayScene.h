#pragma once
#include <chrono>
#include <thread>

#include "Game.h"
#include "components/Texture/Textures.h"
#include "components/Collision/Collision.h"
#include "components/Scene/Scene.h"
#include "objects/GameObject.h"
#include "objects/materials/Hud.h"
#include "objects/materials/Effect.h"

using namespace std;

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right?
	LPGAMEOBJECT player;
	LPHUD hud;

	vector<LPGAMEOBJECT> objects;
	CEffect* change_scene_effect;
	// save the id of hidden map to remove it when switch scene
	vector<int> hidden_map_ids;

	// this is the floor of screen
	// this mean it is the y of bottom of all objects
	// no object has y > this max_object_y
	LPGAMEOBJECT max_object_y;
	LPGAMEOBJECT max_object_x;

	virtual void _ParseSection_HIDDEN_MAPS(string line);
	virtual void ClearHiddenMaps();
	virtual void _ParseSection_SPRITES(string line);
	virtual void _ParseSection_ANIMATIONS(string line);

	virtual int CreatePlayer(float x, float y);

	virtual void _ParseSection_ASSETS(string line);
	virtual void _ParseSection_OBJECTS(string line);
	virtual void _ParseSection_SETTINGS(string line);

	virtual void LoadAssets(LPCWSTR assetFile);
	virtual void UpdateHud(DWORD dt, vector<LPGAMEOBJECT>* co_objects = nullptr);
	virtual void UpdateCamera();

	virtual void SetMaxCoordinate(LPGAMEOBJECT object)
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
	virtual void RenderChangeSceneEffect();
	LPGAMEOBJECT GetMaxObjectY() { return max_object_y; }
	LPGAMEOBJECT GetMaxObjectX() { return max_object_x; }

	virtual LPGAMEOBJECT GetPlayer() { return player; }

	virtual void Clear();
	virtual void PurgeDeletedObjects();
	LPGAMEOBJECT AddObject(LPGAMEOBJECT obj);

	LPGAMEOBJECT AddObjectToFirst(LPGAMEOBJECT obj);

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
