#include "Effect.h"
#include "scenes/PlayScene.h"
#include "configs/GameObject.h"
#include "objects/Mario.h"

using namespace std;

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (effect == EFFECT_FADE_OUT)
	{
		if (state == EFFECT_STATE_APPEAR && GetTickCount64() - appear_time_start > EFFECT_TIMEOUT)
		{
			is_deleted = TRUE;
			return;
		}
		y -= vy * dt;
	}
	else if (effect == EFFECT_DISAPPEAR)
	{
		if (state == EFFECT_STATE_APPEAR && GetTickCount64() - appear_time_start > EFFECT_TIMEOUT)
		{
			is_deleted = TRUE;
			return;
		}
	}
	else if (effect == EFFECT_CHANGE_SCREEN)
	{
		if (GetTickCount64() - increase_alpha_time_start > EFFECT_INCREASING_ALPHA_DURATION)
		{
			increase_alpha_time_start = GetTickCount64();
			alpha += 0.009f;
		}
	}
	else if (effect == EFFECT_START_FOLLOW_PLAYER)
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

		CMario* mario = (CMario*)scene->GetPlayer();
		if (mario) {
			float distance_x = fabs(mario->GetX() - x);
			float distance_y = fabs(mario->GetY() - y);

			float atan = distance_y / distance_x;

			x = mario->GetX() > x ?
				x + 3.0f : x - 3.0f;

			y = mario->GetY() > y ?
				y + 3.0f * atan : y - 3.0f * atan;

			if (fabs(mario->GetX() - x) < mario->GetWidth() || fabs(mario->GetY() - y) < mario->GetHeight())
			{
				x = mario->GetX();
				y = mario->GetY();
			}

			if (x == mario->GetX() && y == mario->GetY())
			{
				is_deleted = TRUE;
				return;
			}
		}
	}
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
		break;
	case HELP_LEVEL_MAP:
		aniId = EFFECT_ANI_ID_HELP_LEVEL_MAP;
		break;
	case CHANGE_SCENE:
		RenderChangeScreenEffect();
		return;
	case START_FOLLOW_PLAYER:
		RenderStartFollowPlayerEffect();
		return;
	default:
		DebugOut(L"can not handle type %d\n", type);
		return;
	}
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);
	if (ani != nullptr)
		ani->Render(x, y);
}

void CEffect::RenderStartFollowPlayerEffect()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario)
	{
		constexpr float PI = 3.14159265;

		float radius = fabs(x - mario->GetX());

		for (int i = 1; i <= 6; i++)
		{
			float angle = 60.0f / 180.f * (i - 1) * PI;
			float xi = x + radius * cos(angle);
			float yi = y - radius * sin(angle);
			CAnimations::GetInstance()->Get(EFFECT_ANI_ID_START)->Render(xi, yi);
		}
	}
}

void CEffect::RenderChangeScreenEffect()
{
	CGame* game = CGame::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);

	float xx = cx + game->GetBackBufferWidth() / 2;
	float yy = cy + game->GetBackBufferHeight() / 2;

	D3DXVECTOR3 p(xx, yy, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX_BLACK);

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)game->GetBackBufferWidth();
	rect.bottom = (int)game->GetBackBufferHeight();

	game->Draw(xx - cx, yy - cy, bbox, &rect, alpha);
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
		break;
	case CHANGE_SCENE:
		// plus 10 or 20 to make sure the effect is cover full screen
		left = CGame::GetInstance()->GetCamXPos();
		top = CGame::GetInstance()->GetCamYPos();
		right = left + CGame::GetInstance()->GetBackBufferWidth();
		bottom = top + CGame::GetInstance()->GetBackBufferHeight();
		break;
	case START_FOLLOW_PLAYER:
	{
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

		CMario* mario = (CMario*)scene->GetPlayer();
		if (mario)
		{
			left = x - fabs(x - mario->GetX());
			top = y - fabs(x - mario->GetX());
			right = left + fabs(x - mario->GetX()) * 2;
			bottom = top + fabs(x - mario->GetX()) * 2;
		}
		else
			left = top = right = bottom = 0;
	}
	break;
	case HELP_LEVEL_MAP:
		left = x - HELP_LEVEL_MAP_BBOX_WIDTH / 2;
		top = y - HELP_LEVEL_MAP_BBOX_HEIGHT / 2;
		right = left + HELP_LEVEL_MAP_BBOX_WIDTH;
		bottom = top + HELP_LEVEL_MAP_BBOX_HEIGHT;
		break;
	}
}