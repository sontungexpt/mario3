#include "Animation.h"

namespace core {
	void Animation::Add(int spriteId, DWORD time)
	{
		int t = time;
		if (time == 0)
		{
			t = default_time_;
		}
		LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
		LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
		frames_.push_back(frame);
	}

	void Animation::Render(float x, float y)
	{
		ULONGLONG now = GetTickCount64();
		if (current_frame_ == -1)
		{
			current_frame_ = 0;
			last_frame_time_ = now;
		}
		else
		{
			DWORD t = frames_[current_frame_]->GetTime();
			if (now - last_frame_time_ > t)
			{
				current_frame_++;
				last_frame_time_ = now;
				if (current_frame_ == frames_.size()) current_frame_ = 0;
				//DebugOut(L"now: %d, last_frame_time_: %d, t: %d\n", now, last_frame_time_, t);
			}
		}

		frames_[current_frame_]->GetSprite()->Draw(x, y);
	}
}