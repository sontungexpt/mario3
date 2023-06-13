//#include "Koopa.h"
//#include "Goomba.h"
//#include "objects/Mario.h"
//#include "objects/Platform.h"
//#include "components/Scene/Scene.h"
//#include "Game.h"
//#include "debug.h"
//#include "scenes/PlayScene.h"
//
//void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
//	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
//	CMario* mario = (CMario*)scene->GetPlayer();
//
//	if (!IsInCamera())return; // lazy load
//
//	//if (mario->GetIsChanging() || mario->GetState() == MARIO_STATE_DIE) return;
//	//vy += ay * dt;
//	//vx += ax * dt;
//
//	//if (mario->GetIsHolding() && isHeld) {
//	//	this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
//	//	this->y = mario->GetY() - 3;
//
//	//	vx = mario->GetVx();
//	//	vy = mario->GetVy();
//	//}
//	//else {
//	//	if (this->isHeld) {
//	//		ay = KOOPA_GRAVITY;
//	//		SetState(KOOPA_STATE_IS_KICKED);
//	//	}
//	//}
//
//	//if (isDead && isUpside) {
//	//	if (GetTickCount64() - die_start > KOOPA_DIE_TIME)
//	//	{
//	//		isDeleted = true;
//	//		return;
//	//	}
//	//}
//	//if (!isDead) {
//	//	if (!isKicked) {
//	//		if (GetTickCount64() - defend_start > KOOPA_COMBACK_START && (isDefend || isUpside) && !isKicked) {
//	//			isComeback = true;
//	//		}
//	//		if ((GetTickCount64() - defend_start > KOOPA_DEFEND_TIMEOUT && (isDefend || isUpside) && !isKicked)) {
//	//			if (isComeback) {
//	//				SetState(KOOPA_STATE_WALKING);
//	//				vy = -KOOPA_ADJUST_NOT_FALL;
//	//				defend_start = -1;
//	//			}
//	//		}
//	//	}
//	//	else { isComeback = false; }
//	//}
//	//if (state == KOOPA_STATE_UPSIDE && !isOnPlatform) {
//	//	vx = -KOOPA_WALKING_SPEED;
//	//}
//
//	//CGameObject::Update(dt, coObjects);
//	//CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
//	//if ((state == KOOPA_STATE_ISDEAD) || (state == KOOPA_STATE_DEAD_UPSIDE)) return;
//	/*if (isDefend || isUpside) {
//		left = x - KOOPA_BBOX_WIDTH / 2;
//		top = y - KOOPA_BBOX_HEIGHT_DEFEND / 2;
//		right = left + KOOPA_BBOX_WIDTH;
//		bottom = top + KOOPA_BBOX_HEIGHT_DEFEND;
//	}
//	else {
//		left = x - KOOPA_BBOX_WIDTH / 2;
//		top = y - KOOPA_BBOX_HEIGHT / 2;
//		right = left + KOOPA_BBOX_WIDTH;
//		bottom = top + KOOPA_BBOX_HEIGHT;
//	}*/
//}
//int CKoopa::PositionWithMario() {
//	/*CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//	if (mario->GetX() < GetX()) return 1;
//	else return -1;*/
//}
//
//int CKoopa::GetAniGreen() {
//	//int aniId = -1;
//	//if (!isWing) {
//	//	if (isUpside) {
//	//		if (isComeback) aniId = ID_ANI_GREEN_UPSIDE_COMEBACK;
//	//		else if (isKicked) aniId = ID_ANI_GREEN_UPSIDE_KICKED;
//	//		else aniId = ID_ANI_GREEN_UPSIDE;
//	//	}
//	//	else {
//	//		if (isDefend) {
//	//			if (isComeback) aniId = ID_ANI_GREEN_COMEBACK;
//	//			else if (isKicked) aniId = ID_ANI_GREEN_DEFEND;//ID_ANI_GREEN_KICKED;
//	//			else aniId = ID_ANI_GREEN_DEFEND;
//	//		}
//	//		else
//	//		{
//	//			if (vx > 0) aniId = ID_ANI_GREEN_WALK_RIGHT;
//	//			else aniId = ID_ANI_GREEN_WALK_LEFT;
//	//		}
//	//	}
//	//}
//	//else {
//	//	if (vx > 0) aniId = ID_ANI_GREEN_WING_RIGHT;
//	//	else aniId = ID_ANI_GREEN_WING_LEFT;
//	//}
//	//return aniId;
//}
//
//int CKoopa::GetAniRed() {
//	//int aniId;
//	//if (isUpside) {
//	//	if (isComeback) aniId = ID_ANI_RED_UPSIDE_COMEBACK;
//	//	else if (isKicked) aniId = ID_ANI_RED_UPSIDE_KICKED;
//	//	else aniId = ID_ANI_RED_UPSIDE;
//	//}
//	//else {
//	//	if (isDefend) {
//	//		if (isComeback) aniId = ID_ANI_RED_COMEBACK;
//	//		else if (isKicked) aniId = ID_ANI_RED_DEFEND;//ID_ANI_RED_KICKED;
//	//		else aniId = ID_ANI_RED_DEFEND;
//	//	}
//	//	else
//	//	{
//	//		if (vx > 0) aniId = ID_ANI_RED_WALK_RIGHT;
//	//		else aniId = ID_ANI_RED_WALK_LEFT;
//	//	}
//	//}
//	//return aniId;
//}
//
//void CKoopa::Render() {
//	/*if (!checkObjectInCamera(this)) return;
//	int aniId;
//	if (model == KOOPA_RED) {
//		aniId = GetAniRed();
//	}
//	else aniId = GetAniGreen();
//	CAnimations::GetInstance()->Get(aniId)->Render(x, y);*/
//}
//
//void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
//	if (!e->obj->IsBlocking() && !e->obj->IsPlatform() && !e->obj->IsPlayer() && !e->obj->IsEnemy()) return;
//	if (!dynamic_cast<CGoomba*>(e->obj) && !dynamic_cast<CMario*>(e->obj)) {
//		if (e->ny < 0)
//		{
//			if (model != KOOPA_GREEN_WING) {
//				vy = 0;
//				isOnPlatform = true;
//			}
//			else {
//				if (state == KOOPA_STATE_JUMP) {
//					vy = -KOOPA_JUMP_SPEED;
//				}
//				else vy = 0;
//			}
//		}
//		if (e->nx != 0 && e->obj->IsBlocking())
//		{
//			vx = -vx;
//		}
//	}
//
//	if (dynamic_cast<CGoomba*>(e->obj))
//		this->OnCollisionWithGoomba(e);
//	else if (dynamic_cast<CBrickQuestion*>(e->obj))
//		this->OnCollisionWithBrickQuestion(e);
//	else if (dynamic_cast<CPlatform*>(e->obj))
//		this->OnCollisionWithPlatform(e);
//	else if ((dynamic_cast<CKoopa*>(e->obj)))
//		this->OnCollisionWithKoopa(e);
//	else if ((dynamic_cast<CPlantEnemy*>(e->obj)))
//		this->OnCollisionWithPlantEnemy(e);
//	else if ((dynamic_cast<CBrickColor*>(e->obj)))
//		this->OnCollisionWithBrickColor(e);
//}
//
//void CKoopa::OnCollisionWithBrickColor(LPCOLLISIONEVENT e) {
//	CBrickColor* brick = dynamic_cast<CBrickColor*>(e->obj);
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//
//	if ((isKicked) && (e->nx != 0)) {
//		mario->SetScore(mario->GetScore() + 100);
//		brick->SetState(BRICK_STATE_DELETE);
//	}
//}
//void CKoopa::OnCollisionWithPlantEnemy(LPCOLLISIONEVENT e) {
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//
//	CPlantEnemy* plant = dynamic_cast<CPlantEnemy*>(e->obj);
//	if (isKicked) {
//		mario->IncreaseScoreUpCollision(x, y);
//		plant->SetState(PLANT_STATE_DEATH);
//	}
//}
//
//void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e) {
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//
//	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
//	if (isHeld) {
//		SetState(KOOPA_STATE_DEAD_UPSIDE);
//		koopa->SetState(KOOPA_STATE_DEAD_UPSIDE);
//	}
//	else if (isKicked) {
//		mario->IncreaseScoreUpCollision(x, y);
//
//		koopa->SetState(KOOPA_STATE_DEAD_UPSIDE);
//	}
//}
//
//void CKoopa::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e) {
//	/*CBrickQuestion* questionBrick = dynamic_cast<CBrickQuestion*>(e->obj);
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
//
//	if (e->nx != 0) {
//		if (isKicked) {
//			if (!questionBrick->GetIsEmpty() || !questionBrick->GetIsUnbox()) {
//				if (questionBrick->GetModel() == QUESTION_BRICK_ITEM) {
//					if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
//						CMushRoom* mushroom = new CMushRoom(questionBrick->GetX(), questionBrick->GetY());
//						scene->AddObject(mushroom);
//					}
//					else if (mario->GetLevel() >= MARIO_LEVEL_BIG) {
//						CLeaf* leaf = new CLeaf(questionBrick->GetX(), questionBrick->GetY());
//						scene->AddObject(leaf);
//					}
//				}
//				else if (questionBrick->GetModel() == QUESTION_BRICK_COIN) {
//					mario->SetCoin(mario->GetCoin() + 1);
//					CCoin* coin = new CCoin(questionBrick->GetX(), questionBrick->GetY());
//					coin->SetState(COIN_SUMMON_STATE);
//					scene->AddObject(coin);
//				}
//				else {
//					CButton* button = new CButton(questionBrick->GetX(), questionBrick->GetY());
//					scene->AddObject(button);
//				}
//				questionBrick->SetIsEmpty(true);
//				questionBrick->SetIsUnbox(true);
//			}
//		}
//	}*/
//}
//void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
//	/*CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
//
//	if (isKicked) {
//		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//		mario->IncreaseScoreUpCollision(x, y);
//		goomba->SetState(GOOMBA_STATE_DIE_UPSIDE);
//	}*/
//}
//void CKoopa::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {
//	/*CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
//	if (e->ny < 0) {
//		if (!platform->isCanNotBlockKoopa()) {
//			isOnPlatform = true;
//			if (!isDefend && !isUpside) {
//				SetY(platform->GetY() - KOOPA_BBOX_HEIGHT + 4);
//			}
//			else
//			{
//				SetY(platform->GetY() - KOOPA_BBOX_HEIGHT / 2 - 3);
//			}
//			if ((model == KOOPA_GREEN_WING) && (state == KOOPA_STATE_JUMP)) {
//				vy = -KOOPA_JUMP_SPEED;
//			}
//		}
//	}
//	if ((model == KOOPA_RED) && (state == KOOPA_STATE_WALKING))
//	{
//		if (platform->GetX() - KOOPA_BBOX_WIDTH / 2 > GetX()) {
//			SetX(platform->GetX() - KOOPA_BBOX_WIDTH / 2);
//			vx = -vx;
//		}
//		if ((GetX() > (platform->GetX() + (platform->GetLength() - 0.5) * KOOPA_BBOX_WIDTH))) {
//			SetX(platform->GetX() + (float(platform->GetLength() - 0.5)) * KOOPA_BBOX_WIDTH);
//			vx = -vx;
//		}
//	}*/
//}
//void CKoopa::SetState(int state) {
//	/*if (this->state == KOOPA_STATE_ISDEAD) return;
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//	switch (state) {
//	case KOOPA_STATE_WALKING:
//		vx = -KOOPA_WALKING_SPEED;
//		vy = 0;
//		ay = KOOPA_GRAVITY;
//		isComeback = false;
//		isDefend = false;
//		isUpside = false;
//		isKicked = false;
//		isWing = false;
//		isHeld = false;
//		break;
//	case KOOPA_STATE_DEFEND:
//		isDefend = true;
//		isComeback = false;
//		isKicked = false;
//		isUpside = false;
//		if (isOnPlatform) vx = 0;
//		defend_start = GetTickCount64();
//		break;
//	case KOOPA_STATE_UPSIDE:
//		isUpside = true;
//		isDefend = false;
//		isComeback = false;
//		if (isWing) {
//			isWing = false;
//			ay = KOOPA_GRAVITY;
//		}
//		isKicked = false;
//		vy = -KOOPA_JUMP_IS_ATTACKED;
//		if (isOnPlatform) vx = 0;
//		defend_start = GetTickCount64();
//		break;
//	case KOOPA_STATE_IS_KICKED:
//		if (isHeld) {
//			vy = -KOOPA_KICKED_NOT_FALL;
//		}
//		isOnPlatform = true;
//		isKicked = true;
//		isHeld = false;
//		vx = PositionWithMario() * KOOPA_IS_KICKED_SPEED;
//		break;
//	case KOOPA_STATE_JUMP:
//		isUpside = false;
//		isDefend = false;
//		isComeback = false;
//		isKicked = false;
//		vx = -KOOPA_WALKING_SPEED;
//		if (isWing) {
//			ay = KOOPA_GRAVITY_WING;
//		}
//		break;
//	case KOOPA_STATE_DEAD_UPSIDE:
//		vy = -KOOPA_JUMP_DEATH;
//		ay = KOOPA_GRAVITY;
//		vx = 0;
//		isWing = false;
//		isComeback = false;
//		isDefend = false;
//		isHeld = false;
//		isKicked = false;
//		isUpside = true;
//		isDead = true;
//		die_start = GetTickCount64();
//		break;
//	}
//	CGameObject::SetState(state);*/
//}