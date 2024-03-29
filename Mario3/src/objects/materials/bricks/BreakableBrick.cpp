#include "BreakableBrick.h"
#include "scenes/PlayScene.h"

#include "objects/items/Coin.h"
#include "objects/items/BreakableBrickSwitch.h"
#include <objects/Mario.h>

void CBreakableBrick::CreateItem()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

	switch (item_type) {
	case BREAKABLE_BRICK_COIN:
		CCreatableBrick::CreateItem(new CCoin());
		break;
	case BREAKABLE_BRICK_NONE:
		break;
	case BREAKABLE_BRICK_BUTTON:
		if (is_created_switch) break;
		((CBreakableBrickSwitch*)CCreatableBrick::CreateItemBehind(
			new CBreakableBrickSwitch(
				x,
				y,
				y - (BREAKABLE_BRICK_BBOX_HEIGHT + BREAKABLE_BRICK_SWITCH_BBOX_HEIGHT) / 2))
			)->MoveOutBreakablerBrickSwitch();
		is_created_switch = TRUE;
		break;
	default:
		DebugOut(L"[ERROR] Can not handle item_type of question brick in CQuestionBrick::CreateItem(int state): ", item_type);
		break;
	}
}

void CBreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BREAKABLE_BRICK_BBOX_WIDTH / 2;
	top = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2;
	right = left + BREAKABLE_BRICK_BBOX_WIDTH;
	bottom = top + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
	if (mario && mario->IsPressedButtonBreakAbleBrick())
	{
		SetState(BREAKABLE_BRICK_STATE_DISAPPEAR);
		return;
	}

	CCollision::GetInstance()->Process(this, dt, co_objects);

	// the brick is blocked by something
	// so it can't bounce
	if (is_blocked)
	{
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
		is_blocked = FALSE;
		return;
	}
	vx += ax * dt;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;

	// make sure that the brick can't fall
	if (y >= start_y)
	{
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
	}
}

void CBreakableBrick::Render()
{
	if (!IsInCamera()) return; // lazy load

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION animation = animations->Get(ID_ANI_BREAKABLE_BRICK);
	if (animation != nullptr)
		animation->Render(x, y);
}

void CBreakableBrick::SetState(int state)
{
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_BREAK:
	{
		is_breaked = TRUE;
		int number_debris_brick = breakable_brick_gen_debris(number_debris);
		for (int i = 0; i < number_debris_brick; i++)
		{
			((CDebrisBrick*)CCreatableBrick::CreateItem(new CDebrisBrick()))->Splash();
		}
		is_deleted = TRUE;
	}
	break;
	case BREAKABLE_BRICK_STATE_BOUNCE:
		if (item_type == BREAKABLE_BRICK_BUTTON)
		{
			vy = 0;
			ay = 0;
			CreateItem();
			break;
		}
		vy = -BREAKABLE_BRICK_SPEED;
		ay = BREAKABLE_BRICK_GRAVITY;

		break;
	case BREAKABLE_BRICK_STATE_NORMAL:
		y = start_y;
		x = start_x;
		vy = 0;
		ay = 0;
		ax = 0;
		vx = 0;
		break;
	case BREAKABLE_BRICK_STATE_DISAPPEAR:
		if (item_type == BREAKABLE_BRICK_BUTTON) return;
		is_deleted = TRUE;
		is_breaked = TRUE;
		CreateItem();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}

void CBreakableBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->IsCollidedFromBottom() && e->obj->IsBlocking())
		is_blocked = TRUE;
}

void CBreakableBrick::Bounce()
{
	SetState(BREAKABLE_BRICK_STATE_BOUNCE);
}

void CBreakableBrick::Break()
{
	SetState(BREAKABLE_BRICK_STATE_BREAK);
}

void CBreakableBrick::BeMarioHit()
{
	if (is_breaked) return;
	if (item_type == BREAKABLE_BRICK_BUTTON) {
		Bounce();
		return;
	}
	Break();
}