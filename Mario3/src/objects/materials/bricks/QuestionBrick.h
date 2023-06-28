#pragma once
#include "Brick.h"
#include "configs/materials/QuestionBrick100000.h"
#include "objects/items/Item.h"
#include "objects/items/Mushroom.h"

class CQuestionBrick : public CBrick
{
private:
	BOOLEAN is_unboxed;
	int item_type;

	CItem* CreateItem(CItem* item);
	void CreateItem();

public:

	CQuestionBrick(float x, float y, int item_type = QUESTION_BRICK_COIN) : CBrick(x, y) {
		is_unboxed = FALSE;
		this->item_type = item_type;
	};

	float GetItemReferenceY(CItem* item)
	{
		// plus 1 to make sure that it will always colide
		float max_jump_height = QUESTION_BRICK_SPEED * QUESTION_BRICK_SPEED / 2 * QUESTION_BRICK_GRAVITY + 1;
		if (dynamic_cast<CMushroom*>(item))
			max_jump_height += 5.0;
		return y - (QUESTION_BRICK_BBOX_HEIGHT + item->GetHeight()) / 2 - ceil(max_jump_height);
	};

	float GetItemReferenceX(CItem* item) { return x; };

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
