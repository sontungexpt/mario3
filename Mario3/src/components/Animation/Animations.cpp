#include "Animations.h"
#include "debug.h"

CAnimations* CAnimations::__instance = nullptr;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == nullptr) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	if (animations[id] != nullptr)
		DebugOut(L"[WARNING] Animation %d already exists\n", id);

	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == nullptr)
		DebugOut(L"[ERROR] Animation ID %d not found\n", id);
	return ani;
}

void CAnimations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}