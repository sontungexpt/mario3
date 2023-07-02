#include "GameData.h"
#include <debug.h>

CGameData* CGameData::instance = nullptr;

CGameData* CGameData::GetInstance()
{
	if (instance == nullptr)
		instance = new CGameData();
	return instance;
}

void CGameData::CountDownRemainTime()
{
	if (count_down_time_start == 0)
		count_down_time_start = GetTickCount64();
	if (remain_time > 0 && GetTickCount64() - count_down_time_start > 1000)
	{
		remain_time--;
		if (remain_time == 0)
		{
			is_game_over = TRUE;
			count_down_time_start = 0;
			return;
		}
		count_down_time_start = GetTickCount64();
	}
}