#pragma once
#include "Brick.h"

class CQuestionBrick : public CBrick
{
private:
	BOOLEAN is_unbox = false;
	BOOLEAN is_empty = false;

public:

	CQuestionBrick(float x, float y) : CBrick(x, y) {};

	BOOLEAN GetIsUnbox() { return is_unbox; }
	BOOLEAN GetIsEmpty() { return is_empty; }
	void SetIsUnbox(BOOLEAN is_unbox) { this->is_unbox == is_unbox; }
	void SetIsEmpty(BOOLEAN is_empty) { this->is_empty = is_empty; }

	//int IsCollidable() { return is_unbox == FALSE && is_empty == FALSE; };

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt);
	void Render();
};
