#pragma once
#include <Windows.h>

class CMovingObject
{
protected:
	float ax;
	float ay;
	float vx;
	float vy;

public:
	CMovingObject(float x, float y) {
		ax = 0;
		ay = 0;
	};

	void Render();
	void Update(DWORD dt) {
		vx += ax * dt;
		vy += ay * dt;
	}
};
