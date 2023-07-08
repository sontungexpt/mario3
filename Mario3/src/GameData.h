#pragma once
#include <Windows.h>

#include "configs/GameData.h"
#include "configs/Mario.h"
#include "configs/Game.h"
#include <string>
#include <vector>

using namespace std;

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
	BOOLEAN is_show_new_game_dialog;

	ULONGLONG count_down_time_start;
	ULONGLONG show_dialog_time_start;
	ULONGLONG remain_time;

	vector<string> available_items;

public:
	CGameData() {
		player_life = 0;
		player_coin = 0;
		player_point = 0;
		remain_time = 0;
		entry_door_level = 0;
		count_down_time_start = 0;
		show_dialog_time_start = 0;
		max_door_level_passed = 0;

		current_scene_id = INT_MAX;
		is_lost_life = FALSE;
		is_show_new_game_dialog = FALSE;
		mario_level = MARIO_LEVEL_SMALL;
		available_items.clear();
	};
	~CGameData()
	{
		available_items.clear();
	};

	static CGameData* GetInstance();

	void AddAvailableItem(string item) { available_items.push_back(item); };
	vector<string> GetAvailableItems() { return available_items; };
	void ClearAvailableItems() { available_items.clear(); };

	void SetCurrentSceneId(int id) { current_scene_id = id; };
	int GetCurrentSceneId() { return current_scene_id; };
	BOOLEAN IsMoveOutHiddenMap() { return current_scene_id != INT_MAX; };
	BOOLEAN IsMoveInHiddenMap() { return current_scene_id == INT_MAX; };
	void MoveOutHiddenMap() { current_scene_id = INT_MAX; };
	void MoveInHiddenMap(int id) { current_scene_id = id; };

	void SetEntryDoorLevel(int level) { entry_door_level = level; };
	int GetEntryDoorLevel() { return entry_door_level; };

	void SetLife(int player_life) { this->player_life = player_life; };
	void DecreaseLifeBy1() { player_life--; };
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

	void SetIsLostALife(BOOLEAN is_lost_life) { this->is_lost_life = is_lost_life; };
	BOOLEAN IsLostALife() { return is_lost_life == TRUE; };
	BOOLEAN IsGameOver() { return is_lost_life == TRUE && player_life < 0; }

	void CountDownRemainTime();
	void InitRemainTime(ULONGLONG remain_time) { this->remain_time = remain_time; };
	ULONGLONG GetRemainTime() { return remain_time; };

	void SetMarioLevel(int mario_level) { this->mario_level = mario_level; };
	int GetMarioLevel() { return mario_level; };

	BOOLEAN IsShowNewGameDialog() { return is_show_new_game_dialog; };
	BOOLEAN IsStoppedUpdateNewGameDialog() { return !is_show_new_game_dialog && show_dialog_time_start == 0; };
	void UpdateShowNewGameDialog()
	{
		if (show_dialog_time_start &&
			GetTickCount64() - show_dialog_time_start > TIME_OUT_SHOW_DIALOG_NEW_GAME)
		{
			is_show_new_game_dialog = FALSE;
			show_dialog_time_start = 0;
		}
	};

	void CreateNewGame() {
		ClearOldData();
		is_show_new_game_dialog = TRUE;
		show_dialog_time_start = GetTickCount64();
		player_life = 4;
	};

	void ClearOldData()
	{
		player_life = 0;
		player_coin = 0;
		player_point = 0;
		remain_time = 0;
		entry_door_level = 0;
		count_down_time_start = 0;
		show_dialog_time_start = 0;
		max_door_level_passed = 0;
		current_scene_id = INT_MAX;
		is_lost_life = FALSE;
		is_show_new_game_dialog = FALSE;
		mario_level = MARIO_LEVEL_SMALL;

		available_items.clear();
	}
};