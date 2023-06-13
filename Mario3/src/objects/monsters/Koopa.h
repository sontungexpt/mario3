#include "configs/Koopa130000.h"
#include "Monster.h"

class CKoopa : public CMonster
{
private:
	ULONGLONG defend_start;

	BOOLEAN is_defend;
	BOOLEAN is_mario_kicked;

	void OnCollisionWithMonster(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y) : CMonster(x, y) {
		is_defend = FALSE;
		is_mario_kicked = FALSE;

		// always move to mario in the first time
		SetState(MONSTER_STATE_WALKING_LEFT);
	};

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void SetState(int state);

	//int GetPositionWithMario() { return x; }
};
