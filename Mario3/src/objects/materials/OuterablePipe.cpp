#include "OuterablePipe.h"

void COuterablePipe::PlayerMovedOut()
{
	CGameData::GetInstance()->SetCurrentSceneId(INT_MAX);
}