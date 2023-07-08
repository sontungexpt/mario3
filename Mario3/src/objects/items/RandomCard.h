#pragma once

#include "Item.h"
#include "components/Animation/Animation.h"
#include "components/Animation/Animations.h"

// configs
#include "configs/items/Coin300000.h"

class CRandomCard : public CItem {
	vector<string> items =
	{
		"Mushroom",
		"Star",
		"Flower"
	};

	size_t random_item_index;
	ULONGLONG time_start;

	void OnCollisionWithPlayer(LPCOLLISIONEVENT e);

public:

	CRandomCard(float x, float y) : CItem(x, y) {
		ay = 0;
		random_item_index = 0;
		time_start = 0;
	}
	CRandomCard(float x, float y, int state) :CItem(x, y, state) {
		ay = 0;
		time_start = 0;
		random_item_index = 0;
	}

	//void OnCollisionWith(LPCOLLISIONEVENT e);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void IncreaseCyclicRandomItemIndex()
	{
		random_item_index++;
		if (random_item_index >= items.size())
			random_item_index = 0;
	}

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void SetState(int state);

	void BeCollected();
};