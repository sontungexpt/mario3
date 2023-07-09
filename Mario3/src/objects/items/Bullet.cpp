#include "scenes/PlayScene.h"

#include "Bullet.h"
#include "configs/Mario.h"
#include "objects/Platform.h"
#include "objects/Mario.h"

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!IsInCamera()) return; // lazy load
	CItem::Update(dt, co_objects);
}

float CBullet::CalculateVx(float target_x, float target_y)
{
	float distance_x = target_x - x;
	float distance_y = target_y - y;

	float alpha = atan(fabs(distance_y) / fabs(distance_x));

	float v_x = BULLET_SPEED * cos(alpha); // v>0 because 0< alpha < 90 degree

	return distance_x >= 0 ? v_x : -v_x;
}

float CBullet::CalculateVy(float target_x, float target_y)
{
	float distance_x = target_x - x;
	float distance_y = target_y - y;

	float alpha = atan(fabs(distance_y) / fabs(distance_x));

	float v_y = BULLET_SPEED * sin(alpha); // v > 0 because 0 < alpha < 90 degree

	return distance_y > 0 ? v_y : -v_y;
}

void CBullet::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	BeCollected();
}

void CBullet::Render()
{
	if (!IsInCamera()) return;

	int aniId = -1;
	if (fabs(vx) > 0)
		aniId = ID_ANI_BULLET;

	if (aniId == -1)
	{
		DebugOut(L"[ERROR FROM BULLET CLASS] No animation found");
		return; // not in any animation
	}

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
}

void CBullet::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BULLET_STATE_SHOOT:
		vx = CalculateVx(target_x, target_y);
		vy = CalculateVy(target_x, target_y);
		break;
	default:
		DebugOut(L"[ERROR] Can not handle state %d", state);
		break;
	}
}

void CBullet::Shoot(float target_x, float target_y)
{
	this->target_x = target_x;
	this->target_y = target_y;

	SetState(BULLET_STATE_SHOOT);
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBullet::BeCollected()
{
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());

	CMario* mario = scene ? dynamic_cast<CMario*>(scene->GetPlayer()) : nullptr;
	if (!mario) return;

	CItem::BeCollected();
	mario->Die();
}