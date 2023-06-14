#include "Coin.h"
#include "objects/materials/Brick.h"
#include "debug.h"
#include "objects/Mario.h"

void CCoin::OnNoCollision(DWORD dt)
{
	if (isDeleted) return;
	x += vx * dt;
	y += vy * dt;
}

void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	// make sure that the coin will not meet mario by collision framework
	if (e->obj->IsBlocking())
	{
		SetState(COIN_STATE_IDLE);
	}
}

void CCoin::Render()
{
	if (isDeleted) return; // nothing to render
	if (!IsInCamera()) return; // lazy load

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case COIN_STATE_IDLE:
		vx = vy = ax = ay = 0;
		break;
	case COIN_STATE_JUMP_OUT_QUESTION_BRICK:
		vx = 0;
		ay = COIN_GRAVITY;
		vy = -COIN_JUMP_OUT_QUESTION_BRICK_SPEED_Y;

		// max_height_zoom = (0 - v0^2) / 2a (a< 0)
		collect_y = y - (-(vy * vy) / (2 * (-COIN_GRAVITY))) * 1 / 2;
		break;
	}
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	// when coin is jump to max height, it's time to collect
	if (!is_collected && y < collect_y) Collect();

	if (is_collected && y >= collect_y)
	{
		isDeleted = TRUE;
		return;
	}

	if (!IsInCamera()) return;

	// not moving
	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDeleted) return; // nothing to get

	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}