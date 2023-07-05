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
	case OBJECT_TYPE_GRASS:
		obj = new CGrass(x, y);
		break;
	case OBJECT_TYPE_DOOR:
	{
		int screen_id = atoi(tokens[3].c_str());
		int door_level = atoi(tokens[4].c_str());

		CGameData* data = CGameData::GetInstance();

		if (data->GetEntryDoorLevel() == 0)
		{
			prev_door_x = start_x;
			prev_door_y = start_y;
		}
		else if (door_level == data->GetEntryDoorLevel() - 1)
		{
			prev_door_x = x;
			prev_door_y = y;
		}
		else if (door_level == data->GetEntryDoorLevel())
		{
			if (player)
				player->SetPosition(x, y);
			else
				CreatePlayer(x, y);
		}

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

void CLevelMapScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start_position")
	{
		SetPlayerStartPos((float)atof(tokens[1].c_str()), (float)atof(tokens[2].c_str()));

		CreatePlayer(start_x, start_y);
	}
	else
	{
		CPlayScene::_ParseSection_SETTINGS(line);
	}
}

int CLevelMapScene::CreatePlayer(float x, float y)
{
	if (player != nullptr)
	{
		DebugOut(L"[ERROR] MARIO object was created before!\n");
		return 0;
	}
	else
	{
		CGameObject* obj = new CMarioLevelMap(x, y);
		player = (CMarioLevelMap*)obj;
		obj->SetPosition(x, y);
		CGame::GetInstance()->SetCamPos(x - CGame::GetInstance()->GetBackBufferWidth() / 2, y);
		objects.push_back(obj);
		DebugOut(L"[INFO] Player object has been created!\n");
		return 1;
	}
}

void CLevelMapScene::RenderStartPoint()
{
	CAnimations::GetInstance()->Get(ID_ANI_START_POINT)->Render(start_x, start_y);
}

void CLevelMapScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CMarioLevelMap*>(objects[i]))
			continue;
		if (dynamic_cast<CEffect*>(objects[i]))
		{
			if (((CEffect*)objects[i])->GetType() == CHANGE_SCENE)
				continue;
		}
		objects[i]->Render();
	}
	if (hud) hud->Render();
	RenderStartPoint();
	if (player) player->Render();
	if (change_scene_effect) change_scene_effect->Render();
}

void CLevelMapScene::Update(DWORD dt)
{
	CGame* game = CGame::GetInstance();

	if (game->IsInTransitionScene())
	{
		if (change_scene_effect)
			change_scene_effect->Update(dt);
		return;
	}

	// if player is dead, and still have life,
	// then the player will be moved to the previous door
	CGameData* data = CGameData::GetInstance();
	if (data->IsLostALife() && data->GetLife() > 0)
	{
		((CMarioLevelMap*)player)->MoveToSpecialPos(prev_door_x, prev_door_y);
		data->SetGameOver(FALSE);
	}

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

	game->SetCamPos(0, 0);
	if (hud == nullptr)
		hud = new CHud(game->GetCamXPos() + game->GetBackBufferWidth() / 2, game->GetCamYPos() + game->GetBackBufferHeight() - HUD_BACKGROUND_BBOX_HEIGHT / 2);

	hud->Update(dt);

	PurgeDeletedObjects();
}