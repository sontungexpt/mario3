#pragma once

#include "Item.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

class CRandomCard : public CItem {
public:
	enum RandomItem {
		MUSHROOM,
		STAR,
		FLOWER,
		COUNT,
	};

private:
	size_t random_item_index;
	ULONGLONG time_start;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);
	void RenderItem(float xx, float yy);
	void IncreaseCyclicRandomItemIndex();

	vector<RandomItem> items;

public:
	CRandomCard(float x = 0, float y = 0, int state = UNKNOWN_STATE)
		:CItem(x, y, 0, state),
		random_item_index(0),
		time_start(0)
	{
		items.push_back(MUSHROOM);
		items.push_back(STAR);
		items.push_back(FLOWER);
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }

	void BeCollected();
};