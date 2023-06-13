#pragma once
#include "Brick.h"

class CQuestionBrick : public CBrick
{
private:
	BOOLEAN is_unbox = false;

public:

	CQuestionBrick(float x, float y) : CBrick(x, y) {
		is_unbox = FALSE;
	};

	BOOLEAN GetIsUnbox() { return is_unbox; }
	void SetIsUnbox(BOOLEAN is_unbox) { this->is_unbox = is_unbox; }

	int IsCollidable() { return is_unbox == FALSE; };

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt);
	void Render();
};
