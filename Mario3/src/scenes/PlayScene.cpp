#include <iostream>
#include <fstream>

#include "configs/All.h"

#include "PlayScene.h"
#include "utils/Utils.h"
#include "GameData.h"

#include "components/Texture/Textures.h"
#include "components/Sprite/Sprites.h"
#include "components/KeyboardHandler/SampleKeyEventHandler.h"

#include "objects/Platform.h"
#include "objects/Mario.h"

#include "objects/materials/Portal.h"
#include "objects/materials/bricks/QuestionBrick.h"
#include "objects/materials/bricks/BreakableBrick.h"
#include "objects/materials/Pipe.h"
#include "objects/materials/EnterablePipe.h"
#include "objects/materials/OuterablePipe.h"
#include "objects/materials/BlackBackground.h"

#include "objects/items/Coin.h"
#include "objects/items/RandomCard.h"

#include "objects/monsters/WindGoomba.h"
#include "objects/monsters/WindKoopa.h"

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	max_object_x = nullptr;
	max_object_y = nullptr;
	player = nullptr;
	hud = nullptr;
	change_scene_effect = nullptr;
	key_handler = new CSampleKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_SETTINGS	3
#define SCENE_SECTION_HIDDEN_MAPS 4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_HIDDEN_MAPS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);   // file: ASCII format (single-byte char) => Wide Char
	LPSCENE scene = nullptr;
	switch (id)
	{
	default:
		scene = new CPlayScene(id, path);
		break;
	}
	hidden_map_ids.push_back(id);
	CGame::GetInstance()->AddScene(id, scene);
}

void CPlayScene::ClearHiddenMaps()
{
	for (int i = 0; i < hidden_map_ids.size(); i++)
	{
		CGame::GetInstance()->RemoveScene(hidden_map_ids[i]);
	}
	hidden_map_ids.clear();
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == nullptr)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	//DebugOut(L"[ERROR] Texture ID %d not found!\n", tokens.size());

	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());

		DebugOut(L"[INFO] Sprite Id %d add", sprite_id);
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

int CPlayScene::CreatePlayer(float x, float y)
{
	if (player)
	{
		DebugOut(L"[ERROR] MARIO object was created before!\n");
		return 0;
	}
	else
	{
		CGameObject* obj = new CMario(x, y);
		player = (CMario*)obj;
		obj->SetPosition(x, y);
		CGame::GetInstance()->SetCamPos(x - CGame::GetInstance()->GetBackBufferWidth() / 2, y);
		objects.push_back(obj);
		DebugOut(L"[INFO] Player object has been created!\n");
		return 1;
	}
}

