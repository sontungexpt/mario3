#include "MushRoom.h"
#include "Platform.h"
#include "scenes/PlayScene.h"
#include "Mario.h"

CMushRoom::CMushRoom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	vy = 0;
	state = MUSHROOM_RED;
	start_y = y;
	//SetState(MUSHROOM_STATE_OUTSIDE);
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (!IsInCamera()) return; // lazy update

	LPSCENE curr_scene = CGame::GetInstance()->GetCurrentScene();
	if (curr_scene == NULL) {
		DebugOut(L"[ERROR] In CMushRoom::Update, scene is NULL\n");
		return;
	}
	CMario* mario = (CMario*)((LPPLAYSCENE)curr_scene)->GetPlayer();
	if (mario == NULL) {
		DebugOut(L"[ERROR] In CMushRoom::Update, mario is NULL\n");
		return;
	}

	if (mario->GetState() == MARIO_LEVEL_BIG) return; // big mario can't eat mushroom

	if (state == MUSHROOM_STATE_WALKING) {
		vy += ay * dt;
		vx += ax * dt;
	}
	else if (state == MUSHROOM_STATE_OUTSIDE) {
		if (start_y - y < MUSHROOM_BBOX_HEIGHT) {
			vy = OUT_BRICK;
			vx = 0;
		}
		else SetState(MUSHROOM_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CMushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

//void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
//	if (!e->obj->IsPlayer()) {
//		if (e->ny != 0)
//		{
//			vy = 0;
//		}
//		else if (e->nx != 0)
//		{
//			vx = -vx;
//		}
//	}
//
//	if (dynamic_cast<CMushRoom*>(e->obj)) {}
//	else if (dynamic_cast<CPlatform*>(e->obj))
//		OnCollisionWithPlatForm(e);
//}

void CMushRoom::Render()
{
	if (!IsInCamera()) return;

	CAnimations* animations = CAnimations::GetInstance();

	int ani_id = -1;
	//if (model == MUSHROOM_RED) ani_id = ID_ANI_MUSHROOM_RED;
	//if (model == MUSHROOM_GREEN) ani_id = ID_ANI_MUSHROOM_GREEN;

	if (ani_id == -1) {
		DebugOut(L"[ERROR] In CMushRoom::Render, ani_id is -1\n");
		return;
	}

	animations->Get(ani_id)->Render(x, y);
}

void CMushRoom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}

//void CMushRoom::SetState(int state)
//{
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//
//	switch (state)
//	{
//	case MUSHROOM_STATE_WALKING:
//		if (x < mario->GetX()) vx = -MUSHROOM_SPEED;
//		else vx = MUSHROOM_SPEED;
//		break;
//	}
//	CGameObject::SetState(state);
//}