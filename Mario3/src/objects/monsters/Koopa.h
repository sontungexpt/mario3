#include "configs/monsters/Koopa601000.h"
#include "Monster.h"

class CKoopa : public CMonster
{
protected:
	int type; // green or red

	ULONGLONG defend_time_start;
	ULONGLONG comeback_time_start;

	BOOLEAN is_defend;
	BOOLEAN is_comeback;
	BOOLEAN is_mario_kicked;
	BOOLEAN is_mario_holding;

	float limit_x_positive = 0;
	float limit_x_negative = 0;

	float mario_speed_when_kicked;

	void OnCollisionWithMonster(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

	int GetAniIdRed();
	int GetAniIdGreen();

	void AdjustPos();

	void SetState(int state);
public:
	CKoopa(float x, float y, int type = KOOPA_RED) : CMonster(x, y) {
		this->type = type;

		is_defend = FALSE;
		is_comeback = FALSE;
		is_mario_kicked = FALSE;
		is_mario_holding = FALSE;
		is_on_platform = FALSE;

		mario_speed_when_kicked = 0.0f;
		max_vx = KOOPA_MAX_SPEED;

		defend_time_start = -1;
		comeback_time_start = -1;
		// always move to mario in the first time
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	//core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//collision
	void OnCollisionWith(LPCOLLISIONEVENT e);

	BOOLEAN IsDefend() { return is_defend; }
	void Defend();
	void ComebackAfterDefend() { SetState(KOOPA_STATE_COMEBACK); }

	void BeHold();
	void BeKick() { SetState(KOOPA_STATE_IS_KICKED); }

	BOOLEAN IsMarioKicked() { return is_mario_kicked; }

	void MoveRight() { SetState(MONSTER_STATE_WALKING_RIGHT); }
	void MoveLeft() { SetState(MONSTER_STATE_WALKING_LEFT); }

	// reset to default state
	void Reset();

	void Die() { SetState(MONSTER_STATE_DIE); }
};
