#include "Leaf.h"
#include <scenes/PlayScene.h>
#include <objects/Mario.h>
#include <random>
#include "objects/materials/EffectManager.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (IsOutBottomCamera()) return;

	// how to know vx and ax just use physical
	// v^2 -v0^2 = 2as
	// v = v0 + at

	// can not fly higher
	if (!is_falling && start_y - y >= LEAF_MAX_FLY_HEIGHT)
	{
		is_falling = TRUE;
		is_moved_right = TRUE;
		is_moved_left = FALSE;

		vy = 0;
		vx = LEAF_SPEED_X;
		ax = -LEAF_ADJUST_AX_WHEN_FALL;
	}

	// sometimes the wind blows upwards
	// so leaves fly higher than usual
	random_device int_gen;
	uniform_int_distribution<int> int_distribution(0, 7);
	if (is_falling && int_distribution(int_gen) == 3)
	{
		vy -= LEAF_WIND_POWER_SPPED_Y;
	}

	if (is_moved_right && vx <= 0)
	{
		is_moved_right = FALSE;
		is_moved_left = TRUE;

		// Wind speed is also never fixed
		// so leaves fly at an unknown initial speed
		default_random_engine wind_power;
		uniform_real_distribution<float> distribution(1.1f, 1.5f);

		vx = -distribution(wind_power) * LEAF_SPEED_X;
		ax = LEAF_ADJUST_AX_WHEN_FALL;
	}
	else if (is_moved_left && vx >= 0)
	{
		is_moved_right = TRUE;
		is_moved_left = FALSE;

		// Wind speed is also never fixed
		// so leaves fly at an unknown initial speed
		default_random_engine wind_power;
		uniform_real_distribution<float> distribution(1.1f, 1.5f);

		vx = distribution(wind_power) * LEAF_SPEED_X;
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

void CLeaf::OnCollisionWithPlayer(LPCOLLISIONEVENT e) {
	CItem::BeCollected();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (mario->IsBig())
	{
		mario->GrowTail();
		is_deleted = true;
	}
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
		is_moved_right = FALSE;
		is_moved_left = FALSE;

		vy = -LEAF_SPEED_Y;
		ay = LEAF_GRAVITY;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CLeaf::BeCollected()
{
	CItem::BeCollected();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();

	if (mario->IsBig())
	{
		CEffectManager::Gennerate(this, POINT_100, 0.0f);

		mario->GrowTail();
		is_deleted = true;
	}
}