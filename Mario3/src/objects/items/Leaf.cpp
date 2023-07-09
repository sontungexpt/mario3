#include "scenes/PlayScene.h"
#include "GameData.h"

#include "Leaf.h"
#include "objects/Mario.h"
#include "objects/materials/EffectManager.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (IsOutBottomCamera()) return;

	// how to know vx and ax just use physical
	// v^2 -v0^2 = 2as
	// v = v0 + at

	// Check if leaf should fall down
	if (!is_falling && start_y - y >= LEAF_MAX_FLY_HEIGHT)
	{
		is_falling = TRUE;
		nx = 1; // default right first

		vy = 0;
		vx = LEAF_SPEED_X;
		ax = -LEAF_ADJUST_AX_WHEN_FALL;
	}

	if (is_falling && upward_wind_chance_distribution(has_upward_wind) == LEAF_UPWARD_WIND_CHANCE)
	{
		vy -= LEAF_WIND_POWER_SPPED_Y;
	}

	// Change direction when reaching edge
	if (nx > 0 && vx <= 0)
	{
		nx = -1;

		vx = -wind_speed_generator(wind_speed) * LEAF_SPEED_X;
		ax = LEAF_ADJUST_AX_WHEN_FALL;
	}
	else if (nx < 0 && vx >= 0)
	{
		nx = 1;

		vx = wind_speed_generator(wind_speed) * LEAF_SPEED_X;
		ax = -LEAF_ADJUST_AX_WHEN_FALL;
	}

	CItem::Update(dt, co_objects);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	BeCollected();
}

void CLeaf::Render()
{
	if (!IsInCamera()) return;

	CAnimations* animations = CAnimations::GetInstance();
	if (vx < 0) animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y);
	else if (vx >= 0) animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_FLY:
		start_y = y;
		is_falling = FALSE;

		vy = -LEAF_SPEED_Y;
		ay = LEAF_GRAVITY;
		ax = 0;
		nx = 0; // no direction first
		break;
	}

	CGameObject::SetState(state);
}

void CLeaf::BeCollected()
{
	if (is_collected) return;
	CItem::BeCollected();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (mario->IsBig())
		mario->GrowTail();

	CEffectManager::Gennerate(this, POINT_1000);
	CGameData::GetInstance()->IncreasePointBy(1000);
	is_deleted = true;
}