#pragma once
#include "debug.h"
#include "GameObject.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "configs/Mario.h"

class CMario : public CGameObject
{
	float max_vx;
	float ax;				// acceleration on x
	float ay;				// acceleration on y

	int level;
	int coin;
	int untouchable;

	ULONGLONG time_untouchable_start;

	BOOLEAN is_sitting;
	BOOLEAN is_on_platform;
	BOOLEAN dead;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();

public:
	CMario(float x, float y, int level = MARIO_LEVEL_SMALL) : CGameObject(x, y)
	{
		coin = 0;

		ax = 0.0f;
		ay = MARIO_GRAVITY;
		max_vx = MARIO_RUNNING_SPEED;

		is_sitting = false;
		this->level = level;
		untouchable = 0;
		time_untouchable_start = -1;
		is_on_platform = FALSE;
		dead = FALSE;
	}

	// core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	// collision
	int IsCollidable() { return (state != MARIO_STATE_DIE); }
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// states
	void SetLevel(int l);
	int GetLevel() { return level; }
	void LevelUp() { level = MARIO_LEVEL_BIG; }
	void LevelDown() { level = MARIO_LEVEL_SMALL; }
	BOOLEAN IsSmall() { return level == MARIO_LEVEL_SMALL; };
	BOOLEAN IsBig() { return level == MARIO_LEVEL_BIG; };
	void Shrink() { SetLevel(MARIO_LEVEL_SMALL); }
	void Zoom() { SetLevel(MARIO_LEVEL_BIG); }
	void Die();
	BOOLEAN IsDead() { return state == MARIO_STATE_DIE; }

	void StartUntouchable() { untouchable = 1; time_untouchable_start = GetTickCount64(); }
	void JumpDeflect() { vy = -MARIO_JUMP_DEFLECT_SPEED; }
};