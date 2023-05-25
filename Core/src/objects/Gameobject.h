#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <Windows.h>
#include <d3dx10.h>
#include "Texture.h"

namespace core {
	class GameObject {
	protected:
		float x_;
		float y_;
		LPTEXTURE texture_;

	public:
		GameObject(float x = 0.0f, float y = 0.0f, LPTEXTURE texture = nullptr) : x_(x), y_(y), texture_(texture) {}

		virtual ~GameObject() {}

		// getter and setter
		float GetX() { return x_; }
		float GetY() { return y_; }

		void SetX(float x) { x_ = x; }
		void SetY(float y) { y_ = y; }
		void SetPosition(float x, float y)
		{
			x_ = x;
			y_ = y;
		}

		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;
	};

	typedef GameObject* LPGAMEOBJECT;
};

#endif
