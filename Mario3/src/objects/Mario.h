#pragma once

#include "debug.h"
#include "GameData.h"
#include "GameObject.h"
#include "MarioAttackingZone.h"

#include "materials/Pipe.h"
#include "materials/EnterablePipe.h"
#include "materials/OuterablePipe.h"

#include "monsters/Monster.h"
#include "monsters/Koopa.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "configs/Mario.h"

using namespace std;

class CMario : public CGameObject
{
protected:
	int nx;

	int level;
	int power;

	LPMONSTER weapon_monster;
	LPPIPE pipe;

	LPMARIO_ATTACKINGZONE right_attacking_zone;
	LPMARIO_ATTACKINGZONE left_attacking_zone;

	ULONGLONG time_untouchable_start;
	ULONGLONG time_power_up_start;
	ULONGLONG time_fly_start;

	BOOLEAN untouchable;
	BOOLEAN is_sitting;
	BOOLEAN is_flying;
	BOOLEAN is_power_upping;
	BOOLEAN is_on_platform;
	BOOLEAN is_want_holding_koopa;
	BOOLEAN is_appearance_changing;
	BOOLEAN is_completely_inside_pipe;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithEnterablePipe(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithItem(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdTail();
	int GetAniIdEnterOuterPipe();
	int GetAniIdSmall();
	int GetAniIdWinScene();
	int GetAniIdWhenAppearanceChanging();

	void GetBoundingBoxBig(float& left, float& top, float& right, float& bottom);
	void GetBoundingBoxTail(float& left, float& top, float& right, float& bottom);
	void GetBoundingBoxSmall(float& left, float& top, float& right, float& bottom);

	void UpdateV(DWORD dt);
	void UpdatePower();
	void UpdateUntouchable();
	void CheckRemainingPlayingTime();
	void CheckJumpToHole();
	void UpdatePositionAttackingZone(DWORD dt);
public:
	CMario(float x, float y)
		: CGameObject(x, y, 0, 0, 0.0f, MARIO_GRAVITY, MARIO_RUNNING_SPEED),
		is_sitting(FALSE),
		is_flying(FALSE),
		untouchable(FALSE),
		is_on_platform(FALSE),
		is_want_holding_koopa(FALSE),
		is_appearance_changing(FALSE),
		is_power_upping(FALSE),
		weapon_monster(nullptr),
		pipe(nullptr),
		right_attacking_zone(nullptr),
		left_attacking_zone(nullptr),
		is_completely_inside_pipe(FALSE),
		power(0),
		nx(1),
		time_untouchable_start(0),
		time_power_up_start(0),
		time_fly_start(0),
		level(CGameData::GetInstance()->GetMarioLevel())
	{
	}

	~CMario()
	{
		if (weapon_monster)
			delete weapon_monster;
		if (pipe)
			delete pipe;
		if (right_attacking_zone)
			delete right_attacking_zone;
		if (left_attacking_zone)
			delete left_attacking_zone;

		right_attacking_zone = nullptr;
		left_attacking_zone = nullptr;
		weapon_monster = nullptr;
		pipe = nullptr;
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = nullptr);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable()
	{
		return state != MARIO_STATE_DIE &&
			state != MARIO_STATE_ENTER_PIPE &&
			state != MARIO_STATE_OUTER_PIPE;
	}
	/*int IsBlocking()
	{
		return state != MARIO_STATE_DIE &&
			state != MARIO_STATE_ENTER_PIPE &&
			state != MARIO_STATE_OUTER_PIPE &&
			state != MARIO_STATE_WIN_SCENE &&
			!untouchable;
	}*/

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetNx() { return nx; }

	// states
	BOOLEAN IsSmall() { return level == MARIO_LEVEL_SMALL; };
	BOOLEAN IsBig() { return level == MARIO_LEVEL_BIG; };
	BOOLEAN HasTail() { return level == MARIO_LEVEL_TAIL_SUIT; }
	BOOLEAN IsFullPower() { return power == MARIO_MAX_POWER; }
	BOOLEAN IsEnteringPipe()
	{
		return dynamic_cast<LPENTERABLE_PIPE>(pipe) &&
			state == MARIO_STATE_ENTER_PIPE;
	}
	BOOLEAN IsOuteringPipe()
	{
		return dynamic_cast<LPOUTERABLE_PIPE>(pipe) &&
			state == MARIO_STATE_OUTER_PIPE;
	}
	BOOLEAN CanEnterPipe() { return dynamic_cast<LPENTERABLE_PIPE>(pipe) != nullptr; }
	BOOLEAN IsHoldingKoopa() {
		CKoopa* koopa = dynamic_cast<CKoopa*>(weapon_monster);
		if (koopa)
			return koopa->IsMarioHolding();
		return FALSE;
	}

	LPPIPE GetPipe() { return pipe; }
	void SetPipe(LPPIPE pipe) { this->pipe = pipe; }
	void MoveOutPipe() { SetState(MARIO_STATE_OUTER_PIPE); }
	void EnterPipe() { SetState(MARIO_STATE_ENTER_PIPE); }

	void Shrink() { SetLevel(MARIO_LEVEL_SMALL); }
	void Zoom() { SetLevel(MARIO_LEVEL_BIG); }
	void CutTail() { SetLevel(MARIO_LEVEL_BIG); }
	void GrowTail() { SetLevel(MARIO_LEVEL_TAIL_SUIT); }

	void SetLevel(int level);
	int GetLevel() { return level; }
	void LevelUp() { SetLevel(MARIO_LEVEL_BIG); }
	void LevelDown() { SetLevel(MARIO_LEVEL_SMALL); }

	int GetPower() { return power; }
	void StartPowerUp()
	{
		is_power_upping = TRUE;
		time_power_up_start = GetTickCount64();
	}

	void Die();
	BOOLEAN IsDead() { return state == MARIO_STATE_DIE; }

	BOOLEAN IsWinScene() { return state == MARIO_STATE_WIN_SCENE; }
	void WinScene() { SetState(MARIO_STATE_WIN_SCENE); }

	void WantHoldKoopa() { is_want_holding_koopa = TRUE; }
	void WantKickKoopa() { is_want_holding_koopa = FALSE; }

	void SmashTail() {}

	void StartUntouchable() { SetState(MARIO_STATE_UNTOUCHABLE); }
	void JumpDeflect() { vy = -MARIO_JUMP_DEFLECT_SPEED; }

	void Reset();
};