#include "MushRoom.h"
#include "objects/Platform.h"
#include "scenes/PlayScene.h"
#include "objects/Mario.h"

// not work now because the code dirty in the update function in playscene file
void CMushroom::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	CMario* mario = (CMario*)e->obj;

	if (mario->IsSmall())
	{
		mario->Zoom();
		is_deleted = true;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (!IsInCamera()) return; // lazy update

	//	NOTE: need to create a general function for this code
	// move out of screen >> delete
	// fall to to the hole >> delete
	if (x + GetWidth() <= 0 || y > SCREEN_HEIGHT)
	{
		is_deleted = true;
		return;
	}

	CItem::Update(dt, coObjects);
}

void CMushroom::Render()
{
	if (!IsInCamera()) return;

	int ani_id = ID_ANI_MUSHROOM_RED;
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
		ani_id = ID_ANI_MUSHROOM_RED;
		break;
	default:
		DebugOut(L"[ERROR] In CMushRoom::Render animation id = %d", ani_id);
		break;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani_id)->Render(x, y);
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::SetState(int state)
{
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = (CMario*)scene->GetPlayer();

		vx = x < mario->GetX() ? MUSHROOM_SPEED : -MUSHROOM_SPEED;
	}
	break;
	}
	CGameObject::SetState(state);
}

void CMushroom::BeCollect()
{
	CItem::BeCollect();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (mario->IsBig()) return;

	// if mario is small, then zoom and delete mushroom
	mario->Zoom();
	is_deleted = true;
}