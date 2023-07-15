#include "BreakableBrickSwitch.h"
#include <scenes/PlayScene.h>
#include <objects/Mario.h>

void CBreakableBrickSwitch::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	if (e->IsCollidedFromBottom())
		BeCollected();
}

void CBreakableBrickSwitch::Render()
{
	if (is_collected)
		CAnimations::GetInstance()->Get(ID_ANI_BREAKABLE_BRICK_SWITCH_PRESSED)->Render(x, y);
	else
		CAnimations::GetInstance()->Get(ID_ANI_BREAKABLE_BRICK_SWITCH)->Render(x, y);
}

void CBreakableBrickSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (y < min_y)
	{
		SetState(BREAKABLE_BRICK_SWITCH_STATE_NORMAL);
	}
	CItem::Update(dt, co_objects);
}

void CBreakableBrickSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BREAKABLE_BRICK_SWITCH_BBOX_WIDTH / 2;
	r = l + BREAKABLE_BRICK_SWITCH_BBOX_WIDTH;
	if (is_collected)
	{
		t = y - BREAKABLE_BRICK_SWITCH__PRESSED_BBOX_HEIGHT / 2;
		b = t + BREAKABLE_BRICK_SWITCH__PRESSED_BBOX_HEIGHT;
		return;
	}
	t = y - BREAKABLE_BRICK_SWITCH_BBOX_HEIGHT / 2;
	b = t + BREAKABLE_BRICK_SWITCH_BBOX_HEIGHT;
}

void CBreakableBrickSwitch::MoveOutBreakablerBrickSwitch()
{
	SetState(BREAKABLE_BRICK_SWITCH_STATE_MOVING);
}

void CBreakableBrickSwitch::SetState(int state)
{
	switch (state)
	{
	case BREAKABLE_BRICK_SWITCH_STATE_NORMAL:
		vy = 0;
		ay = 0;
		break;
	case BREAKABLE_BRICK_SWITCH_STATE_MOVING:
		vy = -BREAKABLE_BRICK_SWITCH_VY;
		ay = 0;
		break;
	}
	CItem::SetState(state);
}

void CBreakableBrickSwitch::BeCollected()
{
	if (is_collected) return;
	y += (BREAKABLE_BRICK_SWITCH_BBOX_HEIGHT - BREAKABLE_BRICK_SWITCH__PRESSED_BBOX_HEIGHT) / 2; // adjust position
	CItem::BeCollected();
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
	if (mario) mario->PressButtonBreakAbleBrick();
}