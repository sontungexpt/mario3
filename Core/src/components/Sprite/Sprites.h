#pragma once
#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <unordered_map>
#include "Sprite.h"

using namespace std;

namespace core {
	class Sprites
	{
	private:
		static Sprites* instance;

		unordered_map<int, LPSPRITE> sprites_;

	public:
		void Add(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

		LPSPRITE Get(int id);
		static Sprites* GetInstance();
	};
}
#endif // !_SPRITES_H_