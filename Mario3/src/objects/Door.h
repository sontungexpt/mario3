#pragma once
#include "GameObject.h"
#include "Game.h"
#include "GameData.h"

#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"
#include "scenes/PlayScene.h"
#include "objects/Portal.h"
#include "configs/Door.h"

class CDoor : public CPortal
{
private:
	BOOLEAN allow_left;
	BOOLEAN allow_top;
	BOOLEAN allow_right;
	BOOLEAN allow_bottom;
public:
	CDoor(float x, float y, int scene_id, BOOLEAN allow_left, BOOLEAN allow_right, BOOLEAN allow_top, BOOLEAN allow_bottom) : CPortal(x, y, x + DOOR_BBOX_WIDTH, y + DOOR_BBOX_HEIGHT, scene_id)
	{
		state = DOOR_LEVEl_0;
		this->allow_left = allow_left;
		this->allow_top = allow_top;
		this->allow_right = allow_right;
		this->allow_bottom = allow_bottom;
	}

	void Render();

	bool IsAllowLeft() { return allow_left; }
	bool IsAllowTop() { return allow_top; }
	bool IsAllowRight() { return allow_right; }
	bool IsAllowBottom() { return allow_bottom; }
};
