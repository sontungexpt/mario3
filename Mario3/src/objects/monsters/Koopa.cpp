#include "Game.h"
#include "debug.h"
#include "components/Scene/Scene.h"
#include "scenes/PlayScene.h"

#include "configs/Koopa130000.h"
#include "configs/monsters/Monster.h"

#include "Koopa.h"
#include "Goomba.h"

#include "objects/Mario.h"
#include "objects/Platform.h"

void CKoopa::OnCollisionWithMonster(LPCOLLISIONEVENT e)
{
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	CMonster::OnCollisionWith(e);
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (dead) {
		aniId = ID_ANI_KOOPA_DEFEND;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
void CKoopa::SetState(int state)
{
	// this line handle the same state for many monster
	CMonster::SetState(state);

	// this line handle the different state for each monster
	switch (state)
	{
	}
}
void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if ((state == MONSTER_STATE_DEAD) || (state == KOOPA_STATE_DEAD_UPSIDE)) return;

	if (is_defend) {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
	}
	else {
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}