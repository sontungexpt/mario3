#include "GameData.h"

CGameData* CGameData::instance = NULL;

CGameData* CGameData::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CGameData();
	}
	return instance;
}