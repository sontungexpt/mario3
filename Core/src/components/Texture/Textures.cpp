#include "Textures.h"

namespace core {
	Textures* Textures::instance = nullptr;

	Textures* Textures::GetInstance()
	{
		if (instance == nullptr) instance = new Textures();
		return instance;
	}

	void Textures::Add(int id, LPCWSTR file_path)
	{
		textures_[id] = Game::GetInstance()->LoadTexture(file_path);
	}

	LPTEXTURE Textures::Get(unsigned int id)
	{
		return textures_[id];
	}
}