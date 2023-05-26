#pragma once
#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"
#include "Game.h"

using namespace std;

namespace core {
	class Textures {
		static Textures* instance;

		unordered_map<int, LPTEXTURE> textures_;

	public:
		Textures() {};
		~Textures() {};

		void Add(int id, LPCWSTR file_path);

		LPTEXTURE Get(unsigned int id);

		static Textures* GetInstance();
	};
}
#endif // !_TEXTURES_H_
