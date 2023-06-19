#include "GameData.h"

CGameData* CGameData::instance = nullptr;

CGameData* CGameData::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CGameData();
	}
	return instance;
}