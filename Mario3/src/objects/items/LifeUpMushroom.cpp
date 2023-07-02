#include "LifeUpMushroom.h"
#include "objects/Mario.h"
#include "objects/materials/EffectManager.h"

void CLifeUpMushroom::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	BeCollected();
}

void CLifeUpMushroom::Render()
{
	if (!IsInCamera()) return;

	int ani_id = -1;
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
		ani_id = ID_ANI_MUSHROOM_GREEN;
		break;
	default:
		DebugOut(L"[ERROR] In CMushRoom::Render animation id = %d", ani_id);
		return;
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani_id)->Render(x, y);
}

void CLifeUpMushroom::BeCollected()
{
	if (is_collected) return;
	CItem::BeCollected();
	CEffectManager::GetInstance()->Gennerate(this, LIFE_UP);
	CGameData::GetInstance()->IncreaseLifeBy1();
	is_deleted = true;
}