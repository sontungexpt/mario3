#pragma once

#include <Windows.h>
#include <d3dx10.h>

#include "../utils/Texture.h"

class GameObject
{
protected:
	float x;
	float y;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object.
	// For now, just a pointer to a single texture
	LPTEXTURE texture;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return x; }
	float GetY() { return y; }

	GameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = NULL);

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	~GameObject();
};
typedef GameObject* LPGAMEOBJECT;

class CBrick : public GameObject
{
public:
	CBrick(float x, float y, LPTEXTURE texture) : GameObject(x, y, texture) {}
	void Update(DWORD dt) {};
};

class CMario : public GameObject
{
	float vx;
	float vy;
public:
	CMario(float x, float y, float vx, float vy, LPTEXTURE texture) :GameObject(x, y, texture)
	{
		this->vx = vx;
		this->vy = vy;
	};
	void Update(DWORD dt);
};