#pragma once
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <Windows.h>
#include <unordered_map>

#include "AnimationFrame.h"
#include "components/Sprite/Sprites.h"

namespace core {
	using namespace std;

	class Animation
	{
		ULONGLONG last_frame_time_;
		int default_time_;
		int current_frame_;

		vector<LPANIMATION_FRAME> frames_;
	public:

		Animation(int default_time)
		{
			default_time_ = default_time;
			last_frame_time_ = -1;
			current_frame_ = -1;
		}
		void Add(int sprite_id, DWORD time = 0);
		void Render(float x, float y);
	};

	typedef Animation* LPANIMATION;
}

#endif // !_ANIMATION_FRAME_H_
