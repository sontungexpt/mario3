#include "CreatableBrick.h"
#include "scenes/PlayScene.h"

CItem* CCreatableBrick::CreateItem(CItem* item)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	item->SetPosition(GetItemReferenceX(item), GetItemReferenceY(item));
	is_created_item = TRUE;
	return (CItem*)scene->AddObject(item);
}

CItem* CCreatableBrick::CreateItemBehind(CItem* item)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	item->SetPosition(GetItemReferenceX(item), GetItemReferenceY(item));
	is_created_item = TRUE;
	return (CItem*)scene->AddObjectToFirst(item);
}