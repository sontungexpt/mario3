#include "BreakableBrick.h"
#include "scenes/PlayScene.h"

#include "objects/items/Coin.h"
#include "objects/items/DebrisBrick.h"

#include <cstdlib>
#include <ctime>
#include <random>
void CBreakableBrick::CreateItem()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

	switch (item_type) {
	case BREAKABLE_BRICK_COIN:
		CCreatableBrick::CreateItem(new CCoin());
		break;
	case BREAKABLE_BRICK_NONE:
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
	vx += ax * dt;
	vy += ay * dt;
	x += vx * dt;
	y += vy * dt;

	// make sure that the brick can't fall
	if (y >= start_y)
	{
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
	}

	CCollision::GetInstance()->Process(this, dt, co_objects);
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
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_BREAK:
	{
		is_breaked = TRUE;
		srand(time(NULL));
		random_device int_gen;
		uniform_int_distribution<int> int_distribution(BREAKABLE_BRICK_MIN_DEBRIS_BRICK, BREAKABLE_BRICK_MAX_DEBRIS_BRICK);
		int number_debris_brick = int_distribution(int_gen);
		for (int i = 0; i < number_debris_brick; i++)
		{
			((CDebrisBrick*)CCreatableBrick::CreateItem(new CDebrisBrick()))->Splash();
		}
		CreateItem();
		is_deleted = TRUE;
		break;
	}
	break;
	case BREAKABLE_BRICK_STATE_BOUNCE:
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
	}
}

void CBreakableBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->IsCollidedInYDimension() && e->obj->IsBlocking())
	{
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
	}
}