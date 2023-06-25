#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "components/Texture/Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "components/Sprite/Sprites.h"
#include "configs/GameObject.h"
#include "scenes/PlayScene.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	ax = ay = 0;
	start_x, start_y = 0;
	max_vx = max_vy = -1; // no limit
	state = -1;
	is_deleted = false;
	is_collidable = 0;
	is_blocking = 1;
}

void CGameObject::ResetPositionIfOutOfWidthScreen(float& curr_x, float& curr_y) {
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);

	// no permit move out of screen
	if (curr_x - (right - left) / 2 <= cam_x)
	{
		curr_x = cam_x + (right - left) / 2;
	}
	else if (right > cam_x + SCREEN_WIDTH)
	{
		curr_x = cam_x + SCREEN_WIDTH;
	}
}

int CGameObject::RemoveWhenMoveToDangerousSpace()
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);

	//move out of screen >> delete
	//fall to to the hole >> delete
	if (right <= 0 ||
		left >= ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMaxObjectX()->GetRight() ||
		bottom <= 0 ||
		top >= ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMaxObjectY()->GetBottom())
	{
		is_deleted = TRUE;
		return 1;
	}

	return 0;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, CALCULATE_COLOR(0.7, 0, 0.5));
}

float CGameObject::GetWidth()
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	return right - left;
}

float CGameObject::GetHeight()
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	return bottom - top;
}

BOOLEAN CGameObject::IsInCamera() {
	float cam_x, cam_y;
	float left, top, right, bottom;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	GetBoundingBox(left, top, right, bottom);

	//// out of width screen
	if (right < cam_x || left > cam_x + CGame::GetInstance()->GetBackBufferWidth())
		return FALSE;

	//// out of height screen
	if (bottom < cam_y || top > cam_y + CGame::GetInstance()->GetBackBufferHeight())
		return FALSE;

	// in camera
	return TRUE;
}