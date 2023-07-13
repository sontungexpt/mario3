#include "IntroScene.h"
#include "configs/core/ObjectTypes.h"
#include "configs/monsters/Koopa601000.h"
#include "utils/Utils.h"

#include "objects/Platform.h"
#include "objects/Mario.h"

#include "objects/monsters/WindGoomba.h"
#include "objects/monsters/WindKoopa.h"
#include <configs/Intro.h>

void CIntroScene::_ParseSection_OBJECTS(string line)
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
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	SetMaxCoordinate(obj);

	objects.push_back(obj);
}

void CIntroScene::UpdateCamera()
{
	CGame::GetInstance()->SetCamPos(0, 0);
}

void CIntroScene::UpdateCurtain(DWORD dt)
{
}

void CIntroScene::RenderCurtain()
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(ID_ANI_INTRO_CURTAIN);
	float back_buffer_width = (float)CGame::GetInstance()->GetBackBufferWidth();
	float back_buffer_height = (float)CGame::GetInstance()->GetBackBufferHeight();

	int number_cell_width = ceil(back_buffer_width / INTRO_CURTAIN_BBOX_WIDTH);
	int number_cell_height = ceil(back_buffer_height / INTRO_CURTAIN_BBOX_HEIGHT);

	for (int i = 0; i < number_cell_height; i++)
	{
		for (int j = 0; j < number_cell_width; j++)
		{
			ani->Render(
				INTRO_CURTAIN_BBOX_WIDTH / 2 + j * INTRO_CURTAIN_BBOX_WIDTH,
				INTRO_CURTAIN_BBOX_HEIGHT / 2 + i * INTRO_CURTAIN_BBOX_HEIGHT
			);
		}
	}
}

void CIntroScene::Render()
{
	RenderCurtain();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	if (change_scene_effect) change_scene_effect->Render();
}

void CIntroScene::Update(DWORD dt)
{
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

	UpdateCamera();
	PurgeDeletedObjects();
}

void CIntroScene::Unload()
{
	CPlayScene::Unload();
}