void CPlayScene::_ParseSection_OBJECTS(string line)
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
	case OBJECT_TYPE_MARIO:
	{
		CreatePlayer(x, y);
		return;
	}
	break;
	case OBJECT_TYPE_GOOMBA:
	{
		if (tokens.size() == 4)
		{
			int goomba_type = atoi(tokens[3].c_str());
			if (goomba_type == GOOMBA_TYPE_FLY)
			{
				obj = new CWindGoomba(x, y);
				break;
			}
		}
		obj = new CGoomba(x, y);
	}
	break;
	case OBJECT_TYPE_COIN:
	{
		int coin_state = COIN_STATE_IDLE;
		if (tokens.size() >= 4)
			coin_state = atoi(tokens[3].c_str());
		obj = new CCoin(x, y, coin_state);
	}
	break;
	case OBJECT_TYPE_QUESTION_BRICK:
	{
		if (tokens.size() == 4)
		{
			int item_type = atoi(tokens[3].c_str());
			obj = new CQuestionBrick(x, y, item_type);
			break;
		}
		else
		{
			obj = new CQuestionBrick(x, y);
			break;
		}
	}
	case OBJECT_TYPE_BREAKABLE_BRICK:
	{
		int item_type = BREAKABLE_BRICK_NONE;
		if (tokens.size() >= 4)
			item_type = atoi(tokens[3].c_str());
		obj = new CBreakableBrick(x, y, item_type);
		break;
	}
	case OBJECT_TYPE_RANDOM_CARD:
		obj = new CRandomCard(x, y);
		break;
	case OBJECT_TYPE_BLACK_BAKCGROUND:
	{
		float length = atof(tokens[3].c_str());
		obj = new CBlackBackground(x, y, length);
	}
	break;
	case OBJECT_TYPE_PIPE:
	{
		int state = PIPE_STATE_LONG;
		int plant_type = PIPE_PLANT_NOTHING;
		int direction = PIPE_DIRECTION_UP;
		int color = PIPE_COLOR_GREEN;
		if (tokens.size() >= 4)
		{
			state = atoi(tokens[3].c_str());
		}
		if (tokens.size() >= 5)
		{
			plant_type = atoi(tokens[4].c_str());
		}
		if (tokens.size() >= 6)
		{
			direction = atoi(tokens[5].c_str());
		}
		if (tokens.size() >= 7)
		{
			color = atoi(tokens[6].c_str());
		}

		obj = new CPipe(x, y, state, plant_type, direction, color);
	}
	break;
	case OBJECT_TYPE_ENTERABLE_PIPE:
	{
		int state = atoi(tokens[3].c_str());
		int plant_type = atoi(tokens[4].c_str());
		int direction = atoi(tokens[5].c_str());
		int color = atoi(tokens[6].c_str());
		int scene_id = atoi(tokens[7].c_str());

		obj = new CEnterablePipe(x, y, state, plant_type, direction, color, scene_id);
	}
	break;
	case OBJECT_TYPE_OUTERABLE_PIPE:
	{
		int state = atoi(tokens[3].c_str());
		int plant_type = atoi(tokens[4].c_str());
		int direction = atoi(tokens[5].c_str());
		int color = atoi(tokens[6].c_str());
		int scene_id = atoi(tokens[7].c_str());

		obj = new COuterablePipe(x, y, state, plant_type, direction, color, scene_id);

		if (((LPOUTERABLE_PIPE)obj)->IsCurrentOutdoor())
		{
			if (!player)
				CreatePlayer(x, y);

			((CMario*)player)->SetPipe((LPOUTERABLE_PIPE)obj);
			((CMario*)player)->MoveOutPipe();
		}
	}
	break;
	case OBJECT_TYPE_KOOPA:
	{
		int koopa_color = KOOPA_RED;
		BOOLEAN is_limit_moving_space = TRUE;
		if (tokens.size() >= 4)
			koopa_color = atoi(tokens[3].c_str());
		if (tokens.size() >= 6)
			is_limit_moving_space = atoi(tokens[5].c_str());
		if (tokens.size() >= 5)
		{
			int koopa_type = atoi(tokens[4].c_str());
			if (koopa_type == KOOPA_TYPE_FLY)
			{
				obj = new CWindKoopa(x, y, koopa_color, is_limit_moving_space);
				break;
			}
		}

		obj = new CKoopa(x, y, koopa_color, is_limit_moving_space);
	}
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
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	SetMaxCoordinate(obj);

	objects.push_back(obj);
}

void CPlayScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "limit_time")
	{
		CGameData::GetInstance()->InitRemainTime(atoi(tokens[1].c_str()));
	}
	else if (tokens[0] == "background_color")
	{
		float r = (float)atof(tokens[1].c_str());
		float g = (float)atof(tokens[2].c_str());
		float b = (float)atof(tokens[3].c_str());
		float a = (float)atof(tokens[4].c_str());
		CGame::GetInstance()->SetBackgroundColor(r, g, b, a);
	}
	else
	{
		DebugOut(L"[ERROR] Unknown game setting: %s\n", ToWSTR(tokens[0]).c_str());
	}
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#' || line[0] == '/') continue;	// skip comment lines

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

