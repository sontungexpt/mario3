#pragma once
#include "Brick.h"
#include "objects/items/Item.h"

class CCreatableBrick : public CBrick
{
protected:

	int item_type;
	BOOLEAN is_created_item;

	virtual CItem* CreateItem(CItem* item);
	virtual CItem* CreateItemBehind(CItem* item);

	virtual float GetItemReferenceY(CItem* item) = 0;
	virtual float GetItemReferenceX(CItem* item) = 0;
public:

	CCreatableBrick(float x, float y, int item_type)
		: CBrick(x, y),
		item_type(item_type),
		is_created_item(FALSE)
	{};
};