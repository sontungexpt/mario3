#pragma once
#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_

#include "Animation.h"
#include "components/Sprite/Sprite.h"

namespace core {
	class Animations
	{
		static Animations* instance;

		unordered_map<int, LPANIMATION> animations_;

	public:
		void Add(int id, LPANIMATION animation);
		LPANIMATION Get(int id);

		static Animations* GetInstance();
	};
}

#endif // !_ANIMATIONS_H_
