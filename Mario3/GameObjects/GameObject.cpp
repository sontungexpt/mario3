#include <d3dx9.h>

#include "GameObject.h"
#include "../utils/Game.h"

GameObject::GameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void GameObject::Render()
{
	Game::GetInstance()->Draw(x, y, texture);
}

GameObject::~GameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {
		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}