#include "configs/Koopa.h"
#include "Monster.h"

class CKoopa : public CMonster
{
private:
	ULONGLONG defend_start;
	//ULONGLONG comeback_start;

	//bool isUpside;
	//bool isDefend;
	//bool isHeld;
	//bool isKicked;
	//bool isWing;
	//bool isOnPlatform;
	//bool isComeback;
public:
	CKoopa(float x, float y) : CMonster(x, y) {};

	//void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int PositionWithMario();
	int IsCollidable() { return !dead; };
	virtual int IsEnemy() { return 1; }
};
