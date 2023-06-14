#pragma once
#include "Brick.h"
#include "configs/materials/QuestionBrick100000.h"
#include "objects/items/Item.h"
class CQuestionBrick : public CBrick
{
private:
	BOOLEAN is_unboxed = FALSE;
	int item_type;

	// the value of y at the first time the brick is colliding with mario
	// NOTE: it is the top-left corner of the brick
	float orginal_y;

	float ax;
	float ay;

	CItem* CreateItem(CItem* item);

public:

	CQuestionBrick(float x, float y, int item_type = QUESTION_BRICK_COIN) : CBrick(x, y) {
		is_unboxed = FALSE;
		this->item_type = item_type;

		orginal_y = y;
		ax = 0;
		ay = 0;
	};

	float GetItemReferenceY(CItem* item) { return y - item->GetHeight() - 1; };
	float GetItemReferenceX(CItem* item) { return x - item->GetWidth() / 2 + 1; };

	// core
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void Render();
	void SetState(int state);

	BOOLEAN GetIsUnbox() { return is_unboxed; }
	void SetIsUnbox(BOOLEAN is_unboxed) { this->is_unboxed = is_unboxed; }

	// collision
	void OnNoCollision(DWORD dt);

	int IsCollidable() { return !is_unboxed; };

	// is wall
	int IsBlocking() { return 1; };

	// this part is the other name to call SetState
	void Bounce() { SetState(QUESTION_BRICK_STATE_UNBOXING); };
	void Disable() { SetState(QUESTION_BRICK_STATE_DISABLED); };
};
