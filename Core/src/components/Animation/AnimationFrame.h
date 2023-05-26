#pragma once
#ifndef _ANIMATION_FRAME_H_
#define _ANIMATION_FRAME_H_

#include "components/Sprite/Sprite.h"

namespace core {
	class AnimationFrame
	{
	private:
		LPSPRITE sprite_;
		DWORD time_;

	public:
		AnimationFrame(LPSPRITE sprite, int time)
		{
			sprite_ = sprite;
			time_ = time;
		}
		DWORD GetTime() { return time_; }
		LPSPRITE GetSprite() { return sprite_; }
	};

	typedef AnimationFrame* LPANIMATION_FRAME;
}

#endif // !_ANIMATION_FRAME_H_
