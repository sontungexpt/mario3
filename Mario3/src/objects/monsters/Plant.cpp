//#include "Plant.h"
//#include "GameObject.h"
//#include "Mario.h"
//#include "scenes/PlayScene.h"
//#include "Goomba.h"
//
//CPlant::CPlant(float x, float y, int model) : CGameObject(x, y)
//{
//	this->model = model;
//	startY = y;
//	minY = startY - PLANT_BBOX_HEIGHT;
//	SetState(PLANT_STATE_UP);
//}
//
//void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
//	if (state == PLANT_STATE_DEATH) return;
//	if (model == PLANT_SHOOT_RED) {
//		left = x - PLANT_BBOX_WIDTH / 2;
//		top = y - PLANT_BBOX_HEIGHT / 2 + 4;
//		right = left + PLANT_BBOX_WIDTH;
//		bottom = top + PLANT_BBOX_HEIGHT;
//	}
//	else {
//		left = x - PLANT_BBOX_WIDTH / 2;
//		top = y - PLANT_BBOX_HEIGHT_SMALL / 2 + 4;
//		right = left + PLANT_BBOX_WIDTH;
//		bottom = top + PLANT_BBOX_HEIGHT_SMALL;
//	}
//}
//void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//	if (mario->GetIsChanging() || mario->GetState() == MARIO_STATE_DIE) return;
//	if (isUpping) {
//		if (y > minY) {
//			vy = -PLANT_SPEED_UP_DOWN;
//		}
//		else {
//			time_shoot = GetTickCount64();
//			vy = 0;
//			y = minY;
//			if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE) {
//				SetState(PLANT_STATE_DOWN);
//			}
//			else {
//				if ((model == PLANT_SHOOT_GREEN) || (model == PLANT_SHOOT_RED)) {
//					if (!isShoot) {
//						if (GetTickCount64() - time_shoot < TIME_SHOOT_INTERVAl) {
//							isShoot = true;
//							bool isOnTop = false, isLeft = false;
//							if (PositionXWithMario() == 1) {
//								isOnTop = true;
//							}
//							if (PositionYWithMario() == 1) {
//								isLeft = true;
//							}
//							/*if (isOnTop && isLeft)
//							{
//								CFireFromPlant* fire = new CFireFromPlant(x, y, isLeft, !isOnTop);
//								scene->AddObject(fire);
//							}
//							else if (isOnTop && !isLeft) {
//								CFireFromPlant* fire = new CFireFromPlant(x, y, isLeft, !isOnTop);
//								scene->AddObject(fire);
//							}
//							else if (!isOnTop && !isLeft) {
//								CFireFromPlant* fire = new CFireFromPlant(x, y, isLeft, !isOnTop);
//								scene->AddObject(fire);
//							}
//							else if (!isOnTop && isLeft) {
//								CFireFromPlant* fire = new CFireFromPlant(x, y, isLeft, !isOnTop);
//								scene->AddObject(fire);
//							}*/
//						}
//					}
//				}
//			}
//		}
//	}
//	else if (isDowning) {
//		if (model == PLANT_SHOOT_GREEN || model == PLANT_SHOOT_RED) {
//			if ((y < startY + 2)) {
//				vy = PLANT_SPEED_UP_DOWN;
//			}
//			else {
//				vy = 0;
//				y = startY + 2;
//				if (GetTickCount64() - time_down_pipe > TIME_DOWN_PIPE) {
//					SetState(PLANT_STATE_UP);
//				}
//			}
//		}
//		else {
//			if (y < startY + 2 - DISTANCE_PIPE_LONG_SHORT) {
//				vy = PLANT_SPEED_UP_DOWN;
//			}
//			else {
//				vy = 0;
//				y = startY + 2 - DISTANCE_PIPE_LONG_SHORT;
//				if (GetTickCount64() - time_down_pipe > TIME_DOWN_PIPE) {
//					SetState(PLANT_STATE_UP);
//				}
//			}
//		}
//	}
//	CGameObject::Update(dt, coObjects);
//	CCollision::GetInstance()->Process(this, dt, coObjects);
//}
////int CPlant::PositionXWithMario() {
////	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
////	if (mario->GetX() < GetX()) //mario left, plant right
////	{
////		return 1;
////	}
////	else return -1;
////}
//
//void CPlant::OnNoCollision(DWORD dt) {
//	x += vx * dt;
//	y += vy * dt;
//}
//
////int CPlant::PositionYWithMario() {
////	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
////	if (mario->GetY() < GetY()) //mario top, plant under
////	{
////		return 1;
////	}
////	else return -1;
////}
//
//void CPlant::Render() {
//	CAnimations* animations = CAnimations::GetInstance();
//	int aniId = -1;
//	if (model == PLANT_SHOOT_RED) {
//		if (PositionXWithMario() == 1 && PositionYWithMario() == -1)
//			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT;
//			else aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT;
//		else if (PositionXWithMario() == 1 && PositionYWithMario() == 1)
//			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT;
//			else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT;
//		else if (PositionXWithMario() == -1 && PositionYWithMario() == 1)
//			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT;
//			else aniId = ID_ANI_PLANT_RIGHT_TOP_SHOOT;
//		else {
//			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT;
//			else aniId = ID_ANI_PLANT_RIGHT_UNDER_SHOOT;
//		}
//	}
//	else if (model == PLANT_SHOOT_GREEN) {
//		if (PositionXWithMario() == 1 && PositionYWithMario() == -1)
//			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT_GREEN;
//			else aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT_GREEN;
//		else if (PositionXWithMario() == 1 && PositionYWithMario() == 1)
//			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT_GREEN;
//			else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT_GREEN;
//		else if (PositionXWithMario() == -1 && PositionYWithMario() == 1)
//			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT_GREEN;
//			else aniId = ID_ANI_PLANT_RIGHT_TOP_SHOOT_GREEN;
//		else {
//			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT_GREEN;
//			else aniId = ID_ANI_PLANT_RIGHT_UNDER_SHOOT_GREEN;
//		}
//	}
//	else if (model == PLANT_NOT_SHOOT) {
//		aniId = ID_ANI_PLANT_NOT_SHOOT;
//	}
//
//	animations->Get(aniId)->Render(x, y);
//}
//
//void CPlant::SetState(int state) {
//	switch (state) {
//	case PLANT_STATE_UP:
//		isUpping = true;
//		isDowning = false;
//		isShoot = false;
//		time_out_pipe = GetTickCount64();
//		time_down_pipe = 0;
//		break;
//	case PLANT_STATE_DOWN:
//		isShoot = false;
//		isUpping = false;
//		isDowning = true;
//		time_down_pipe = GetTickCount64();
//		time_out_pipe = 0;
//		break;
//	case PLANT_STATE_DEATH:
//		isDeleted = true;
//		break;
//	}
//	CGameObject::SetState(state);
//}