/// <summary>
/// Load scene resources from scene file (textures, sprites, animations and objects)
/// </summary>
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#' || line[0] == '/') continue;	// skip comment lines
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[SETTINGS]") { section = SCENE_SECTION_SETTINGS; continue; };
		if (line == "[HIDDEN_MAPS]") { section = SCENE_SECTION_HIDDEN_MAPS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		switch (section)
		{
		case SCENE_SECTION_ASSETS: this->_ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: this->_ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_SETTINGS: this->_ParseSection_SETTINGS(line); break;
		case SCENE_SECTION_HIDDEN_MAPS: this->_ParseSection_HIDDEN_MAPS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::UpdateHud(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CGame* game = CGame::GetInstance();

	if (hud == nullptr)
		hud = new CHud(game->GetCamXPos() + game->GetBackBufferWidth() / 2, game->GetCamYPos() + game->GetBackBufferHeight() - HUD_BACKGROUND_BBOX_HEIGHT / 2);
	else
	{
		hud->SetX(game->GetCamXPos() + game->GetBackBufferWidth() / 2);
		hud->SetY(game->GetCamYPos() + game->GetBackBufferHeight() - HUD_BACKGROUND_BBOX_HEIGHT / 2);
	}

	hud->Update(dt);
}

void CPlayScene::UpdateCamera()
{
	CGame* game = CGame::GetInstance();
	if (player == nullptr)
	{
		game->SetCamPos(0, 0);
		return;
	};

	float camera_width = game->GetBackBufferWidth();
	float camera_height = game->GetBackBufferHeight();

	float old_cam_x = game->GetCamXPos();
	float old_cam_y = game->GetCamYPos();

	float mario_x = player->GetX();
	float mario_y = player->GetY();

	float new_cam_x = mario_x - camera_width / 2;
	float new_cam_y = floor(mario_y / camera_height) * camera_height;

	if (new_cam_x < 0) new_cam_x = 0;
	if (new_cam_y < 0) new_cam_y = 0;

	float max_cam_x = max_object_x->GetRight() - camera_width;
	if (max_object_x && new_cam_x > max_cam_x)
		new_cam_x = max_cam_x;
	if (max_object_y && new_cam_y > max_object_y->GetBottom())
		new_cam_y = old_cam_y;

	game->SetCamPos(new_cam_x, new_cam_y);
}

void CPlayScene::Update(DWORD dt)
{
	//player is dead not need to update other objects
	CGame* game = CGame::GetInstance();

	if (game->IsInTransitionScene())
	{
		CMario* mario = dynamic_cast<CMario*>(player);

		if (mario)
		{
			if (mario->IsDead())
				mario->Update(dt);
			else if (mario->IsWinScene())
			{
				vector<LPGAMEOBJECT> coObjects;
				for (size_t i = 0; i < objects.size(); i++)
				{
					// if win game scene, only colliable with wall
					if (!objects[i]->IsBlocking())
						continue;
					coObjects.push_back(objects[i]);
				}
				mario->Update(dt, &coObjects);
			}
		}
		if (change_scene_effect)
			change_scene_effect->Update(dt);
		return;
	}

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

	UpdateCamera();
	UpdateHud(dt);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CMario*>(objects[i]))
			continue;
		else if (dynamic_cast<LPENTERABLE_PIPE>(objects[i]))
		{
			if (player)
			{
				CMario* mario = dynamic_cast<CMario*>(player);
				if (mario->IsEnteringPipe() &&
					mario->GetPipe() == objects[i])
					continue;
			}
		}
		else if (dynamic_cast<LPOUTERABLE_PIPE>(objects[i]))
		{
			if (player)
			{
				CMario* mario = dynamic_cast<CMario*>(player);
				if (mario->IsOuteringPipe() &&
					mario->GetPipe() == objects[i])
					continue;
			}
		}
		else if (dynamic_cast<CEffect*>(objects[i]))
		{
			if (((CEffect*)objects[i])->GetType() == CHANGE_SCENE)
				continue;
		}
		objects[i]->Render();
	}
	if (hud) hud->Render();

	// if player is not entering pipe then render player
	// after other objects
	if (player)
	{
		CMario* mario = dynamic_cast<CMario*>(player);
		player->Render();

		if (mario->IsEnteringPipe() || mario->IsOuteringPipe())
			mario->GetPipe()->Render();
	}

	// change scene effect is have to render last
	if (change_scene_effect) change_scene_effect->Render();
}

void CPlayScene::RenderChangeSceneEffect()
{
}

void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
	ClearHiddenMaps();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}

	objects.clear();

	//clear hidden maps if next scene is not a hidden map of this scene
	vector<int>::iterator it =
		find(hidden_map_ids.begin(),
			hidden_map_ids.end(),
			CGame::GetInstance()->GetNextScene());
	if (it == hidden_map_ids.end())
		ClearHiddenMaps();

	player = nullptr;
	max_object_x = nullptr;
	max_object_y = nullptr;
	change_scene_effect = nullptr;

	if (hud != nullptr)
	{
		delete hud;
		hud = nullptr;
	}

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == nullptr; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
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

LPGAMEOBJECT CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	SetMaxCoordinate(obj);
	objects.push_back(obj);
	CEffect* effect = dynamic_cast<CEffect*>(objects.back());
	if (effect && effect->GetType() == CHANGE_SCENE)
		change_scene_effect = effect;
	return objects.back();
}

LPGAMEOBJECT CPlayScene::AddObjectToFirst(LPGAMEOBJECT obj)
{
	SetMaxCoordinate(obj);
	objects.insert(objects.begin() + 1, obj);

	CEffect* effect = dynamic_cast<CEffect*>(objects.front());
	if (effect && effect->GetType() == CHANGE_SCENE)
		change_scene_effect = effect;
	return objects.front();
}