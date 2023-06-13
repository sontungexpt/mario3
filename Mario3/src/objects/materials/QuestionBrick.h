#pragma once
#include "Brick.h"

class CQuestionBrick : public CBrick
{
private:
	BOOLEAN is_unbox = false;

	float collied_y;
	float ax;

public:

	CQuestionBrick(float x, float y) : CBrick(x, y) {
		is_unbox = FALSE;
		collied_y = y;
		ax = 0;
	};

	BOOLEAN GetIsUnbox() { return is_unbox; }
	void SetIsUnbox(BOOLEAN is_unbox) { this->is_unbox = is_unbox; }

	int IsCollidable() { return is_unbox == FALSE; };

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt);
	void Render();
};
