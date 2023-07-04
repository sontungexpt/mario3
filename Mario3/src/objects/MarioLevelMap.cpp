#include <algorithm>
#include "debug.h"

#include "components/Collision/Collision.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

#include "Platform.h"
#include "MarioLevelMap.h"

#include "materials/EffectManager.h"

#define DIRECTION_HIT_DOOR_FROM_TOP 1
#define DIRECTION_HIT_DOOR_FROM_BOTTOM 2
#define DIRECTION_HIT_DOOR_FROM_LEFT	3
#define DIRECTION_HIT_DOOR_FROM_RIGHT 4

void CMarioLevelMap::OnNoCollision(DWORD dt)
{
	if (state == MARIO_LEVEL_MAP_STATE_MOVING_SPECIAL_POS)
	{
		if (x == specical_target_x && y == specical_target_y)
		{
			SetState(MARIO_STATE_IDLE);
		}
		else
		{
			if (vx != 0 && fabs(x - start_x) > distance_specical_x)
			{
				x = specical_target_x;
				vx = 0;
			}
			if (vy != 0 && fabs(y - start_y) > distance_specical_y)
			{
				y = specical_target_y;
				vy = 0;
			}
			x += vx * dt;
			y += vy * dt;
		}
	}
	else
	{
		x += vx * dt;
		y += vy * dt;
		if (vx != 0 && fabs(x - start_x) > MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE)
		{
			x = vx > 0 ? start_x + MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE :
				start_x - MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE;
			SetState(MARIO_STATE_IDLE);
		}

		if (vy != 0 && fabs(y - start_y) > MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE)
		{
			y = vy > 0 ? start_y + MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE :
				start_y - MARIO_LEVEL_MAP_MAX_MOVING_DISTANCE;
			SetState(MARIO_STATE_IDLE);
		}
	}
}

void CMarioLevelMap::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CDoor*>(e->obj))
		OnCollisionWithDoor(e);

	if (e->IsCollidedInYDimension() && e->obj->IsBlocking())
	{
		SetState(MARIO_STATE_IDLE);
	}

	if (e->IsCollidedInXDimension() && e->obj->IsBlocking())
	{
		SetState(MARIO_STATE_IDLE);
	}
}

void CMarioLevelMap::OnCollisionWithDoor(LPCOLLISIONEVENT e)
{
	door = dynamic_cast<CDoor*>(e->obj);
	if (e->IsCollidedFromBottom())
		direction_hit_door = DIRECTION_HIT_DOOR_FROM_BOTTOM;
	else if (e->IsCollidedFromTop())
		direction_hit_door = DIRECTION_HIT_DOOR_FROM_TOP;
	else if (e->IsCollidedFromRight())
		direction_hit_door = DIRECTION_HIT_DOOR_FROM_RIGHT;
	else
		direction_hit_door = DIRECTION_HIT_DOOR_FROM_LEFT;
}

void CMarioLevelMap::Render()
{
	int aniId = ID_ANI_MARIO_LEVEL_MAP_SMALL_FORWARD;

	int level = CGameData::GetInstance()->GetMarioLevel();
	if (level == MARIO_LEVEL_SMALL) aniId = ID_ANI_MARIO_LEVEL_MAP_SMALL_FORWARD;
	else if (level == MARIO_LEVEL_BIG) aniId = ID_ANI_MARIO_LEVEL_MAP_BIG_FORWARD;
	else if (level == MARIO_LEVEL_TAIL_SUIT) aniId = ID_ANI_MARIO_LEVEL_MAP_TAIL_FORWARD;

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani = animations->Get(aniId);
	if (ani != nullptr)
		ani->Render(x, y);
}

void CMarioLevelMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (door)
	{
		float mario_left, mario_top, mario_right, mario_bottom;
		GetBoundingBox(mario_left, mario_top, mario_right, mario_bottom);

		float door_left, door_top, door_right, door_bottom;
		door->GetBoundingBox(door_left, door_top, door_right, door_bottom);

		// move out of door
		if (mario_right < door_left || mario_left > door_right ||
			mario_bottom < door_top || mario_top > door_bottom)
		{
			door = nullptr;
		}
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMarioLevelMap::MoveToSpecialPos(float target_x, float target_y)
{
	if (!is_stop_moving) return;
	if (x == target_x && y == target_y) return;

	start_x = x;
	start_y = y;

	specical_target_x = target_x;
	specical_target_y = target_y;

	distance_specical_x = fabs(x - target_x);
	distance_specical_y = fabs(y - target_y);

	vx = CalulateVx(target_x, target_y);
	vy = CalulateVy(target_x, target_y);

	SetState(MARIO_LEVEL_MAP_STATE_MOVING_SPECIAL_POS);
}

void CMarioLevelMap::MoveToSpecialPosFrom(float x, float y, float special_posx, float special_posy)
{
	if (!is_stop_moving) return;

	this->x = x;
	this->y = y;

	if (x == special_posx && y == special_posy) return;

	MoveToSpecialPos(special_posx, special_posy);
}

float CMarioLevelMap::CalulateVx(float target_x, float target_y)
{
	float distance_x = target_x - x;
	float distance_y = target_y - y;
	float alpha = atan(fabs(distance_y) / fabs(distance_x));
	float v_x = MARIO_LEVEL_MAP_SPEED * cos(alpha); // v>0 because 0< alpha < 90 degree
	return distance_x >= 0 ? v_x : -v_x;
}

float CMarioLevelMap::CalulateVy(float target_x, float target_y)
{
	float distance_x = target_x - x;
	float distance_y = target_y - y;
	float alpha = atan(fabs(distance_y) / fabs(distance_x));
	float v_y = MARIO_LEVEL_MAP_SPEED * sin(alpha); // v > 0 because 0 < alpha < 90 degree
	return distance_y > 0 ? v_y : -v_y;
}

void CMarioLevelMap::SetState(int state)
{
	switch (state)
	{
	case MARIO_LEVEL_MAP_STATE_MOVING_RIGHT:
		if (!is_stop_moving) return;
		if (!is_bypass_door_block_rule && door)
		{
			if (!door->IsPassed() && direction_hit_door != DIRECTION_HIT_DOOR_FROM_RIGHT)
				return;
		}
		start_x = x;
		vx = MARIO_LEVEL_MAP_SPEED;
		is_stop_moving = FALSE;
		break;
	case MARIO_LEVEL_MAP_STATE_MOVING_LEFT:
		if (!is_stop_moving) return;
		if (!is_bypass_door_block_rule && door)
		{
			if (!door->IsPassed() && direction_hit_door != DIRECTION_HIT_DOOR_FROM_LEFT)
				return;
		}
		start_x = x;
		is_stop_moving = FALSE;
		vx = -MARIO_LEVEL_MAP_SPEED;
		break;
	case MARIO_LEVEL_MAP_STATE_MOVING_UP:
		if (!is_stop_moving) return;
		if (!is_bypass_door_block_rule && door)
		{
			if (!door->IsPassed() && direction_hit_door != DIRECTION_HIT_DOOR_FROM_TOP)
				return;
		}
		start_y = y;
		vy = -MARIO_LEVEL_MAP_SPEED;
		is_stop_moving = FALSE;
		break;
	case MARIO_LEVEL_MAP_STATE_MOVING_DOWN:
		if (!is_stop_moving) return;
		if (!is_bypass_door_block_rule && door)
		{
			if (!door->IsPassed() && direction_hit_door != DIRECTION_HIT_DOOR_FROM_BOTTOM)
				return;
		}
		start_y = y;
		is_stop_moving = FALSE;
		vy = MARIO_LEVEL_MAP_SPEED;
		break;
	case MARIO_LEVEL_MAP_STATE_MOVING_SPECIAL_POS:
		is_stop_moving = FALSE;
		break;
	case MARIO_STATE_IDLE:
		vx = vy = 0;
		is_stop_moving = TRUE;
		break;
	default:
		break;
	}

	CGameObject::SetState(state);
}

void CMarioLevelMap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MARIO_LEVEL_MAP_BBOX_WIDTH / 2;
	top = y - MARIO_LEVEL_MAP_BBOX_HEIGHT / 2;
	right = left + MARIO_LEVEL_MAP_BBOX_WIDTH;
	bottom = top + MARIO_LEVEL_MAP_BBOX_HEIGHT;
}