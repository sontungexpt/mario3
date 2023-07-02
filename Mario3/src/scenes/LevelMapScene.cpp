#include "LevelMapScene.h"
#include "utils/Utils.h"
#include "configs/core/ObjectTypes.h"

#include "objects/Mario.h"
#include "objects/MarioLevelMap.h"
#include "objects/Platform.h"
#include "objects/materials/Grass.h"
#include "objects/materials/Door.h"
#include "objects/materials/Effect.h"

#include "objects/monsters/Hammer.h"

void CLevelMapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = nullptr;

	switch (object_type)
	{
		//case OBJECT_TYPE_MARIO:
			//if (player != nullptr)
			//{
			//	DebugOut(L"[ERROR] MARIO object was created before!\n");
			//	return;
			//}
			//obj = new CMarioLevelMap(x, y);
			//player = (CMarioLevelMap*)obj;
			//DebugOut(L"[INFO] Player object has been created!\n");
		//break;
	case OBJECT_TYPE_GRASS:
		obj = new CGrass(x, y);
		break;
	case OBJECT_TYPE_DOOR:
	{
		int screen_id = atoi(tokens[3].c_str());
		int door_level = atoi(tokens[4].c_str());

		obj = new CDoor(x, y, screen_id, door_level);
	}
	break;
	case OBJECT_TYPE_HAMMER:
		obj = new CHammer(x, y);
		break;
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int is_blocking = 0;
		int is_colliable_all_direction = -1;

		if (tokens.size() >= 10)
		{
			is_blocking = atoi(tokens[9].c_str());
		}
		if (tokens.size() >= 11)
		{
			is_colliable_all_direction = atoi(tokens[10].c_str());
		}
		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			is_blocking, is_colliable_all_direction
		);
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	SetMaxCoordinate(obj);
	objects.push_back(obj);
}

void CLevelMapScene::RenderStartPoint()
{
	CAnimations::GetInstance()->Get(105050)->Render(start_x, start_y);
}
void CLevelMapScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start_position")
	{
		start_x = (float)atof(tokens[1].c_str());
		start_y = (float)atof(tokens[2].c_str());

		if (player != nullptr)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
		}
		else
		{
			CGameObject* obj = nullptr;
			obj = new CMarioLevelMap(start_x, start_y);
			player = (CMarioLevelMap*)obj;
			obj->SetPosition(start_x, start_y);
			objects.push_back(obj);
			DebugOut(L"[INFO] Player object has been created!\n");
		}
	}
	else
	{
		CPlayScene::_ParseSection_SETTINGS(line);
	}
}

void CLevelMapScene::Render()
{
	CEffect* effect_change_scene = nullptr;
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CMarioLevelMap*>(objects[i]))
			continue;
		if (dynamic_cast<CEffect*>(objects[i]))
		{
			effect_change_scene = dynamic_cast<CEffect*>(objects[i]);
			if (effect_change_scene->GetType() == CHANGE_SCENE)
				continue;
			else
				effect_change_scene = nullptr;
		}
		objects[i]->Render();
	}
	if (hud)
		hud->Render();
	RenderStartPoint();
	player->Render();
	if (effect_change_scene)
		effect_change_scene->Render();
}

void CLevelMapScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		/*	if (dynamic_cast<CMario*>(objects[i]))
				continue;*/
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded
	// (Mario::Update might trigger PlayScene::Unload)
	if (player == nullptr) return;
	CGame* game = CGame::GetInstance();

	game->SetCamPos(0, 0);
	if (hud == nullptr)
		hud = new CHud(game->GetCamXPos() + game->GetBackBufferWidth() / 2, game->GetCamYPos() + game->GetBackBufferHeight() - HUD_BACKGROUND_BBOX_HEIGHT / 2);

	hud->Update(dt);

	PurgeDeletedObjects();
}