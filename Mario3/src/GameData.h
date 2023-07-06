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

	// if the player is completely move to hidden map this variable will be assigned with the scene_id
	// if the player is completely move out hidden map this variable will be assigned with INT_MAX
	// example: the player is in world 1-1, he move to hidden map 1-1,
	// when player is completely in pipe then this var will be assign with the scene_id of hidden_map
	// when player change to hidden map 1-1 and completely move out pipe then this var will be assign with INT_MAX
	// and when the player comback to world 1-1 and completely in pipe, this var will be assign the scene_id of world 1-1
	// and when player change to world 1-1 and completely move out pipe, this var will be assign with INT_MAX
	int current_scene_id;

	BOOLEAN is_lost_life;

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
		current_scene_id = INT_MAX;

		is_lost_life = FALSE;
		mario_level = MARIO_LEVEL_SMALL;
	};
	~CGameData() {};

	static CGameData* GetInstance();

	void SetCurrentSceneId(int id) { current_scene_id = id; };
	int GetCurrentSceneId() { return current_scene_id; };
	BOOLEAN IsMoveOutHiddenMap() { return current_scene_id != INT_MAX; };
	BOOLEAN IsMoveInHiddenMap() { return current_scene_id == INT_MAX; };
	void MoveOutHiddenMap() { current_scene_id = INT_MAX; };
	void MoveInHiddenMap(int id) { current_scene_id = id; };

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

	void SetGameOver(BOOLEAN is_lost_life) { this->is_lost_life = is_lost_life; };
	BOOLEAN IsLostALife() { return is_lost_life == TRUE; };
	BOOLEAN IsGameOver() { return is_lost_life == TRUE && player_life == 0; }

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
		is_lost_life = FALSE;
	};
};