#include "RandomCard.h"
#include "GameData.h"
#include <objects/Mario.h>

void CRandomCard::OnCollisionWithPlayer(LPCOLLISIONEVENT e)
{
	BeCollected();
}

void CRandomCard::Render()
{
	// frame
	CAnimations::GetInstance()->Get(ID_ANI_WHITE_FRAME_ICON)->Render(x, y);

	if (!is_collected)
	{
		if (items[random_item_index] == "Mushroom")
			CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM_CARD_ICON)->Render(x, y);
		else if (items[random_item_index] == "Star")
			CAnimations::GetInstance()->Get(ID_ANI_STAR_CARD_ICON)->Render(x, y);
		else if (items[random_item_index] == "Flower")
			CAnimations::GetInstance()->Get(ID_ANI_FLOWER_CARD_ICON)->Render(x, y);
	}
}

void CRandomCard::Update(DWORD dt, vector<LPGAMEOBJECT>* co_objects)
{
	if (!is_collected && GetTickCount64() - time_start > RANDOM_CARD_CHANGE_DURATION)
	{
		IncreaseCyclicRandomItemIndex();
		time_start = GetTickCount64();
	}
}

void CRandomCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_WHITE_FRAME_BBOX_WIDTH / 2;
	t = y - HUD_WHITE_FRAME_BBOX_HEIGHT / 2;
	r = l + HUD_WHITE_FRAME_BBOX_WIDTH;
	b = t + HUD_WHITE_FRAME_BBOX_HEIGHT;
}

void CRandomCard::SetState(int state)
{
}

void CRandomCard::BeCollected()
{
	if (is_collected) return;
	CItem::BeCollected();

	CGameData* data = CGameData::GetInstance();
	data->AddAvailableItem(items[random_item_index]);
	vector<string> available_items = CGameData::GetInstance()->GetAvailableItems();
	size_t size = available_items.size();
	if (size >= 3)
	{
		bool all_equal = true;
		string first_item = available_items[0];

		for (int i = 1; i < size; i++) {
			if (available_items[i] != first_item) {
				all_equal = false;
				break;
			}
		}
		if (all_equal)
		{
			if (first_item == "Mushroom")
				data->SetLife(data->GetLife() + 2);
			else if (first_item == "Flower")
				data->SetLife(data->GetLife() + 3);
			else if (first_item == "Star")
				data->SetLife(data->GetLife() + 5);
		}
		else
		{
			data->IncreaseLifeBy1();
		}
		data->ClearAvailableItems();
	}
}