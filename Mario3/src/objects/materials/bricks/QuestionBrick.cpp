#include "scenes/PlayScene.h"

#include "QuestionBrick.h"
#include "objects/Mario.h"

#include "objects/items/Coin.h"
#include "objects/items/Mushroom.h"
#include "objects/items/Leaf.h"
#include "objects/items/LifeUpMushroom.h"

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!is_unboxed) return;

	vx += ax * dt;
	vy += ay * dt;

	CCollision::GetInstance()->Process(this, dt, co_objects);
}

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	// if it is not unboxed, it will not bounce
	if (!is_unboxed) return;

	x += vx * dt;
	y += vy * dt;

	// make sure that the question brick can't fall
	if (y >= start_y)
		Disable();
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
		if (is_unboxed) return;

		is_unboxed = TRUE;
		vy = -QUESTION_BRICK_SPEED;
		ay = QUESTION_BRICK_GRAVITY;
		CreateItem();
	}
	break;
	case QUESTION_BRICK_STATE_DISABLED:
		y = start_y;
		vy = 0;
		ay = 0;
		ax = 0;
		vx = 0;
		break;
	}
}

CItem* CQuestionBrick::CreateItem(CItem* item) {
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	item->SetPosition(GetItemReferenceX(item), GetItemReferenceY(item));
	return (CItem*)scene->AddObject(item);
}

void CQuestionBrick::CreateItem()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

	// x and y of item
	switch (item_type) {
	case QUESTION_BRICK_COIN:
	{
		((CCoin*)CreateItem(new CCoin()))->JumpOutQuestionBrick();
	}
	break;
	case QUESTION_BRICK_ITEM_SUPPORT:
	{
		CMario* mario = (CMario*)scene->GetPlayer();
		if (!mario->IsSmall())
			((CLeaf*)CreateItem(new CLeaf()))->Fly();
		else
			((CMushroom*)CreateItem(new CMushroom()))->Walk();
	}
	break;
	case QUESTION_BRICK_MUSHROOM_LIFE_UP:
		((CLifeUpMushroom*)CreateItem(new CLifeUpMushroom()))->Walk();
		break;
	case QUESTION_BRICK_NONE:
		break;
	default:
		DebugOut(L"[ERROR] Can not handle item_type of question brick in CQuestionBrick::CreateItem(int state): ", item_type);
		break;
	}
}