#include "LevelMapScene.h"

#include "utils/Utils.h"

#include "objects/Mario.h"
#include "objects/MarioLevelMap.h"
#include "objects/Platform.h"
#include "objects/materials/Grass.h"
#include "objects/materials/Door.h"
#include "objects/materials/Effect.h"

#include "objects/monsters/Hammer.h"

#include "configs/core/ObjectTypes.h"

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

void CLevelMapScene::RenderNewGameDialog()
{
	CDrawingManager::RenderOverlay(0.4f);
	int number_cell_width = 8;
	int number_cell_height = 4;
	float x_new_game_dialog = SCREEN_WIDTH / 2.0f;
	float y_new_game_dialog = CGame::GetInstance()->GetBackBufferHeight() / 2.0f;

	float left = x_new_game_dialog - number_cell_width / 2.0f * HUD_FRAME_CELL_WIDTH;
	float top = y_new_game_dialog - number_cell_height / 2.0f * HUD_FRAME_CELL_HEIGHT;

	CDrawingManager::RenderBlueFrame(x_new_game_dialog, y_new_game_dialog, number_cell_width, number_cell_height);

	CDrawingManager::RenderString("WORLD 1", x_new_game_dialog - 7.0f / 2 * HUD_CHAR_BBOX_WIDTH, top + 6);
	CDrawingManager::RenderString("MARIO", left + 16, top + 28);

	CDrawingManager::RenderIcon("MARIO LEVEL DIALOG", left + 64, top + 30);

	CDrawingManager::RenderIcon("X", left + 82, top + 31);
	CDrawingManager::RenderNumber(CGameData::GetInstance()->GetLife(), left + 96, top + 28);
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
			else if (((CEffect*)objects[i])->GetType() == START_FOLLOW_PLAYER)
				continue;
		}
		objects[i]->Render();
	}
	if (hud) hud->Render();

	RenderStartPoint();

	CGameData* data = CGameData::GetInstance();

	if (player &&
		!data->IsGameOver() &&
		!IsShowNewGameDialog() &&
		!star_follow_mario_effect
		)
		player->Render();

	if (star_follow_mario_effect) star_follow_mario_effect->Render();

	if (game_over_control_panel) game_over_control_panel->Render();

	if (IsShowNewGameDialog()) RenderNewGameDialog();

	if (change_scene_effect) change_scene_effect->Render();
}

void CLevelMapScene::UpdateHud(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CGame* game = CGame::GetInstance();

	if (hud == nullptr)
		hud = new CHud(
			game->GetCamXPos() + game->GetBackBufferWidth() / 2,
			game->GetCamYPos() + game->GetBackBufferHeight() - HUD_BACKGROUND_BBOX_HEIGHT / 2
		);

	hud->Update(dt);
}

void CLevelMapScene::UpdateCamera()
{
	CGame::GetInstance()->SetCamPos(0, 0);
}

int CLevelMapScene::UpdateGameOverPanel(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CGameData* data = CGameData::GetInstance();

	if (data->IsGameOver())
	{
		// clear old key_handler
		if (dynamic_cast<CLevelMapKeyHandler*>(key_handler))
		{
			delete key_handler;
			key_handler = nullptr;
		}
		if (!key_handler)
		{
			key_handler = new CGameOverControlPanelKeyEventHandler(this);
			CGame::GetInstance()->SetKeyHandler(key_handler);
		}

		if (!game_over_control_panel)
			game_over_control_panel = new GameOverControlPanel(
				SCREEN_WIDTH / 2.0f,
				CGame::GetInstance()->GetBackBufferHeight() / 2.0f
			);

		game_over_control_panel->Update(dt);
		return 1;
	}
	else
	{
		if (dynamic_cast<CGameOverControlPanelKeyEventHandler*>(key_handler))
		{
			delete key_handler;
			key_handler = nullptr;
		}
		if (!key_handler)
		{
			key_handler = new CLevelMapKeyHandler(this);
			CGame::GetInstance()->SetKeyHandler(key_handler);
		}
		if (game_over_control_panel)
		{
			((CMarioLevelMap*)player)->MoveToSpecialPos(start_x, start_y);
			delete game_over_control_panel;
			game_over_control_panel = nullptr;
		}
		return 0;
	}
}

int CLevelMapScene::UpdateShowNewGameDialog()
{
	if (IsShowNewGameDialog())
	{
		CGameData::GetInstance()->UpdateShowNewGameDialog();
		is_showed_follow_mario_effect = FALSE;
		return 1;
	}

	if (!star_follow_mario_effect && !is_showed_follow_mario_effect)
	{
		float x_new_game_dialog = SCREEN_WIDTH / 2.0f;
		float y_new_game_dialog = CGame::GetInstance()->GetBackBufferHeight() / 2.0f;
		CEffectManager::Gennerate(x_new_game_dialog, y_new_game_dialog, START_FOLLOW_PLAYER, EFFECT_START_FOLLOW_PLAYER);
		is_showed_follow_mario_effect = TRUE;
	}
	return 0;
};

BOOLEAN CLevelMapScene::IsShowNewGameDialog()
{
	return CGameData::GetInstance()->IsShowNewGameDialog() &&
		!game_over_control_panel &&
		player->GetX() == start_x &&
		player->GetY() == start_y;
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

	CGameData* data = CGameData::GetInstance();

	if (!data->IsGameOver() && !IsShowNewGameDialog() && !star_follow_mario_effect)
	{
		if (data->IsLostALife())
		{
			((CMarioLevelMap*)player)->MoveToSpecialPos(prev_door_x, prev_door_y);
			data->SetIsLostALife(FALSE);
		}

		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CMario*>(objects[i]))
				continue;
			coObjects.push_back(objects[i]);
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}

	UpdateCamera();
	UpdateHud(dt);

	if (star_follow_mario_effect)
		star_follow_mario_effect->Update(dt);

	UpdateGameOverPanel(dt);
	UpdateShowNewGameDialog();
	PurgeDeletedObjects();
}

void CLevelMapScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;

		if (o->IsDeleted())
		{
			CEffect* effect = dynamic_cast<CEffect*>(o);
			if (effect && effect->GetType() == START_FOLLOW_PLAYER)
				star_follow_mario_effect = nullptr;

			delete o;
			*it = nullptr;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		remove_if(objects.begin(),
			objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CLevelMapScene::Unload()
{
	if (game_over_control_panel)
		delete game_over_control_panel;

	if (star_follow_mario_effect)
		delete star_follow_mario_effect;

	game_over_control_panel = nullptr;
	star_follow_mario_effect = nullptr;
	CPlayScene::Unload();
}

LPGAMEOBJECT CLevelMapScene::AddObject(LPGAMEOBJECT obj)
{
	LPGAMEOBJECT object = CPlayScene::AddObject(obj);
	CEffect* effect = dynamic_cast<CEffect*>(object);
	if (effect && effect->GetType() == START_FOLLOW_PLAYER)
		star_follow_mario_effect = effect;
	return object;
}

LPGAMEOBJECT CLevelMapScene::AddObjectToFirst(LPGAMEOBJECT obj)
{
	LPGAMEOBJECT object = CPlayScene::AddObjectToFirst(obj);

	CEffect* effect = dynamic_cast<CEffect*>(object);
	if (effect && effect->GetType() == START_FOLLOW_PLAYER)
		star_follow_mario_effect = effect;
	return object;
}