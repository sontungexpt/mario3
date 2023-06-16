#include "Leaf.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	// if have time we should use phýycal for this it will make the game more real
	if (!IsInCamera())return;

	if (!is_falling && fabs(start_y - y) >= LEAF_MAX_FLY_HEIGHT)
	{
		vy = 0;
		ax = LEAF_ADJUST_AX_WHEN_FALL;
		is_falling = TRUE;
	}

	if (fabs(x - start_x) >= LEAF_MAX__FALING_WIDTH)
	{
		vx = -vx;
		ax = -ax;
	}

	if (fabs(vx) > LEAF_ADJUST_MAX_VX)
		vx = vx > 0 ? LEAF_ADJUST_MAX_VX : -LEAF_ADJUST_MAX_VX;

	CItem::Update(dt, co_objects);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnCollisionWithPlayer(LPCOLLISIONEVENT e) {}

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
	case LEAF_STATE_FLY:
		start_y = y;
		start_x = x;
		is_falling = FALSE;
		vy = -LEAF_SPEED_Y;
		ay = LEAF_SPEED_FALLING;
		break;
	}

	CGameObject::SetState(state);
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->obj->IsBlocking())
	{
		this->SetIsCollidable(0);
		return;
	}
	this->SetIsCollidable(1);

	CItem::OnCollisionWith(e);
}