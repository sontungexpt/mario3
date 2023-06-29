#pragma once
#include <Windows.h>
#include "configs/GameData.h"

class CGameData {
	static CGameData* instance;

	int player_coin;
	int player_point;
	int door_level;
	BOOLEAN is_game_over;

public:
	CGameData() {
		player_coin = 0;
		door_level = 0;
		player_point = 0;
		is_game_over = FALSE;
	};
	~CGameData() {};

	static CGameData* GetInstance();

	void UnitIncreaseCoin() { this->player_coin++; };
	void SetCoin(unsigned int player_coin) { this->player_coin = player_coin; };
	int GetCoin() { return player_coin; };

	void SetDoorLevel(int door_level) { this->door_level = door_level; };
	void UnitIncreaseDoorLevel() { this->door_level++; };
	int GetDoorLevel() { return door_level; };

	void SetPoint(int player_point) { this->player_point = player_point; };
	void IncreasePointBy(int player_point) { this->player_point += player_point; };
	int GetPoint() { return player_point; };

	void SetGameOver(BOOLEAN is_game_over) { this->is_game_over = TRUE; };
	BOOLEAN IsGameOver() { return is_game_over == TRUE; };

	void CreateNewGame() {
		player_coin = 0;
		is_game_over = FALSE;
	};

	void Reset() {
		player_coin = 0;
		door_level = 0;
		player_point = 0;
		is_game_over = FALSE;
	};
};