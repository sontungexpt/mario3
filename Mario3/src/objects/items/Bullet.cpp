#include "Bullet.h"
#include "configs/Mario.h"
#include "objects/Platform.h"

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CItem::Update(dt, co_objects);
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())
	{
		this->SetIsColliable(0);
		return;
	}
	this->SetIsColliable(1);

	CItem::OnCollisionWith(e);
}

void CBullet::Render()
{
	if (!IsInCamera()) return;

	int aniId = -1;
	if (fabs(vx) > 0)
		aniId = ID_ANI_BULLET;

	if (aniId == -1)
	{
		DebugOut(L"[ERROR FROM BULLET CLASS] No animation found");
		return; // not in any animation
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CBullet::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BULLET_STATE_SHOOT:
		vx = CalulateVx(target_x, target_y);
		vy = CalulateVy(target_x, target_y);
		break;
	default:
		DebugOut(L"[ERROR] Can not handle state %d", state);
		break;
	}
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}