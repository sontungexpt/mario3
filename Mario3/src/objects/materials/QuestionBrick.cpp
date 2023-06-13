#include "QuestionBrick.h"
#include "objects/Mario.h"
#include "objects/items/Coin.h"

#include "scenes/PlayScene.h"
#include "configs/QuestionBrick100000.h"

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Update(DWORD dt)
{
}

void CQuestionBrick::Render()
{
	if (!IsInCamera()) return; // lazy load
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_QUESTION_BRICK)->Render(x, y);
}