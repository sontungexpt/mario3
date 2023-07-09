#include "DebrisBrick.h"

void CDebrisBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - DEBRIS_BRICK_BBOX_WIDTH / 2;
	top = y - DEBRIS_BRICK_BBOX_HEIGHT / 2;
	right = x + DEBRIS_BRICK_BBOX_WIDTH;
	bottom = y + DEBRIS_BRICK_BBOX_HEIGHT;
}

void CDebrisBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (GetTickCount64() - time_debris_splashing_start > DEBRIS_BRICK_TIME_SPLASHING)
	{
		is_deleted = TRUE;
		return;
	}
	CItem::Update(dt, co_objects);
}
void CDebrisBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->IsCollidedInYDimension())
		vy = -vy;

	if (e->IsCollidedInXDimension())
	{
		vx = -vx;
		ax = -ax;
	}
}

void CDebrisBrick::Render()
{
	if (!IsInCamera()) return; // lazy load

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION animation = animations->Get(ID_ANI_DEBRIS_BRICK_SPLASING);
	if (animation != nullptr)
		animation->Render(x, y);
}

void CDebrisBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case DEBRIS_BRICK_STATE_SPLASHING:
	{
		time_debris_splashing_start = GetTickCount64();

		float random_vx = debris_brick_speed_generator(debris_brick_speed);
		float random_vy = debris_brick_speed_generator(debris_brick_speed);
		vx = debris_brick_direction_generator(debris_brick_direction) ? random_vx : -random_vx;
		vy = debris_brick_direction_generator(debris_brick_direction) ? random_vy : -random_vy;

		ay = GRAVITY;
		ax = 0;
	}
	break;
	default:
		break;
	}
}