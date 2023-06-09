#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "components/Texture/Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "components/Sprite/Sprites.h"
#include "configs/GameObject.h"
#include "scenes/PlayScene.h"

void CGameObject::ResetPositionIfOutOfWidthScreen(float& curr_x, float& curr_y) {
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float max_width = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetMaxObjectX()->GetRight();

	// no permit move out of screen
	if (left < 0)
	{
		curr_x = (right - left) / 2;
		vx = 0;
	}
	else if (right > max_width)
	{
		curr_x = max_width - (right - left) / 2;
		vx = 0;
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

BOOLEAN CGameObject::IsOutBottomCamera() {
	float cam_x, cam_y;
	float left, top, right, bottom;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	GetBoundingBox(left, top, right, bottom);

	if (top > cam_y + CGame::GetInstance()->GetBackBufferHeight())
		return TRUE;
	return FALSE;
}

BOOLEAN CGameObject::IsOutLeftCamera() {
	float cam_x, cam_y;
	float left, top, right, bottom;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	GetBoundingBox(left, top, right, bottom);

	if (right < cam_x)
		return TRUE;
	return FALSE;
}

BOOLEAN CGameObject::IsOutRightCamera() {
	float cam_x, cam_y;
	float left, top, right, bottom;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	GetBoundingBox(left, top, right, bottom);

	if (left > cam_x + CGame::GetInstance()->GetBackBufferWidth())
		return TRUE;
	return FALSE;
}

BOOLEAN CGameObject::IsOutTopCamera() {
	float cam_x, cam_y;
	float left, top, right, bottom;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	GetBoundingBox(left, top, right, bottom);

	if (bottom < cam_y)
		return TRUE;
	return FALSE;
}

void CGameObject::ProcessCollision(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	CCollision::GetInstance()->Process(this, dt, co_objects);
}