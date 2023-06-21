#include "configs/monsters/Koopa601000.h"
#include "Monster.h"

class CKoopa : public CMonster
{
private:
	ULONGLONG defend_time;
	ULONGLONG comeback_time;

	BOOLEAN is_defend;
	BOOLEAN is_comback;
	BOOLEAN is_mario_kicked;
	BOOLEAN is_mario_holding;
	BOOLEAN is_on_platform;

	float limit_x_positive = 0;
	float limit_x_negative = 0;

	float mario_speed_when_kicked;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

	void AdjustPos();

public:
	CKoopa(float x, float y) : CMonster(x, y) {
		is_defend = FALSE;
		is_comback = FALSE;
		is_mario_kicked = FALSE;
		is_mario_holding = FALSE;
		is_on_platform = FALSE;

		mario_speed_when_kicked = 0.0f;
		max_vx = KOOPA_MAX_SPEED;

		defend_time = -1;
		comeback_time = -1;
		// always move to mario in the first time
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	//core
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//collision
	void OnCollisionWith(LPCOLLISIONEVENT e);

	// this part is a other name for the same state
	BOOLEAN IsDefend() { return is_defend; }
	void Defend() { SetState(KOOPA_STATE_DEFEND); };
	void CombackAfterDefend() { SetState(KOOPA_STATE_COMEBACK); };

	void BeKick(float v) {
		mario_speed_when_kicked = v;
		SetState(KOOPA_STATE_IS_KICKED);
	};
	BOOLEAN IsMarioKicked() { return is_mario_kicked; }

	void BeHold() { SetState(KOOPA_STATE_IS_HOLDING); }

	void MoveRight() { SetState(MONSTER_STATE_WALKING_RIGHT); };
	void MoveLeft() { SetState(MONSTER_STATE_WALKING_LEFT); };

	// reset to default state
	void Reset();
	void Die() { SetState(MONSTER_STATE_DIE); }
};
