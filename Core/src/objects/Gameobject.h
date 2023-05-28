#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <Windows.h>
#include <d3dx10.h>
#include "components/Texture/Texture.h"

namespace core {
	class GameObject {
	protected:
		float x_;
		float y_;

		float vx_;
		float vy_;

		int navx_;

		int state_;

	public:
		GameObject(float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f)
			: x_(x), y_(y), vx_(vx), vy_(vy)
		{
			navx_ = 1;
			state_ = -1;
		}

		virtual ~GameObject() {}

		// getter and setter
		float GetX() { return x_; }
		void SetX(float x) { x_ = x; }

		float GetY() { return y_; }
		void SetY(float y) { y_ = y; }

		void SetState(int state) { state_ = state; }
		int GetState(int state) { return state_; }

		void SetPosition(float x, float y)
		{
			x_ = x;
			y_ = y;
		}

		void SetSpeed(float vx, float vy)
		{
			vx_ = vx;
			vy_ = vy;
		}

		virtual void Update(DWORD dt) = 0;
		virtual void Render() = 0;
	};

	typedef GameObject* LPGAMEOBJECT;
};

#endif
