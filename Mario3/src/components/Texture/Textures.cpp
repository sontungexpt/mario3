#include <Windows.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

CTextures* CTextures::__instance = nullptr;

CTextures* CTextures::GetInstance()
{
	if (__instance == nullptr) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE CTextures::Get(unsigned int i)
{
	LPTEXTURE t = textures[i];
	if (t == nullptr)
		DebugOut(L"[ERROR] Texture Id %d not found !\n", i);

	return t;
}

void CTextures::Clear()
{
	for (auto x : textures)
	{
		LPTEXTURE tex = x.second;
		if (tex != nullptr) delete tex;
	}

	textures.clear();
}