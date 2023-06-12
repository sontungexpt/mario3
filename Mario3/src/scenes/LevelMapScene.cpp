#include "LevelMapScene.h"
#include "configs/ids/ObjectTypes.h"
#include "objects/Grass.h"
#include "objects/Platform.h"
#include "objects/Door.h"
#include "utils/Utils.h"

void CLevelMapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GRASS:
		obj = new CGrass(x, y);
		break;
	case OBJECT_TYPE_DOOR:
	{
		int screen_id = atoi(tokens[3].c_str());
		BOOLEAN allowLeft = atoi(tokens[4].c_str());
		BOOLEAN allowTop = atoi(tokens[5].c_str());
		BOOLEAN allowRight = atoi(tokens[6].c_str());
		BOOLEAN allowBottom = atoi(tokens[7].c_str());
		obj = new CDoor(x, y, screen_id, allowLeft, allowTop, allowRight, allowBottom);
	}
	break;
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	DebugOut(L"ERROR", obj);
	// General object setup
	obj->SetPosition(x, y);

	objects.push_back(obj);
}