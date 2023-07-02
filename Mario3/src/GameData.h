#pragma once
#include <Windows.h>
#include "configs/GameData.h"
#include "configs/Mario.h"

class Door;

class CGameData {
	static CGameData* instance;

	int player_life;
	int player_coin;
	int player_point;
	int mario_level;
	int max_door_level_passed;
	int entry_door_level;

	BOOLEAN is_game_over;

	ULONGLONG count_down_time_start;
	ULONGLONG remain_time;

public:
	CGameData() {
		player_life = 0;
		player_coin = 0;
		player_point = 0;
		remain_time = 0;
		entry_door_level = 0;
		count_down_time_start = 0;
		max_door_level_passed = 0;

		mario_level = MARIO_LEVEL_SMALL;
		is_game_over = FALSE;
	};
	~CGameData() {};

	static CGameData* GetInstance();

	void SetEntryDoorLevel(int level) { entry_door_level = level; };
	int GetEntryDoorLevel() { return entry_door_level; };

	void SetLife(int player_life) { this->player_life = player_life; };
	void DecreaseLifeBy1() { player_life = player_life > 0 ? player_life - 1 : 0; };
	void IncreaseLifeBy1() { player_life++; }
	int GetLife() { return player_life; };

	int GetMaxDoorLevelPassed() { return max_door_level_passed; }
	void  SetMaxDoorLevelPassed(int level) { max_door_level_passed = level; }

	void UnitIncreaseCoin() { this->player_coin++; };
	void SetCoin(unsigned int player_coin) { this->player_coin = player_coin; };
	int GetCoin() { return player_coin; };

	void SetPoint(int player_point) { this->player_point = player_point; };
	void IncreasePointBy(int player_point) { this->player_point += player_point; };
	int GetPoint() { return player_point; };

	void SetGameOver(BOOLEAN is_game_over) { this->is_game_over = is_game_over; };
	BOOLEAN IsGameOver() { return is_game_over == TRUE; };

	void CountDownRemainTime();
	void InitRemainTime(ULONGLONG remain_time) { this->remain_time = remain_time; };
	ULONGLONG GetRemainTime() { return remain_time; };

	void SetMarioLevel(int mario_level) { this->mario_level = mario_level; };
	int GetMarioLevel() { return mario_level; };

	void CreateNewGame() {
		player_life = 4;
		player_coin = 0;
		player_point = 0;
		remain_time = 0;
		count_down_time_start = 0;
		is_game_over = FALSE;
	};
};