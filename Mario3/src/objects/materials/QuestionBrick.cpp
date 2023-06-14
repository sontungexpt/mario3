#include "scenes/PlayScene.h"

#include "QuestionBrick.h"
#include "objects/Mario.h"
#include "objects/items/Coin.h"

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!is_unboxed)return;

	vx += ax * dt;
	vy += ay * dt;

	CGameObject::Update(dt, co_objects);
	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	// the brick is unboxed
	// so it can move anywhere
	if (!is_unboxed) return;

	x += vx * dt;
	y += vy * dt;

	if (y > orginal_y)
	{
		Disable();
	}
}

void CQuestionBrick::Render()
{
	if (!IsInCamera()) return; // lazy load

	int aniId = ID_ANI_QUESTION_BRICK;

	switch (state) {
	case QUESTION_BRICK_STATE_DISABLED:
		aniId = ID_ANI_QUESTION_BRICK_DISABLED;
		break;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_UNBOXING:
	{
		is_unboxed = TRUE;
		orginal_y = y;

		// this is the first velocity of brick  when mario collides with the brick
		vy = -QUESTION_BRICK_SPEED;
		ay = QUESTION_BRICK_GRAVITY;

		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		// x and y of item
		switch (item_type) {
		case QUESTION_BRICK_COIN:
		{
			float item_x, item_y;

			float x_axis_centroid_brick = x + QUESTION_BRICK_BBOX_WIDTH / 2;

			// don't know why it deflect to right
			item_x = x_axis_centroid_brick - (COIN_BBOX_WIDTH / 2) - 1;
			item_y = this->y - COIN_BBOX_HEIGHT;

			CCoin* coin = (CCoin*)scene->AddObject(new CCoin(item_x, item_y));
			coin->SetPosition(item_x, item_y);
			coin->JumpOutQuestionBrick();
		}
		break;
		}
	}
	break;
	case QUESTION_BRICK_STATE_DISABLED:
		vy = 0;
		y = orginal_y;
		break;
	}
}