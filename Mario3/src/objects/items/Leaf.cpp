#include "Leaf.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CItem::Update(dt, co_objects);

	/*if (isOnPlatForm) {
		vy = 0;
		ay = 0;
	}
	else {
		if (vy < MAX_VY) {
			vy += ay * dt;
		}
		else vy = ay * dt;
		if (vy > 0) {
			if (vx <= ADJUST_MAX_VX) {
				vx += ax * dt;
			}
			else vx = -vx;
		}
	}*/
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

//void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
//	if (dynamic_cast<CLeaf*>(e->obj)) return;
//
//	if (e->ny != 0)
//	{
//		isOnPlatForm = true;
//		vy = 0;
//		vx = 0;
//	}
//	else if (dynamic_cast<CPlatform*>(e->obj))
//		OnCollisionWithPlatForm(e);
//}

//void CLeaf::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
//{
//	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
//	if (platform->IsBlocking()) {}
//	else if (e->ny < 0) {
//		SetY(platform->GetY() - LEAF_BBOX_HEIGHT);
//		isOnPlatForm = true;
//	}
//}

void CLeaf::Render()
{
	if (!IsInCamera()) return;

	CAnimations* animations = CAnimations::GetInstance();
	if (vx <= 0) animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
	else if (vx > 0) animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_FALL:
		ax += ADJUST_AX_WHEN_FALL;
		break;
	case LEAF_STATE_FLY:
		ax = 0;

		/*vx = LEAF_FLY_SPEED_X;
		vy = LEAF_FLY_SPEED_Y;*/
		break;
	}

	CGameObject::SetState(state);
}