#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "components/Texture/Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "components/Sprite/Sprites.h"
#include "configs/GameObject.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	state = -1;
	isDeleted = false;
}

void CGameObject::ResetPositionIfOutOfScreen(float& curr_x, float& curr_y) {
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

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, &rect, CALCULATE_COLOR(0.7, 0, 0.2));
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

	if (right < cam_x || left > cam_x + SCREEN_WIDTH)
		return false;
	return true;
}