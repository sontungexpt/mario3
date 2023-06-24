#pragma once
#include "debug.h"
#include "GameObject.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "configs/Mario.h"
#include "objects/monsters/Monster.h"

class CMario : public CGameObject
{
	int nx;

	int level;
	int coin;

	LPMONSTER weapon_monster;

	ULONGLONG time_untouchable_start;

	BOOLEAN untouchable;
	BOOLEAN is_sitting;
	BOOLEAN is_on_platform;
	BOOLEAN is_want_holding_koopa;
	BOOLEAN is_appearance_changing;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithItem(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

	int GetAniIdWhenAppearanceChanging();

	void GetBoundingBoxBig(float& left, float& top, float& right, float& bottom);
	void GetBoundingBoxSmall(float& left, float& top, float& right, float& bottom);

public:
	CMario(float x, float y, int level = MARIO_LEVEL_SMALL) : CGameObject(x, y)
	{
		coin = 0;
		nx = 1;

		ax = 0.0f;
		ay = MARIO_GRAVITY;

		max_vx = MARIO_RUNNING_SPEED;

		is_sitting = FALSE;
		untouchable = FALSE;
		is_on_platform = FALSE;
		is_want_holding_koopa = FALSE;
		is_appearance_changing = FALSE;

		weapon_monster = nullptr;

		this->level = level;
		time_untouchable_start = -1;
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return state != MARIO_STATE_DIE; }
	//int IsBlocking() { return (state != MARIO_STATE_DIE && !untouchable); }

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetNx() { return nx; }
	void  SetNx(int nx) { this->nx = nx; }

	// states
	BOOLEAN IsSmall() { return level == MARIO_LEVEL_SMALL; };
	BOOLEAN IsBig() { return level == MARIO_LEVEL_BIG; };
	void Shrink() { SetLevel(MARIO_LEVEL_SMALL); }
	void Zoom() { SetLevel(MARIO_LEVEL_BIG); }
	void SetLevel(int level);
	int GetLevel() { return level; }
	void LevelUp() { SetLevel(MARIO_LEVEL_BIG); }
	void LevelDown() { SetLevel(MARIO_LEVEL_SMALL); }

	void Die();
	BOOLEAN IsDead() { return state == MARIO_STATE_DIE; }

	void WantHoldKoopa() { is_want_holding_koopa = TRUE; }
	void WantKickKoopa() { is_want_holding_koopa = FALSE; }

	void StartUntouchable() { SetState(MARIO_STATE_UNTOUCHABLE); }
	void JumpDeflect() { vy = -MARIO_JUMP_DEFLECT_SPEED; }

	void Reset();
};