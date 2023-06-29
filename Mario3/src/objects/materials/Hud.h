#pragma once
#include "objects/GameObject.h"
#include "configs/materials/Hud103000.h"

class CHud : public CGameObject
{
	void RenderArrowPower();
	void RenderMarioRemainingLife();
	void RenderPlayerPoint();
	void RenderHudBackground();
	void RenderWorldNumber();
	void RenderPlayerCoin();

	int GetAniIdNumber(char number);

	int GetAniIdNumber(int number);

	void RenderNumber(int number, float left, float top, int min_char = 0);

	BOOLEAN is_full_power_dark;

	ULONGLONG time_change_full_power_status_start;

public:
	CHud(float x, float y) : CGameObject(x, y) {
		is_full_power_dark = TRUE;
		time_change_full_power_status_start = 0;
	}
	void Update(DWORD dt);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }

	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

typedef CHud* LPHUD;