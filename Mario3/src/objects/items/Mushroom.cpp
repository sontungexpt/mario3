#include "MushRoom.h"
#include "objects/Platform.h"
#include "scenes/PlayScene.h"
#include "objects/Mario.h"
#include "objects/materials/EffectManager.h"
#include <GameData.h>

void CMushroom::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	BeCollected();
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	RemoveWhenMoveToDangerousSpace();
	if (!IsInCamera()) return; // lazy update

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
		return;
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
		LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;

		vx = mario && x < mario->GetX() ? MUSHROOM_SPEED : -MUSHROOM_SPEED;
	}
	break;
	}
	CGameObject::SetState(state);
}

void CMushroom::BeCollected()
{
	if (is_collected) return;
	CItem::BeCollected();
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;

	if (mario && mario->IsSmall())
		mario->Zoom();

	CEffectManager::GetInstance()->Gennerate(this, POINT_1000);
	CGameData::GetInstance()->IncreasePointBy(1000);

	is_deleted = true;
}