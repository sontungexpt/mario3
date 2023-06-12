#pragma once
#include <Windows.h>
#include "configs/GameData.h"

class CGameData {
	static CGameData* instance;

	int coin;
	int door_level;
	BOOLEAN is_game_over;

public:
	CGameData() {
		coin = 0;
		door_level = 0;
		is_game_over = FALSE;
	};
	~CGameData() {};

	static CGameData* GetInstance();

	void UnitIncreaseCoin() { this->coin++; };
	void SetCoin(unsigned int coin) { this->coin = coin; };
	int GetCoin() { return coin; };

	void SetDoorLevel(int door_level) { this->door_level = door_level; };
	void UnitIncreaseDoorLevel() { this->door_level++; };
	int GetDoorLevel() { return door_level; };

	void SetGameOver(BOOLEAN is_game_over) { this->is_game_over = TRUE; };
	BOOLEAN IsGameOver() { return is_game_over == TRUE; };

	void CreateNewGame() {
		coin = 0;
		is_game_over = FALSE;
	};
};