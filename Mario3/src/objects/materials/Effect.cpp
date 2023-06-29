#include "Effect.h"
#include "scenes/PlayScene.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == EFFECT_STATE_APPEAR && GetTickCount64() - appear_time_start > EFFECT_TIMEOUT)
	{
		is_deleted = TRUE;
		return;
	}
	y -= vy * dt;
}

void CEffect::Render()
{
	int aniId = -1;
	switch (type)
	{
	case  POINT_100:
		aniId = EFFECT_ANI_ID_100_POINT;
		break;
	case POINT_200:
		aniId = EFFECT_ANI_ID_200_POINT;
		break;
	case POINT_400:
		aniId = EFFECT_ANI_ID_400_POINT;
		break;
	case POINT_800:
		aniId = EFFECT_ANI_ID_800_POINT;
		break;
	case POINT_1000:
		aniId = EFFECT_ANI_ID_1000_POINT;
		break;
	case POINT_2000:
		aniId = EFFECT_ANI_ID_2000_POINT;
		break;
	case POINT_4000:
		aniId = EFFECT_ANI_ID_4000_POINT;
		break;
	case POINT_8000:
		aniId = EFFECT_ANI_ID_8000_POINT;
		break;
	case LIFE_UP:
		aniId = EFFECT_ANI_ID_1UP;
	default:
		DebugOut(L"can not handle type %d\n", type);
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);
	if (ani != nullptr)
		ani->Render(x, y);
}

void CEffect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECT_STATE_APPEAR:
		appear_time_start = GetTickCount64();
		break;
	default:
		break;
	}
}

void CEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	switch (type)
	{
	case  POINT_100:
	case POINT_200:
	case POINT_400:
	case POINT_800:
		left = x - POINT_3_CHAR_BBOX_WIDTH / 2;
		top = y - POINT_BBOX_HEIGHT / 2;
		right = left + POINT_3_CHAR_BBOX_WIDTH;
		bottom = top + POINT_BBOX_HEIGHT;
		break;
	case POINT_1000:
	case POINT_2000:
	case POINT_4000:
	case POINT_8000:
		left = x - POINT_4_CHAR_BBOX_WIDTH / 2;
		top = y - POINT_BBOX_HEIGHT / 2;
		right = left + POINT_4_CHAR_BBOX_WIDTH;
		bottom = top + POINT_BBOX_HEIGHT;
		break;
	case LIFE_UP:
		left = x - LIFE_UP_BBOX_WIDTH / 2;
		top = y - LIFE_UP_BBOX_HEIGHT / 2;
		right = left + LIFE_UP_BBOX_WIDTH;
		bottom = top + LIFE_UP_BBOX_HEIGHT;
	}
}