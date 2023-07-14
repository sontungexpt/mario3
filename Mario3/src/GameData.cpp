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
	ULONGLONG time_passed = GetTickCount64() - count_down_time_start;

	if (remain_time > 0 && time_passed > 1000)
	{
		remain_time -= time_passed / 1000;
		if (remain_time == 0)
		{
			is_lost_life = TRUE;
			count_down_time_start = 0;
			return;
		}
		count_down_time_start = GetTickCount64();
	}
}

#define FAST_COUNT_DOWN_TIME 2

void CGameData::CountDownAndAddScore()
{
	if (count_down_time_start == 0)
		count_down_time_start = GetTickCount64();
	if (remain_time > 0 && GetTickCount64() - count_down_time_start > FAST_COUNT_DOWN_TIME)
	{
		remain_time--;
		player_point += MARIO_POINT_FOR_ONE_SECOND;
		if (remain_time == 0)
		{
			count_down_time_start = 0;
			return;
		}
		count_down_time_start = GetTickCount64();
	}
}